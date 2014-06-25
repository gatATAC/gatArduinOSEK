#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>

// The Arduino board i2c address
#define ADDRESS 0x04

#define I2C_WAIT 40000

// The I2C bus: This is for V2 pi's. For V1 Model B you need i2c-0
static const char *devName = "/dev/i2c-1";
static char bufAnt[]="01234567s";

#define TRUE (1==1)
#define FALSE (1==0)

typedef unsigned char bool;

int main(int argc, char** argv) {

	///////////// Nos bifurcamos y guardaremos una pipe para que el proceso que no tiene i2c pueda enviarle
	///////////// sus comandos al que lo tiene
	int fd[2];
	pid_t childpid;

	pipe (fd);

	if ((childpid = fork ()) == -1)
	{
		perror ("fork");
		exit (1);
	}

	if (childpid == 0)
	{
		/* Child process closes up input side of pipe */
		printf("Soy el proceso padre con el fd %d y childpid %d\n",fd[0],childpid);


		if (fcntl(fd[0], F_SETFL, O_NONBLOCK) == -1){
			fprintf(stderr,"Call to fcntl failed.\n");
			exit(1);
		}

		//////// Conectamos el I2C
		printf("I2C: Connecting\n");

		int file;

		if ((file = open(devName, O_RDWR)) < 0) {
			fprintf(stderr, "I2C: Failed to access %d\n", devName);
			exit(1);
		}

		printf("I2C: acquiring buss to 0x%x\n", ADDRESS);

		if (ioctl(file, I2C_SLAVE, ADDRESS) < 0) {
			fprintf(stderr, "I2C: Failed to acquire bus access/talk to slave 0x%x\n", ADDRESS);
			exit(1);
		}

		/////////// Ahora entramos en el loop de gestión del i2c
		bool salida=FALSE;

		while (salida==FALSE) {
			char bufPipe[]="aaa";
			int nread=read(fd[0],bufPipe,3);
			switch (nread){
				case -1:
					// lA PIPE ESTÁ VACÍA ?
					if (errno == EAGAIN) {
						// La pipe está vacía, cursamos la petición normal
					} else {
						// Un error en la pipe
						fprintf(stderr, "Parent: could not read from pipe\n");
						exit(1);
					}
					bufPipe[1]='\0';
					break;
				case 0:
					// La pipe ha sido cerrada
					salida = TRUE;
					printf("Parent --> Pipe has been closed");
					break;
				default:
					// Hemos recibido un comando
					bufPipe[nread]='\0';
					if (bufPipe[0]=='q'){
						printf("Exit request received!!!!\n");
						salida=TRUE;
					} else {
						printf("Sending %s through I2C...\n",bufPipe);
					}
				break;
			}
			if (salida == FALSE) {
				///// Escribimos el comando de petición
				if (write(file, bufPipe, strlen(bufPipe)) == strlen(bufPipe)) {
					// Todo bien
				}
				usleep(I2C_WAIT);

				///// Recuperamos la respuesta
				char buf[]="01234567s";
				if (read(file, buf, 9) == 9) {
					/// Si la respuesta es diferente a la anterior, la escribimos x la consola
					if (strncmp(buf,bufAnt,9)!=0){
						strcpy(bufAnt,buf);
						printf("Status changed ---> %s\n", buf);
					}
				}
				// Now wait else you could crash the arduino by sending requests too fast
				usleep(I2C_WAIT);
			}
		}
		close(fd[0]);
  		close(file);
	} else
	{
		bool salida=FALSE;

		printf("Child process with pipe handler fd %d and childpid %d\n",fd[1],childpid);
		while (salida==FALSE){
			char buf[4];

			printf("Please send a command (3 characters, or 'q' to exit, or 'x' to cancel the command if you sent an incomplete one)\n");
			scanf("%s",buf);
			buf[3]='\0';

			if (buf[0]=='q' && buf[1]=='\0'){
				salida=TRUE;
			}

			printf("Command to send:  %s",buf);
			write(fd[1],buf,strlen(buf));
		}
		close (fd[1]);
	}
	printf("****** Exiting process with childpid %d\n",childpid);
	return (EXIT_SUCCESS);
}

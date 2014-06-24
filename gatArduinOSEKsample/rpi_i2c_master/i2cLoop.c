#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>

// The PiWeather board i2c address
#define ADDRESS 0x04

//#define DEBUG_I2C_LOAD

#ifdef DEBUG_I2C_LOAD
	#define I2C_WAIT 1000
#else
	#define I2C_WAIT 100000
#endif

// The I2C bus: This is for V2 pi's. For V1 Model B you need i2c-0
static const char *devName = "/dev/i2c-1";
static char bufAnt[]="01234567s";

int main(int argc, char** argv) {

  if (argc == 1) {
    printf("Supply one or more commands to send to the Arduino\n");
    exit(1);
  }

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

  int arg;

  for (arg = 1; arg < argc; 
#ifndef DEBUG_I2C_LOAD
arg++
#endif
) {
    char val[4];
    unsigned char cmd[16];

    if (0 == sscanf(argv[arg], "%s", val)) {
      fprintf(stderr, "Invalid parameter %d \"%s\"\n", arg, argv[arg]);
      exit(1);
    }
for (;;){
#ifndef DEBUG_I2C_LOAD
//    printf("Sending %s\n", val);
#endif
    if (write(file, val, 3) == 3) {
#ifndef DEBUG_I2C_LOAD
//      printf("Argument sent!\n");
#endif
    }
    usleep(I2C_WAIT);

      char buf[]="01234567s";

      if (read(file, buf, 9) == 9) {

	if (strncmp(buf,bufAnt,9)!=0){
		strcpy(bufAnt,buf);
#ifndef DEBUG_I2C_LOAD
		printf("Received %s    \n", buf);
#endif
	}
}

    // Now wait else you could crash the arduino by sending requests too fast
    usleep(I2C_WAIT);
 }
  }

  close(file);
  return (EXIT_SUCCESS);
}

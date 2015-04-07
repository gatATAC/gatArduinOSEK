CC=gcc
CFLAGS=
DEPS = 
OBJ =  

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

%: %.o
	$(CC) -o $@ $^ $(CFLAGS)

all: i2cTest i2cFork

clean:
	rm i2cTest
	rm i2cFork

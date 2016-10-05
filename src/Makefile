CC=gcc
CFLAGS=-I.
DEPS = toy_hash.h table.h

all: login cracker


%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

login: login.o toy_hash.o table.o
	gcc -o login login.o toy_hash.o table.o -I.

cracker: cracker.o toy_hash.o table.o
	gcc -o cracker cracker.o toy_hash.o table.o -I.

clean:
	rm login cracker *.o

	
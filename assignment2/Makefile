CC = gcc
CFLAGS = -std=c99 -pg -Wall -Werror -O2

default: strassen

strassen:  matrix_multiply.o
	$(CC) $(CFLAGS) -lm -o strassen matrix_multiply.o

matrix_multiply.o:  matrix_multiply.c matrix_multiply.h
	$(CC) $(CFLAGS) -c matrix_multiply.c

clean: 
	$(RM) strassen *.o *~

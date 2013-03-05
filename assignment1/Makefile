# Typing 'make' or 'make randmst' will create the executable file.

# define some Makefile variables for the compiler and compiler flags
# to use Makefile variables later in the Makefile: $()
#
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CC = gcc
CFLAGS = -std=c99 -g -lm -Wall -Werror -O2

# typing 'make' will invoke the first target entry in the file 
default: randmst

# To create the executable file count we need the object files
# disjoint_set.o and graph.o:
randmst:  disjoint-set.o graph.o main.o 
	$(CC) $(CFLAGS) -o randmst disjoint-set.o graph.o main.o

# To create the object file disjoint_set.o, we need the source
# files disjoint_set.c and disjoint_set.h:
disjoint-set.o:  disjoint-set.c disjoint-set.h
	$(CC) $(CFLAGS) -c disjoint-set.c

# To create the object file graph.o, we need the source files
# graph.c and graph.h:
graph.o:  graph.c graph.h 
	$(CC) $(CFLAGS) -c graph.c

# To create the object file main.o, we need the source files main.o
main.o:  main.c
	$(CC) $(CFLAGS) -c main.c

# This removes the executable file, as well as old .o object
# files and *~ backup files:
clean: 
	$(RM) randmst *.o *~

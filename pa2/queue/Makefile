#------------------------------------------------------------------------------
#  Makefile for Queue ADT
#
#      make             makes QueueTest
#      make clean       removes object files
#
#------------------------------------------------------------------------------

QueueTest : QueueTest.o Queue.o
	gcc -o QueueTest QueueTest.o Queue.o 

QueueTest.o : Queue.h QueueTest.c
	gcc -c -std=c99 -Wall QueueTest.c

Queue.o : Queue.h Queue.c
	gcc -c -std=c99 -Wall Queue.c

clean :
	rm -f QueueTest QueueTest.o Queue.o


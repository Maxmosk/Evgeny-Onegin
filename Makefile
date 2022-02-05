.PHONY: all clean


#C programming language compiler
CC=gcc
#Compiler flags
CFLAGS=-Wall


all: sort


sort: main.o text.o helper.o sort.o
	$(CC) $(CFLAGS) -o sort main.o text.o helper.o sort.o

main.o: main.c
	$(CC) -c $(CFLAGS) -o main.o main.c
text.o: text.c
	$(CC) -c $(CFLAGS) -o text.o text.c
helper.o: helper.c
	$(CC) -c $(CFLAGS) -o helper.o helper.c
sort.o: sort.c
	$(CC) -c $(CFLAGS) -o sort.o sort.c

clean:
	rm -rf *.o sort


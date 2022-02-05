.PHONY: all clean


#C programming language compiler
CC=gcc
#Compiler flags
CFLAGS=  -Wall -Wextra -Wfloat-equal -Wundef -Wshadow -Wpointer-arith -Wcast-align 
CFLAGS+= -Wstrict-prototypes -Wstrict-overflow=5 -Wwrite-strings -Waggregate-return 
CFLAGS+= -Wcast-qual -Wswitch-default -Wswitch-enum -Wconversion -Wunreachable-code 
CFLAGS+= -Wformat=2 -Werror -Winit-self -Wuninitialized -Wpointer-arith -save-temps 
CFLAGS+= -Wold-style-definition -Wstrict-prototypes -Wmissing-prototypes 
CFLAGS+= -Werror-implicit-function-declaration -Wlogical-op -Wduplicated-cond
CFLAGS+= -Wcast-qual -Wcast-align -Wformat-security 
CFLAGS+= -lasan -fsanitize=address,leak,undefined -fstack-protector 
CFLAGS+= -s -masm=intel -pedantic -std=c99


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
	rm -rf *.o sort *.s *.i


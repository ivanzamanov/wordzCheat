DEBUG=-g
CC=g++
CFLAGS=-c -Wall -std=c++11 $(DEBUG)
LFLAGS=-Wall $(DEBUG)

OBJS=main.o ptree.o

all: clean $(OBJS)
	mkdir -p bin
	$(CC) $(LFLAGS) $(OBJS) -o bin/cheat

main.o:
	$(CC) $(CFLAGS) src/main.cpp

ptree.o:
	$(CC) $(CFLAGS) src/ptree.cpp

clean:
	rm -rf bin
	rm *.o

CC = clang++-9
GCC = gcc
FLAGS = -g -c
LFLAGS = -lpthread

all: guard singleton queue

guard: guard.o
	$(CC) guard.o -o guard $(LFLAGS)

singleton: singleton.o
	$(CC) singleton.o -o singleton $(LFLAGS)

queue: queue.o
	$(GCC) queue.o -o queue $(LFLAGS)

guard.o: guard.cpp
	$(CC) $(FLAGS) guard.cpp 

singleton.o: singleton.cpp
	$(CC) $(FLAGS) singleton.cpp

queue.o: queue.c
	$(GCC) $(FLAGS) queue.c

clean:
	rm -f *.o guard singleton main
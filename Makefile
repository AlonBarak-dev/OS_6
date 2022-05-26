CC = clang++-9
GCC = gcc
FLAGS = -g -c
LFLAGS = -lpthread

all: guard singleton main 

guard: guard.o
	$(CC) guard.o -o guard $(LFLAGS)

singleton: singleton.o
	$(CC) singleton.o -o singleton $(LFLAGS)

main: main1.o
	$(GCC) main1.o -o main $(LFLAGS)

client: client.o
	$(GCC) client.o -o client

guard.o: guard.cpp
	$(CC) $(FLAGS) guard.cpp 

singleton.o: singleton.cpp
	$(CC) $(FLAGS) singleton.cpp

queue.o: queue.c
	$(GCC) $(FLAGS) queue.c

main1.o: main1.c
	$(GCC) $(FLAGS) main1.c

client.o: client.c
	$(GCC) $(FLAGS) client.c

clean:
	rm -f *.o guard singleton main 
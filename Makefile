CC = clang++-9
GCC = gcc
FLAGS = -g -c
LFLAGS = -lpthread
OBJECTS = guard.o singleton.o queue.o AO.o main1.o client.o pollServer.o reactor.o

all: guard singleton main client pollserver 

guard: guard.o
	$(CC) guard.o -o guard $(LFLAGS)

singleton: singleton.o
	$(CC) singleton.o -o singleton $(LFLAGS)

main: main1.o queue.o AO.o
	$(GCC) main1.o queue.o AO.o -o main $(LFLAGS)

client: client.o
	$(GCC) client.o -o client

pollserver: pollServer.o reactor.o
	$(CC) pollServer.o reactor.o -o pollserver $(LFLAGS)

guard.o: guard.cpp
	$(CC) $(FLAGS) guard.cpp 

singleton.o: singleton.cpp
	$(CC) $(FLAGS) singleton.cpp

queue.o: queue.c
	$(GCC) $(FLAGS) queue.c

AO.o: AO.c
	$(GCC) $(FLAGS) AO.c

main1.o: main1.c
	$(GCC) $(FLAGS) main1.c

client.o: client.c
	$(GCC) $(FLAGS) client.c

pollServer.o: pollServer.cpp
	$(CC) $(FLAGS) pollServer.cpp

reactor.o: reactor.cpp
	$(CC) $(FLAGS) reactor.cpp

OS6: $(OBJECTS)
	gcc --shared -fPIC -pthread $(OBJECTS)

clean:
	rm -f *.o guard singleton main pollserver client
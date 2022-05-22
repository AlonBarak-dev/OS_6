CC = clang++-9
FLAGS = -g -c
LFLAGS = -lpthread

guard: guard.o
	$(CC) guard.o -o guard $(LFLAGS)

singleton: singleton.o
	$(CC) singleton.o -o singleton $(LFLAGS)

guard.o: guard.cpp
	$(CC) $(FLAGS) guard.cpp 

singleton.o: singleton.cpp
	$(CC) $(FLAGS) singleton.cpp

clean:
	rm -f guard.o guard
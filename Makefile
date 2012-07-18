exe=test
ldflags=-lrt
ccflags=-std=c++0x -ggdb -Wall -Wextra
cc=g++

.PHONY: all clean

all: $(exe)

clean:
	@rm -f *.o
	@rm -f $(exe)

test: main.cpp timer.o LinkedList.cpp LinkedList_iterator.cpp LinkedList_sort.cpp LinkedList.h
	$(cc) $(ccflags) $< timer.o $(ldflags) -o $@

timer.o: timer.cpp timer.h
	$(cc) $(ccflags) -c $< $(ldflags) -o $@

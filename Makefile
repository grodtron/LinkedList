exe=test
ldflags=
ccflags=-ggdb#-Wall -Wextra
cc=g++

.PHONY: all clean

all: $(exe)

clean:
	@rm -f *.o
	@rm -f $(exe)

test: main.cpp LinkedList.cpp LinkedList_iterator.cpp LinkedList.h
	$(cc) $(ccflags) $(ldflags) $< -o $@

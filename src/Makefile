.PHONY: all clean

CC := g++
CFLAGS := -std=c++11 -O2 -Wall
BINARIES := main

main: main.cpp mochila.cpp
	$(CC) $(CFLAGS) -o main main.cpp mochila.cpp
clean:
	rm -f $(BINARIES) *.o

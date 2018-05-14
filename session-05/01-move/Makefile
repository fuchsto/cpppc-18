
CC=g++
CFLAGS=--std=c++11 -Wall -Wextra -pedantic -O0
LDFLAGS=-lrt

OBJS = main.o array_maker.o

.DEFAULT: all
all: $(OBJS) main.a

run: main.a
	clear
	./main.a

%.o: %.cc
	$(CC) $(CFLAGS) -c $< -o $@

%.a: $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $@

.PHONY: clean
clean:
	-rm -f *.o
	-rm -f *.a

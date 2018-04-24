
CC=g++
CFLAGS=--std=c++11 -Wall -Wextra -pedantic -g
LDFLAGS=-lrt

OBJS = main.o

.DEFAULT: all
all: $(OBJS) main.a

run: main.a
	./main.a

%.pp.cc: %.cc
	$(CC) $(CFLAGS) -E $< | clang-format -style=file > $@

%.o: %.cc
	$(CC) $(CFLAGS) -c $< -o $@

%.a: $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $@

.PHONY: clean
clean:
	-rm -f *.o
	-rm -f *.a
	-rm -f *.pp.cc

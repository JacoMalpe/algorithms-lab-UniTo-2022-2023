CC = gcc

CFLAGS = -Ofast -Wall -Wextra -Wpedantic -Wconversion

INCLUDES = src/*.h

COMMON_DEPS = $(INCLUDES) Makefile

ARG0 ?= data/dictionary.txt data/correctme.txt

ARG1 ?= 20

all: clean build/main_ex2

bin/%.o: src/%.c $(COMMON_DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

build/main_ex2: bin/skiplist.o bin/main_ex2.o $(COMMON_DEPS)
	$(CC) -o build/main_ex2 bin/skiplist.o bin/main_ex2.o

build/skiplist_test: bin/skiplist_test.o bin/skiplist.o bin/unity.o $(COMMON_DEPS)
	$(CC) -o build/skiplist_test  bin/skiplist_test.o bin/skiplist.o bin/unity.o

run:
	./build/main_ex2 $(ARG0) $(ARG1)

test: build/skiplist_test
	./build/skiplist_test

clean:
	rm -f build/* bin/*

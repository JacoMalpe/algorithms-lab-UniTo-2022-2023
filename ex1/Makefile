CC = gcc

CFLAGS = -Ofast -Wall -Wpedantic

INCLUDES = src/*.h

COMMON_DEPS = $(INCLUDES) Makefile

ARG0 ?= ./record.csv ./sorted.csv

ARG1 ?= 40 2

all: clean build/main_ex1

bin/%.o: src/%.c $(COMMON_DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

build/main_ex1: bin/merge_binary_insertion_sort.o bin/main_ex1.o $(COMMON_DEPS)
	$(CC) -o build/main_ex1 bin/merge_binary_insertion_sort.o bin/main_ex1.o

build/merge_binary_insertion_sort_test: bin/merge_binary_insertion_sort_test.o bin/merge_binary_insertion_sort.o bin/unity.o $(COMMON_DEPS)
	$(CC) -o build/merge_binary_insertion_sort_test  bin/merge_binary_insertion_sort_test.o bin/merge_binary_insertion_sort.o bin/unity.o

run:
	./build/main_ex1 $(ARG0) $(ARG1)

test: build/merge_binary_insertion_sort_test
	./build/merge_binary_insertion_sort_test

clean:
	rm -f build/* bin/*

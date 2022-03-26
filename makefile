CC = gcc
FLAGS = -Wextra  -Wall -std=c99
SRC = src/main.c

.PHONY: all run clean
all: bin/main

run: bin/main
	./bin/main

clean:
	- rm bin/*

bin/main: $(SRC)
	$(CC) $(FLAGS) -o $@ $^

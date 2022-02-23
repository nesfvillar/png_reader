CC = gcc
FLAGS = -Wextra  -Wall

all: bin/main

bin/main: src/main.c
	gcc $(FLAGS) -o bin/main src/main.c

.PHONY: run clean
run: bin/main
	./bin/main

clean:
	rm bin/main




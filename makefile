CC = gcc
FLAGS = -Wextra  -Wall -std=c99
EXC = bin/png_reader
SRC = src/png_reader.c
OBJS = lib/chunk.o lib/dynArr.o

.PHONY: all run clean
all: ${EXC}

run: ${EXC}
	${EXC}

clean:
	@- rm bin/* lib/*

${EXC}: $(SRC) $(OBJS)
	@ mkdir -p bin/
	$(CC) $(FLAGS) -o $@ $^

lib/%.o: src/%.c src/%.h
	@ mkdir -p lib/
	$(CC) $(FLAGS) -c -o $@ $<

#include "dynArr.h"
#include "chunk.h"
#include "stdlib.h"

void dynArr_init(DynArr *dynArr) {
    dynArr->size = 1;
    dynArr->top = 0;
    dynArr->data = malloc(sizeof(chunk_t));
}

void dynArr_push(DynArr *dynArr, chunk_t chunk) {
    if (dynArr->top >= dynArr->size) {
        dynArr_resize(dynArr, dynArr->size * 2);
    }

    dynArr->data[dynArr->top++] = chunk;
}

chunk_t dynArr_pop(DynArr *dynArr) {
    if (dynArr->top == 0) {
        perror("ERROR tried to pop an empty stack");
        exit(1);
    }
    return dynArr->data[--dynArr->top];
}

void dynArr_resize(DynArr *dynArr, size_t new_size) {
    dynArr->size = new_size;
    chunk_t *new_data = malloc(sizeof(chunk_t) * new_size);
    for (size_t i = 0; i < dynArr->top; i++) {
        new_data[i] = dynArr->data[i];
    }
    free(dynArr->data);
    dynArr->data = new_data;
}

void dynArr_clear(DynArr *dynArr) {
    for (size_t i = 0; i < dynArr->top; i++) {
        chunk_t chunk = dynArr_pop(dynArr);
        freeChunk(&chunk);
    }
}
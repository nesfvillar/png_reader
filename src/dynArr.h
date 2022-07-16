#ifndef DYN_ARR_H
#define DYN_ARR_H

#include "chunk.h"

typedef struct DynArr {
    size_t size;
    size_t top;
    chunk_t *data;
} DynArr;

void dynArr_init(DynArr *);

void dynArr_push(DynArr *, chunk_t);

chunk_t dynArr_pop(DynArr *);

void dynArr_resize(DynArr *, size_t);

void dynArr_clear(DynArr *);

#endif
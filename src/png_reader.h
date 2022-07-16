#ifndef PNG_READER_H
#define PNG_READER_H

#include "dynArr.h"

DynArr png_read(char *);

void png_print(DynArr *);

void png_clean(DynArr *);


#endif
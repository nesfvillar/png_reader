#include "chunk.h"
#include "dynArr.h"
#include "png_reader.h"
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char **argv) {
  if (argc == 1) {
    fprintf(stderr, "Usage: %s IMAGE.png\n", argv[0]);
    exit(1);
  }

  for (int i = 1; i < argc; i++) {
    char *file_name = argv[i];

      DynArr dynArr = png_read(file_name);

    png_print(&dynArr);
    png_clean(&dynArr);
  }

  return 0;
}


DynArr png_read(char *file_name) {
  FILE *file = fopen(file_name, "r");
  if (file == NULL) {
    perror("ERROR could not open file");
    exit(1);
  }

  uint8_t header[8];
  readChunkPart(header, file, sizeof(header));

  chunk_t chunk;
  chunk = readChunk(file);
  DynArr dynArr;
  dynArr_init(&dynArr);
  dynArr_push(&dynArr, chunk);

  while (chunk.int_length > 0) {
    chunk = readChunk(file);
    dynArr_push(&dynArr, chunk);
  }
  fclose(file);

  return dynArr;
}

void png_print(DynArr *dynArr) {
  for (size_t i = 0; i < dynArr->top; i++) {
    printChunk(&dynArr->data[i]);
  }
}

void png_clean(DynArr *dynArr) {
  dynArr_clear(dynArr);
}
#include "chunk.h"
#include "dynArr.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: %s IMAGE.png\n", argv[0]);
    exit(1);
  }
  char *file_name = argv[1];

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

  for (size_t i = 0; i < dynArr.top; i++) {
    printChunk(&dynArr.data[i]);
  }

  dynArr_clear(&dynArr);
  return 0;
}
#include "chunk.h"
#include <stdio.h>
#include <stdlib.h>

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

  for (size_t i = 0; i < sizeof(header); i++) {
    printf("%X ", header[i]);
  }
  printf("\n\n");

  chunk_t chunk;
  while (chunk.int_length > 0) {
    chunk = readChunk(file);

    printChunk(&chunk);

    freeChunk(&chunk);
  }

  fclose(file);
  return 0;
}

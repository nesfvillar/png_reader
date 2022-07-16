#include "chunk.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

chunk_t readChunk(FILE *file) {
  chunk_t chunk;
  readChunkPart(chunk.length, file, sizeof(chunk.type));
  readChunkPart(chunk.type, file, sizeof(chunk.type));

  chunk.int_length = arrToInt(chunk.length, sizeof(chunk.length));
  if (chunk.int_length > 0) {
    chunk.data = malloc(chunk.int_length);
    if (chunk.data == NULL) {
      perror("ERROR could not allocate memory");
      exit(1);
    }
    readChunkPart(chunk.data, file, chunk.int_length);
  }

  readChunkPart(chunk.crc, file, sizeof(chunk.crc));

  return chunk;
}

void readChunkPart(uint8_t *part, FILE *file, size_t size) {
  size_t result = fread(part, size, 1, file);
  if (result != 1) {
    perror("ERROR could not read bytes");
    exit(1);
  }
}

void printChunk(const chunk_t *chunk) {
  printf("Length: 0x");
  for (size_t i = 0; i < sizeof(chunk->length); i++) {
    printf("%X", chunk->length[i]);
  }
  printf("\n");

  printf("Type: ");
  for (size_t i = 0; i < sizeof(chunk->type); i++) {
    printf("%c", chunk->type[i]);
  }
  printf("\n");

  printf("CRC: ");
  for (size_t i = 0; i < sizeof(chunk->crc); i++) {
    printf("%X", chunk->crc[i]);
  }
  printf("\n\n");
}

int arrToInt(uint8_t *arr, size_t size) {
  int result = 0;
  for (size_t i = 0; i < size; i++) {
    result |= arr[i] << 8 * (size - i - 1);
  }
  return result;
}

void freeChunk(chunk_t *chunk) {
  if (chunk->int_length > 0) {
    free(chunk->data);
  }
}

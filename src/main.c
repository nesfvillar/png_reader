#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  uint8_t length[4];
  uint32_t int_length;
  uint8_t type[4];
  uint8_t *data;
  uint8_t crc[4];
} chunk_t;

chunk_t readChunk(FILE *);
void readPart(uint8_t *, FILE *, size_t);
int arrToInt(uint8_t *, size_t);
void freeChunk(chunk_t*);

int arrToInt(uint8_t *arr, size_t size) {
  int result = 0;
  for (size_t i = 0; i < size; i++) {
    result |= arr[i] << 8 * (size - i - 1);
  }
  return result;
}

chunk_t readChunk(FILE *file) {
  chunk_t chunk;
  readPart(chunk.length, file, sizeof(chunk.type));
  readPart(chunk.type, file, sizeof(chunk.type));

  chunk.int_length = arrToInt(chunk.length, sizeof(chunk.length));
  if (chunk.int_length > 0) {
    chunk.data = malloc(chunk.int_length);
    if (chunk.data == NULL) {
      perror("ERROR could not allocate memory");
      exit(1);
    }
    readPart(chunk.data, file, chunk.int_length);
  }

  readPart(chunk.crc, file, sizeof(chunk.crc));

  return chunk;
}

void readPart(uint8_t *part, FILE *file, size_t size) {
  size_t result = fread(part, size, 1, file);
  if (result != 1) {
    perror("ERROR could not read bytes");
    exit(1);
  }
}

void printChunk(const chunk_t *chunk) {
  for (size_t i = 0; i < sizeof(chunk->length); i++) {
    printf("%X ", chunk->length[i]);
  }
  printf("\n");

  for (size_t i = 0; i < sizeof(chunk->type); i++) {
    printf("%c ", chunk->type[i]);
  }
  printf("\n");

  for (size_t i = 0; i < sizeof(chunk->crc); i++) {
    printf("%X ", chunk->crc[i]);
  }
  printf("\n\n");
}

void freeChunk(chunk_t* chunk) {
  if (chunk->int_length > 0) {
    free(chunk->data);
  }
}

int main() {
  char *file_name = "data/784px-PNG-Gradient_hex.png";

  FILE *file = fopen(file_name, "r");
  if (file == NULL) {
    perror("ERROR could not open file");
    exit(1);
  }

  uint8_t header[8];
  readPart(header, file, sizeof(header));

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

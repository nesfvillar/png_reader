#include <stdint.h>
#include <stdio.h>

typedef struct {
  uint8_t length[4];
  uint32_t int_length;
  uint8_t type[4];
  uint8_t *data;
  uint8_t crc[4];
} chunk_t;

chunk_t readChunk(FILE *);

void readChunkPart(uint8_t *, FILE *, size_t);

void printChunk(const chunk_t *chunk);

int arrToInt(uint8_t *, size_t);

void freeChunk(chunk_t *);

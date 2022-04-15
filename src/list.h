#ifndef LIST_H
#define LIST_H
#include "chunk.h"

typedef struct list {
  chunk_t value;
  struct list *next;
  struct list *prev;
} list_t;

list_t *list_init();

void list_dest(list_t *list);

void list_node_dest(list_t *node);

void list_node_remove(list_t *node);

list_t *list_head(list_t *list);

list_t *list_tail(list_t *list);

void list_append(list_t *list, chunk_t chunk);

void list_prepend(list_t *list, chunk_t chunk);
#endif

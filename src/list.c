#include "list.h"
#include <stdlib.h>

list_t *list_init(chunk_t chunk) {
  list_t *list = malloc(sizeof(list_t));
  list->value = chunk;
  list->next = list->prev = NULL;
  return list;
}

void list_dest(list_t *list) {
  if (list->prev != NULL) {
    list->prev->next = NULL;
    list_dest(list->prev);
  }
  if (list->next != NULL) {
    list->next->prev = NULL;
    list_dest(list->next);
  }
  list_node_dest(list);
}

void list_node_dest(list_t *node) {
  freeChunk(&node->value);
  free(node);
}

void list_node_remove(list_t *node) {
  list_t *prev = node->prev;
  list_t *next = node->next;
  list_node_dest(node);
  prev->next = next;
  next->prev = prev;
}

list_t *list_head(list_t *list) {
  if (list->prev == NULL) {
    return list;
  } else {
    return list_head(list->prev);
  }
}

list_t *list_tail(list_t *list) {
  if (list->next == NULL) {
    return list;
  } else {
    return list_tail(list->next);
  }
}

void list_append(list_t *list, chunk_t chunk) {
  list_t *new_node = list_init(chunk);
  list_t *tail = list_tail(list);
  new_node->prev = tail;
  tail->next = new_node;
}

void list_prepend(list_t *list, chunk_t chunk) {
  list_t *new_node = list_init(chunk);
  list_t *head = list_head(list);
  new_node->next = head;
  head->prev = new_node;
}

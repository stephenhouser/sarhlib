/* 
 *
 */

/****** LIST ******/

#if !defined(LIST_H)
#define LIST_H

#include "common.h"

/* The list contains only pointers to the elements, not the elements themselves */

typedef struct list_s List;
typedef struct list_node_s ListNode;

bool list_init(List *list);
void list_destroy(List *list);

bool list_empty(List *list);
size_t list_size(List *list);

bool list_add(List *list, void *element);
bool list_remove(List *list, void *element);

void list_map(List *list, void (*map_function)(void *));
void list_reduce(List *list, void (*reduce_function)(void *, void *, void *), void *result);

#endif

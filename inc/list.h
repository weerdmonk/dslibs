
/*
 * dslibs v0.1
 * list implementation v0.1
 * weerdmonk Dec2014
 *
 */

#ifndef LIST_H
#define LIST_H

#include <stdlib.h>
#include <error.h>

#define DS_LIST_ALLOC_SIZE		sizeof(struct _List)
#define DS_LIST_NODE_SIZE		sizeof(struct _LNode)

typedef struct _LNode *LNode;

struct _LNode {
   void *data;
   struct _LNode *next;
};

typedef struct _List *List;

struct _List {
   LNode head;
   LNode tail;
};

LNode _ds_list_node_new(void *data);

List ds_list_new(void *data);

List ds_list_append(List l, void *data);

List ds_list_prepend(List l, void *data);

List ds_list_insert_pos(List l, void *data, int pos);

List ds_list_delete_pos(List l, void **data, int pos);

LNode ds_list_search(List l, void* data, int *pos);

List ds_list_update_pos(List l, void *data_new, void **data_old, int pos);

int ds_list_count(List l);

#endif /* LIST_H */

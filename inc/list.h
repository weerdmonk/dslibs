
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

// FIXME move structure declarations to source file. header will be exported.

typedef struct _LNode *LNode;

struct _LNode {
   void *data;
   struct _LNode *next;
   struct _LNode *prev;
};

typedef struct _List *List;

struct _List {
   LNode head;
   LNode tail;
};

LNode _ds_list_node_new(void *data);

List ds_list_new(void *data);

void ds_list_del(List l);

void ds_list_free(List *p_l);

List ds_list_append(List l, void *data);

List ds_list_append_val(List l, unsigned int data);

List ds_list_prepend(List l, void *data);

List ds_list_prepend_val(List l, unsigned int data);

List ds_list_insert_pos(List l, void *data, int pos);

List ds_list_insert_pos_val(List l, unsigned int data, int pos);

List ds_list_delete_pos(List l, void **data, int pos);

List ds_list_delete_pos_val(List l, unsigned int *data, int pos);

List ds_list_delete_start(List l, void **data);

List ds_list_delete_start_val(List l, unsigned int *data);

List ds_list_delete_end(List l, void **data);

List ds_list_delete_end_val(List l, unsigned int *data);

List ds_list_free_pos(List l, int pos);

LNode ds_list_search(List l, void *data, int *pos);

LNode ds_list_search_val(List l, unsigned int data, int *pos);

List ds_list_update_pos(List l, void *data_new, void **data_old, int pos);

List ds_list_update_pos_val(List l, unsigned int data_new, unsigned int *data_old, int pos);

int ds_list_count(List l);

#endif /* LIST_H */

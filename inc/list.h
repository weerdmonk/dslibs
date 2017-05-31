
/*
 * dslibs v0.1
 * list implementation v0.1
 * weerdmonk Dec2014
 *
 */

#ifndef LIST_H
#define LIST_H

typedef struct LNode_t *LNode;

typedef struct List_t *List;

typedef int (*ds_list_callback)(List l, void* node_data, void *cb_data);

void ds_list_callback_add(List l, ds_list_callback cb, void *cb_data);

void ds_list_callback_remove(List l);

List ds_list_new(void *p_data);

void ds_list_delete(List l, unsigned char should_free_data);

List ds_list_append(List l, void *p_data);

List ds_list_prepend(List l, void *p_data);

LNode ds_list_search(List l, void *p_data);

List ds_list_insert_after(List l, LNode node, void *p_data);

List ds_list_insert_before(List l, LNode node, void *p_data);

List ds_list_delete_node(List l, LNode node, void **p_data);

List ds_list_delete_head(List l, void **p_data);

List ds_list_delete_tail(List l, void **p_data);

List ds_list_update_node(List l, LNode node, void *p_new_data, void **p_old_data);

unsigned int ds_list_count(List l);

unsigned int ds_list_traverse_forward(List l, LNode node);

unsigned int ds_list_traverse_reverse(List l, LNode node);

LNode ds_list_get_head(List l);

LNode ds_list_get_tail(List l);

LNode ds_list_get_next_node(List l, LNode node);

LNode ds_list_get_prev_node(List l, LNode node);

void ds_list_get_data(LNode node, void **p_data);

#endif /* LIST_H */

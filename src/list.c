
/*
 * dslibs v0.1
 * list implementation v0.1
 * weerdmonk Dec2014
 *
 */

#include <stdlib.h>
#include <error.h>
#include <list.h>

#define DS_LIST_NODE_ALLOC_SIZE   sizeof(struct LNode_t)
#define DS_LIST_ALLOC_SIZE	sizeof(struct List_t)

struct LNode_t
{
  void *data;
  struct LNode_t *prev;
  struct LNode_t *next;
} __attribute__ ((aligned (4))) ;

struct List_t
{
  LNode head;
  LNode tail;
  ds_list_callback cb;
  void *cb_data;
  unsigned int count;
} __attribute__ ((aligned (4))) ;

void ds_list_callback_add(List l, ds_list_callback cb, void *cb_data)
{
  if (!l || !cb)
  {
    return;
  }
  else
  {
    l->cb = cb;
    if (cb_data != NULL)
    {
      l->cb_data = cb_data;
    }
  }

  return;
}

void ds_list_callback_remove(List l)
{
  if (!l || !l->cb)
  {
    return;
  }
  else
  {
    l->cb = NULL;
    l->cb_data = NULL;
  }

  return;
}

static LNode ds_list_node_new(void *p_data)
{
  LNode ln = aligned_alloc(4, DS_LIST_NODE_ALLOC_SIZE);
  if (!ln)
  {
    DS_C_ERR(__func__);
    return NULL;
  }

  if (!p_data)
  {
    DS_LIB_ERR("ds_list_node_new: no data to supplied!");
    free(ln);
    return NULL;
  }

  ln->data = p_data;
  ln->prev = ln->next = NULL;

  return ln;
}

List ds_list_new(void *p_data)
{
  List l = aligned_alloc(4, DS_LIST_ALLOC_SIZE);
  if (!l)
  {
    DS_C_ERR(__func__);
    return NULL;
  }

  if (p_data != NULL)
  {
    l->head = ds_list_node_new(p_data);
    if (!l->head)
    {
      DS_LIB_ERR("ds_list_new: failed to create new list node!");
      free(l);
      return NULL;
    }
    l->count++;
  }
  else
  {
    l->head = NULL;
  }
  l->tail = l->head;
  l->cb = NULL;
  l->cb_data = NULL;
  l->count = 0;

  return l;
}

static void ds_list_delete_nodes(List l, unsigned char should_free_data)
{
  LNode ln, tmp;

  if (!l)
  {
    DS_LIB_ERR("ds_list_delete_nodes: supplied argument 1 is not a valid List!");
    return;
  }

  if (!l->head) return;

  for(ln = l->head; ln != NULL; )
  {
    tmp = ln;
    ln = ln->next;
    l->head = ln;
    free(tmp);
    l->count--;
  }

  l->tail = l->head;
}

void ds_list_delete(List l, unsigned char should_free_data)
{
  if (!l)
  {
    DS_LIB_ERR("ds_list_delete: supplied argument 1 is not a valid List!");
    return;
  }

  ds_list_delete_nodes(l, should_free_data);

  free(l);
  l = NULL;
}

List ds_list_append(List l, void *p_data)
{
  if (!l)
  {
    DS_LIB_ERR("ds_list_append: supplied argument 1 is not a valid List!");
    return NULL;
  }

  if (!p_data)
  {
    DS_LIB_ERR("ds_list_append: no data to append!");
    return l;
  }

  LNode ln = ds_list_node_new(p_data);
  if (!ln)
  {
    DS_LIB_ERR("ds_list_append: failed to create new list node!");
    return l;
  }

  if (l->head == NULL)
  {
    l->head = ln;
    l->tail = l->head;
  }
  else
  {
    l->tail->next = ln;
    ln->prev = l->tail;
    l->tail = ln;
  }
  l->count++;

  return l;
}

List ds_list_prepend(List l, void *p_data)
{
  if (!l)
  {
    DS_LIB_ERR("ds_list_prepend: supplied argument 1 is not a valid List!");
    return NULL;
  }

  if (!p_data)
  {
    DS_LIB_ERR("ds_list_prepend: no data to prepend!");
    return l;
  }

  LNode ln = ds_list_node_new(p_data);
  if (!ln)
  {
    DS_LIB_ERR("ds_list_prepend: failed to create new list node!");
    return l;
  }

  if (l->head == NULL)
  {
    l->head = ln;
    l->tail = l->head;
  }
  else
  {
    ln->next = l->head;
    l->head->prev = ln;
    l->head = ln;
  }
  l->count++;

  return l;
}


LNode ds_list_search(List l, void *p_data)
{
  LNode dest = NULL;

  if (!l)
  {
    DS_LIB_ERR("ds_list_search: supplied argument 1 is not a valid List!");
    return dest;
  }

  if (!p_data)
  {
    DS_LIB_ERR("ds_list_search: pointer to data is invalid!");
    return dest;
  }

  for (dest = l->head; dest != NULL; dest = dest->next)
  {
    if (dest->data == p_data)
    {
      break;
    }
  }

  return dest;
}

List ds_list_insert_after(List l, LNode node, void *p_data)
{
  LNode tmp;

  if (!l)
  {
    DS_LIB_ERR("ds_list_insert_after: supplied argument 1 is not a valid List!");
    return NULL;
  }

  if (!node)
  {
    DS_LIB_ERR("ds_list_insert_after: no node passed to insert after!");
    return l;
  }

  if (!p_data)
  {
    DS_LIB_ERR("ds_list_insert_after: no data passed to insert!");
    return l;
  }

  if ( l->tail == node )
  {
    return ds_list_append(l, p_data);
  }
  else
  {
    tmp = ds_list_node_new(p_data);
    if (!tmp)
    {
      DS_LIB_ERR("ds_list_insert_after: failed to create new list node!");
      return l;
    }

    tmp->prev = node;
    tmp->next = node->next;
    node->next = tmp;
    if (tmp->next != NULL)
    {
      tmp->next->prev = tmp;
    }
  }
  l->count++;

  return l;
}

List ds_list_insert_before(List l, LNode node, void *p_data)
{
  LNode tmp;

  if (!l)
  {
    DS_LIB_ERR("ds_list_insert_before: supplied argument 1 is not a valid List!");
    return NULL;
  }

  if (!node)
  {
    DS_LIB_ERR("ds_list_insert_before: no node passed to insert after!");
    return l;
  }

  if (!p_data)
  {
    DS_LIB_ERR("ds_list_insert_before: no data passed to insert!");
    return l;
  }

  tmp = ds_list_node_new(p_data);
  if (!tmp)
  {
    DS_LIB_ERR("ds_list_insert_before: failed to create new list node!");
    return l;
  }

  if ( l->head == node )
  {
    return ds_list_prepend(l, p_data);
  }
  else
  {
    tmp->next = node;
    tmp->prev = node->prev;
    node->prev = tmp;
    if (tmp->prev != NULL)
    {
      tmp->prev->next = tmp;
    }
  }

  return l;
}

List ds_list_delete_node(List l, LNode node, void **p_data)
{
  LNode tmp;

  if (!l)
  {
    DS_LIB_ERR("ds_list_delete_node: supplied argument 1 is not a valid List!");
    return NULL;
  }

  if (!p_data)
  {
    DS_LIB_ERR("ds_list_delete_node: no variabe to save data from node to be deleted!");
    return l;
  }

  if (l->count == 0)
  {
    DS_LIB_ERR("ds_list_delete_node: list is already empty!\n");
  }

  tmp = node;
  *p_data = tmp->data;
  if (tmp->next != NULL)
  {
    tmp->next->prev = tmp->prev;
  }
  if (tmp->prev != NULL)
  {
    tmp->prev->next = tmp->next;
  }
  if (tmp == l->head)
  {
    l->head = tmp->next;
  }
  if (tmp == l->tail)
  {
    l->tail = tmp->prev;
  }
  free(tmp);
  l->count--;

  return l;
}

List ds_list_delete_head(List l, void **p_data)
{
  if (!l)
  {
    DS_LIB_ERR("ds_list_delete_head: supplied argument 1 is not a valid List!");
    return NULL;
  }

  if (!p_data)
  {
    DS_LIB_ERR("ds_list_delete_head: no variabe to save data from node to be deleted!");
    return l;
  }

  return ds_list_delete_node(l, l->head, p_data);
}

List ds_list_delete_tail(List l, void **p_data)
{
  if (!l)
  {
    DS_LIB_ERR("ds_list_delete_tail: supplied argument 1 is not a valid List!");
    return NULL;
  }

  if (!p_data)
  {
    DS_LIB_ERR("ds_list_delete_tail: no variabe to save data from node to be deleted!");
    return l;
  }

  return ds_list_delete_node(l, l->tail, p_data);
}

List ds_list_update_node(List l, LNode node, void *p_new_data, void **p_old_data)
{
  LNode dest;

  if (!l)
  {
    DS_LIB_ERR("ds_list_update_node: supplied argument 1 is not a valid List!");
    return NULL;
  }

  if (!node)
  {
    DS_LIB_ERR("ds_list_update_node: no node passed to update!");
    return l;
  }

  if (!p_new_data)
  {
    DS_LIB_ERR("ds_list_update_node: no data passed to update!");
    return l;
  }

  if (!p_old_data)
  {
    DS_LIB_ERR("ds_list_update_node: no variable passed to save data from updated node!");
    return l;
  }

  *p_old_data = node->data;
  node->data = p_new_data;

  return l;
}

unsigned int ds_list_count(List l)
{
  if (!l)
  {
    DS_LIB_ERR("ds_list_count: supplied argument 1 is not a valid List!");
    return -1;
  }

  return l->count;
}

unsigned int ds_list_traverse_forward(List l, LNode node)
{
  LNode crawl;
  unsigned int count;

  if (!l)
  {
    DS_LIB_ERR("ds_list_traverse_forward: supplied argument 1 is not a valid List!");
    return -1;
  }

  if (l->cb != NULL)
  {
    if (node != NULL)
    {
      crawl = node;
    }
    else
    {
      crawl = l->head;
    }
    for (count = 0; crawl != NULL; crawl = crawl->next, count++)
    {
      int retval = l->cb(l, crawl->data, l->cb_data);
      if (retval == -1)
      {
        break;
      }
    }
  }

  return count;
}

unsigned int ds_list_traverse_reverse(List l, LNode node)
{
  LNode crawl;
  unsigned int count;

  if (!l)
  {
    DS_LIB_ERR("ds_list_traverse_reverse: supplied argument 1 is not a valid List!");
    return -1;
  }

  if (l->cb != NULL)
  {
    if (node != NULL)
    {
      crawl = node;
    }
    else
    {
      crawl = l->tail;
    }
    for (count = 0; crawl != NULL; crawl = crawl->prev, count++)
    {
      int retval = l->cb(l, crawl->data, l->cb_data);
      if (retval == -1)
      {
        break;
      }
    }
  }

  return count;
}

LNode ds_list_get_head(List l)
{
  if (!l)
  {
    DS_LIB_ERR("ds_list_get_head_node: supplied argument 1 is not a valid List!");
    return NULL;
  }

  return l->head;
}

LNode ds_list_get_tail(List l)
{
  if (!l)
  {
    DS_LIB_ERR("ds_list_get_tail_node: supplied argument 1 is not a valid List!");
    return NULL;
  }

  return l->tail;
}

LNode ds_list_get_next_node(List l, LNode node)
{
  if (!l)
  {
    DS_LIB_ERR("ds_list_get_next_node: supplied argument 1 is not a valid List!");
  }
  else if (!node)
  {
    DS_LIB_ERR("ds_list_get_next_node: no valid node to get next from!");
  }
  else if (node->next != NULL)
  {
    return node->next;
  }

  return NULL;
}

LNode ds_list_get_prev_node(List l, LNode node)
{
  if (!l)
  {
    DS_LIB_ERR("ds_list_get_prev_node: supplied argument 1 is not a valid List!");
  }
  else if (!node)
  {
    DS_LIB_ERR("ds_list_get_prev_node: no valid node to get next from!");
  }
  else if (node->prev != NULL)
  {
    return node->prev;
  }

  return NULL;
}

void ds_list_get_data(LNode node, void **p_data)
{
  if (!node)
  {
    DS_LIB_ERR("ds_list_get_data: supplied argument 1 is not a valid LNode!");
    return;
  }

  if (!p_data)
  {
    DS_LIB_ERR("ds_list_get_data: no variable passed to get data!");
    return;
  }

  *p_data = node->data;
}

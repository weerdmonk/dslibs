
/*
 * dslibs v0.1
 * queue implementation v0.1
 * weerdmonk Dec2014
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <error.h>
#include <list.h>
#include <queue.h>

#define DS_QUEUE_ALLOC_SIZE		sizeof(struct Queue_t)

struct Queue_t {
  List l;
  unsigned char is_empty;
  unsigned int length;
};

Queue ds_queue_new(void)
{
  Queue q = calloc(1, DS_QUEUE_ALLOC_SIZE);
  if (!q)
  {
    DS_C_ERR(__func__);
    return NULL;
  }

  q->l = ds_list_new(NULL);
  if (!q->l)
  {
    DS_LIB_ERR("ds_queue_new: could not create queue!");
    free(q);
    return NULL;
  }

  return q;
}

void ds_queue_delete(Queue q)
{
  if (!q)
  {
    DS_LIB_ERR("ds_queue_enqueue: supplied argument 1 is not a valid Queue!");
    return;
  }

  if (q->l != NULL)
  {
    ds_list_delete(q->l, 1);
  }

  free(q);
}

unsigned char ds_queue_empty_check(Queue q)
{
  return (q->is_empty = (q->length == 0));
}

Queue ds_queue_enque(Queue q, void *data)
{
  if (!q)
  {
    DS_LIB_ERR("ds_queue_enqueue: supplied argument 1 is not a valid Queue!");
    return NULL;
  }

  if (!data)
  {
    DS_LIB_ERR("ds_queue_enque: no data to enque!");
    return q;
  }

  ds_list_prepend(q->l, data);
  q->length++;

  return q;
}

void *ds_queue_deque(Queue q)
{
  void *p_data;

  if (!q)
  {
    DS_LIB_ERR("ds_queue_deque: supplied argument 1 is not a valid Queue!");
    return NULL;
  }

  if (q->is_empty)
  {
    DS_LIB_INFO("ds_queue_deque: Queue is empty!");
    return NULL;
  }

  ds_list_delete_tail(q->l, &p_data);
  q->length--;
  ds_queue_empty_check(q);

  return p_data;
}

void *ds_queue_peek(Queue q)
{
  void *p_data;

  if (!q)
  {
    DS_LIB_ERR("ds_queue_peek: supplied argument 1 is not a valid Queue!");
    return NULL;
  }

  if (q->is_empty)
  {
    DS_LIB_INFO("ds_queue_peek: Queue is empty!");
    return NULL;
  }

  ds_list_get_data(ds_list_get_tail(q->l), &p_data);

  return p_data;
}

unsigned int ds_queue_get_length(Queue q)
{
  if (!q)
  {
    DS_LIB_ERR("ds_queue_get_length: supplied argument 1 is not a valid Queue!");
    return -1;
  }

  return q->length;
}

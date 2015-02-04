
/*
 * dslibs v0.1
 * queue implementation v0.1
 * weerdmonk Dec2014
 *
 */

/* TODO:
 * improve error handling macros
 * make fucntions static
 * optimize design
 */

#include <queue.h>

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
		free(q);
		return NULL;
		
	}

	q->qstart = q->qend = q->l->head;
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

   q->length++;
   ds_list_prepend(q->l, data);
	q->qend = q->l->head;
   if (!q->qstart) q->qstart = q->l->tail;

	return q;
}

Queue ds_queue_enque_val(Queue q, unsigned int data)
{
	if (!q)
	{
		DS_LIB_ERR("ds_queue_enque_val: supplied argument 1 is not a valid Queue!");
		return NULL;
	}

   q->length++;
   ds_list_prepend_val(q->l, data);
	q->qend = q->l->head;
   if (!q->qstart) q->qstart = q->l->tail;

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

   ds_list_delete_pos(q->l, &p_data, q->length - 1);
   q->length--;
	_ds_queue_empty_check(q);

	return p_data;
}

unsigned int ds_queue_deque_val(Queue q)
{
	unsigned int data;

	if (!q)
	{
		DS_LIB_ERR("ds_queue_deque_val: supplied argument 1 is not a valid Queue!");
		return 0xFFFFFFFF;
	}

	if (q->is_empty)
	{
		DS_LIB_INFO("ds_queue_deque_val: Queue is empty!");
		return 0xFFFFFFFF;
	}

   ds_list_delete_pos_val(q->l, &data, q->length - 1);
   q->length--;
   _ds_queue_empty_check(q);

	return data;
}


/*
 * dslibs v0.1
 * queue implementation v0.1
 * weerdmonk Dec2014
 *
 */

#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <error.h>
#include <list.h>

#define DS_QUEUE_ALLOC_SIZE		sizeof(struct _Queue)

typedef struct _Queue *Queue;

struct _Queue {
	List l;
	LNode qstart;
	LNode qend;
	unsigned char is_empty;
   int length;
};

static inline unsigned char _ds_queue_empty_check(Queue q)
{
	return (q->is_empty = (q->length == 0));
}

Queue ds_queue_new(void);

Queue ds_queue_enque(Queue q, void *data);

Queue ds_queue_enque_val(Queue q, unsigned int data);

void *ds_queue_deque(Queue q);

unsigned int ds_queue_deque_val(Queue q);

#endif /* QUEUE_H */

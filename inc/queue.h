
/*
 * dslibs v0.1
 * queue implementation v0.1
 * weerdmonk Dec2014
 *
 */

#ifndef QUEUE_H
#define QUEUE_H

typedef struct Queue_t *Queue;

Queue ds_queue_new(void);

void ds_queue_delete(Queue q);

unsigned char ds_queue_empty_check(Queue q);

Queue ds_queue_enque(Queue q, void *data);

void *ds_queue_deque(Queue q);

void *ds_queue_peek(Queue q);

unsigned int ds_queue_get_length(Queue q);

#endif /* QUEUE_H */

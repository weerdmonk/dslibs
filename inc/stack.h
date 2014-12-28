
/*
 * dslibs v0.1
 * stack implementation v0.1
 * weerdmonk Dec2014
 *
 */

#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#include <error.h>

#define DS_STACK_ALLOC_SIZE		sizeof(struct _Stack)
#define DS_STACK_NODE_SIZE		sizeof(void*)

typedef struct _Stack *Stack;

struct _Stack {
	size_t capacity;
	unsigned char is_full;
	void **sptr;
	void **top;
};

static inline unsigned char _ds_stack_full_check(Stack s)
{
	return (s->is_full = ((s->top - s->sptr) == s->capacity));
}

Stack ds_stack_new(size_t capacity);

Stack ds_stack_spush(Stack s, void *data);

void *ds_stack_pop(Stack s);

#endif /* STACK_H */

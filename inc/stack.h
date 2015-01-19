
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
#include <list.h>

#define DS_STACK_ALLOC_SIZE		sizeof(struct _Stack)

typedef struct _Stack *Stack;

struct _Stack {
	List l;
	LNode sptr;
	LNode top;
	unsigned char is_empty;
   int depth;
};

static inline unsigned char _ds_stack_empty_check(Stack s)
{
	return (s->is_empty = (s->depth == 0));
}

Stack ds_stack_new(void);

Stack ds_stack_push(Stack s, void *data);

Stack ds_stack_push_val(Stack s, unsigned int data);

void *ds_stack_pop(Stack s);

unsigned int ds_stack_pop_val(Stack s);

#endif /* STACK_H */

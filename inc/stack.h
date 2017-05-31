
/*
 * dslibs v0.1
 * stack implementation v0.1
 * weerdmonk Dec2014
 *
 */

#ifndef STACK_H
#define STACK_H

typedef struct Stack_t *Stack;

Stack ds_stack_new(void);

void ds_stack_delete(Stack s);

unsigned char ds_stack_empty_check(Stack s);

Stack ds_stack_push(Stack s, void *data);

void *ds_stack_pop(Stack s);

void *ds_stack_peek(Stack s);

unsigned int ds_stack_get_depth(Stack s);

#endif /* STACK_H */

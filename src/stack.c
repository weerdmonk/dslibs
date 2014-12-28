
/*
 * dslibs v0.1
 * stack implementation v0.1
 * weerdmonk Dec2014
 *
 */

/* TODO:
 * improve error handling macros
 * make fucntions static 
 * optimize design
 */

#include <stack.h>

Stack ds_stack_new(size_t capacity)
{
	if (capacity < 0)
	{
		DS_LIB_ERR("ds_stack_new : capacity should be non-negative!");
		return NULL;
	}

	Stack s = calloc(1, DS_STACK_ALLOC_SIZE);
	if (!s)
	{
		DS_C_ERR(__func__);
		return NULL;
	}

	s->capacity = capacity;

	s->sptr = calloc(s->capacity, DS_STACK_NODE_SIZE);
	if (!s->sptr)
	{
		DS_C_ERR(__func__);
		free(s);
		return NULL;
		
	}

	s->top = s->sptr;
}

Stack ds_stack_push(Stack s, void *data)
{
	if (!s)
	{
		DS_LIB_ERR("ds_stack_push: supplied argument 1 is not a valid Stack!");
		return NULL;
	}

	if (!data)
	{
		DS_LIB_ERR("ds_stack_push: no data to push!");
		return s;
	}

	if (s->is_full)
	{
		DS_LIB_INFO("ds_stack_push: Stack is full already!");
		return s;
	}

	*(++s->top) = data;

	_ds_stack_full_check(s);
	
	return s;
}

void *ds_stack_pop(Stack s)
{
	if (!s)
	{
		DS_LIB_ERR("ds_stack_push: supplied argument 1 is not a valid Stack!");
		return NULL;
	}

	if (s->top == s->sptr)
	{
		DS_LIB_INFO("ds_stack_push: Stack is empty!");
		return NULL;
	}

	void *tmp = *(s->top--);

	return tmp;
}


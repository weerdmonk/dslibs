
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

Stack ds_stack_new(void)
{

	Stack s = calloc(1, DS_STACK_ALLOC_SIZE);
	if (!s)
	{
		DS_C_ERR(__func__);
		return NULL;
	}

   s->l = ds_list_new(NULL);
	if (!s->l)
	{
		free(s);
		return NULL;
		
	}

	s->top = s->sptr = s->l->head;
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

   s->depth++;
   ds_list_append(s->l, data);
	s->top = s->l->tail;
   if (!s->sptr) s->sptr = s->l->head;

	return s;
}

Stack ds_stack_push_val(Stack s, unsigned int data)
{
	if (!s)
	{
		DS_LIB_ERR("ds_stack_push_val: supplied argument 1 is not a valid Stack!");
		return NULL;
	}

   s->depth++;
   ds_list_append_val(s->l, data);
	s->top = s->l->tail;
   if (!s->sptr) s->sptr = s->l->head;

	return s;
}

void *ds_stack_pop(Stack s)
{
   void *p_data;

	if (!s)
	{
		DS_LIB_ERR("ds_stack_pop: supplied argument 1 is not a valid Stack!");
		return NULL;
	}

	if (s->is_empty)
	{
		DS_LIB_INFO("ds_stack_pop: Stack is empty!");
		return s;
	}

   ds_list_delete_pos(s->l, &p_data, s->depth);
   s->depth--;
	_ds_stack_empty_check(s);

	return p_data;
}

unsigned int ds_stack_pop_val(Stack s)
{
	unsigned int data;

	if (!s)
	{
		DS_LIB_ERR("ds_stack_pop_val: supplied argument 1 is not a valid Stack!");
		return 0xFFFFFFFF;
	}

	if (s->is_empty)
	{
		DS_LIB_INFO("ds_stack_pop_val: Stack is empty!");
		return 0xFFFFFFFF;
	}

   ds_list_delete_pos_val(s->l, &data, s->depth - 1);
   s->depth--;
   _ds_stack_empty_check(s);

	return data;
}

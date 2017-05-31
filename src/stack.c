
/*
 * dslibs v0.1
 * stack implementation v0.1
 * weerdmonk Dec2014
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <error.h>
#include <list.h>
#include <stack.h>

#define DS_STACK_ALLOC_SIZE		sizeof(struct Stack_t)

struct Stack_t {
  List l;
  unsigned char is_empty;
  unsigned int depth;
};

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

  return s;
}

void ds_stack_delete(Stack s)
{
  if (!s)
  {
    DS_LIB_ERR("ds_stack_push: supplied argument 1 is not a valid Stack!");
    return;
  }

  if (s->l != NULL)
  {
    ds_list_delete(s->l, 0);
  }

  free(s);
}

unsigned char ds_stack_empty_check(Stack s)
{
  return (s->is_empty = (s->depth == 0));
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
    return NULL;
  }

  ds_list_delete_tail(s->l, &p_data);
  s->depth--;
  ds_stack_empty_check(s);

  return p_data;
}

void *ds_stack_peek(Stack s)
{
  void *p_data;

  if (!s)
  {
    DS_LIB_ERR("ds_stack_peek: supplied argument 1 is not a valid Stack!");
    return NULL;
  }

  if (s->is_empty)
  {
    DS_LIB_INFO("ds_stack_peek: Stack is empty!");
    return NULL;
  }

  ds_list_get_data(ds_list_get_tail(s->l), &p_data);

  return p_data;
}

unsigned int ds_stack_get_depth(Stack s)
{
  if (!s)
  {
    DS_LIB_ERR("ds_get_depth: supplied argument 1 is not a valid Stack!");
    return -1;
  }

  return s->depth;
}

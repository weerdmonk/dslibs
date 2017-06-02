
/*
 * dslibs v0.1
 * stack example v0.1
 * weerdmonk Dec2014
 *
 */

#include <stdio.h>
#include <stack.h>

typedef struct
{
  int val;
} integer_data_t;

int main(void)
{
  integer_data_t int_data[6], *p_pop_data;
  Stack st = ds_stack_new();

  printf("Pushing data on to the stack:\n");

  int_data[0].val = 10;
  ds_stack_push(st, &int_data[0]);
  printf("Stack depth is %d\n", ds_stack_get_depth(st));
  int_data[1].val = 20;
  ds_stack_push(st, &int_data[1]);
  printf("Stack depth is %d\n", ds_stack_get_depth(st));
  int_data[2].val = 30;
  ds_stack_push(st, &int_data[2]);
  printf("Stack depth is %d\n", ds_stack_get_depth(st));
  int_data[3].val = 40;
  ds_stack_push(st, &int_data[3]);
  printf("Stack depth is %d\n", ds_stack_get_depth(st));
  int_data[4].val = 50;
  ds_stack_push(st, &int_data[4]);
  printf("Stack depth is %d\n", ds_stack_get_depth(st));
  int_data[5].val = 60;
  ds_stack_push(st, &int_data[5]);
  printf("Stack depth is %d\n", ds_stack_get_depth(st));

  printf("*******************\n");

  p_pop_data = ds_stack_peek(st);
  printf("Element which will be popped first is %d\n", p_pop_data->val);

  printf("**********************\n");

  printf("Popping data off the stack:\n");

  p_pop_data = ds_stack_pop(st);
  if (p_pop_data != NULL)
  {
    printf("Popped data is %d\n", p_pop_data->val );
  }
  p_pop_data = ds_stack_pop(st);
  if (p_pop_data != NULL)
  {
    printf("Popped data is %d\n", p_pop_data->val );
  }
  p_pop_data = ds_stack_pop(st);
  if (p_pop_data != NULL)
  {
    printf("Popped data is %d\n", p_pop_data->val );
  }
  p_pop_data = ds_stack_pop(st);
  if (p_pop_data != NULL)
  {
    printf("Popped data is %d\n", p_pop_data->val );
  }
  p_pop_data = ds_stack_pop(st);
  if (p_pop_data != NULL)
  {
    printf("Popped data is %d\n", p_pop_data->val );
  }
  p_pop_data = ds_stack_pop(st);
  if (p_pop_data != NULL)
  {
    printf("Popped data is %d\n", p_pop_data->val );
  }
  p_pop_data = ds_stack_pop(st);
  if (p_pop_data != NULL)
  {
    printf("Popped data is %d\n", p_pop_data->val );
  }

  ds_stack_delete(st);

  return 0;
}

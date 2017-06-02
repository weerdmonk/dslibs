
/*
 * dslibs v0.1
 * queue example v0.1
 * weerdmonk Dec2014
 *
 */

#include <stdio.h>
#include <queue.h>

typedef struct
{
  int val;
} integer_data_t;

int main(void)
{
  integer_data_t int_data[6], *p_deque_data;
  Queue q = ds_queue_new();

  printf("Enqueing data to queue:\n");

  int_data[0].val = 10;
  ds_queue_enque(q, &int_data[0]);
  printf("Queue length is %d\n", ds_queue_get_length(q));
  int_data[1].val = 20;
  ds_queue_enque(q, &int_data[1]);
  printf("Queue length is %d\n", ds_queue_get_length(q));
  int_data[2].val = 30;
  ds_queue_enque(q, &int_data[2]);
  printf("Queue length is %d\n", ds_queue_get_length(q));
  int_data[3].val = 40;
  ds_queue_enque(q, &int_data[3]);
  printf("Queue length is %d\n", ds_queue_get_length(q));
  int_data[4].val = 50;
  ds_queue_enque(q, &int_data[4]);
  printf("Queue length is %d\n", ds_queue_get_length(q));
  int_data[5].val = 60;
  ds_queue_enque(q, &int_data[5]);
  printf("Queue length is %d\n", ds_queue_get_length(q));

  printf("**********************\n");

  p_deque_data = ds_queue_peek(q);
  printf("Element which will be dequed first is %d\n", p_deque_data->val);

  printf("**********************\n");

  p_deque_data = ds_queue_deque(q);
  if (p_deque_data != NULL)
  {
    printf("Dequeed data from queue is %d\n", p_deque_data->val);
  }
  p_deque_data = ds_queue_deque(q);
  if (p_deque_data != NULL)
  {
    printf("Dequeed data from queue is %d\n", p_deque_data->val);
  }
  p_deque_data = ds_queue_deque(q);
  if (p_deque_data != NULL)
  {
    printf("Dequeed data from queue is %d\n", p_deque_data->val);
  }
  p_deque_data = ds_queue_deque(q);
  if (p_deque_data != NULL)
  {
    printf("Dequeed data from queue is %d\n", p_deque_data->val);
  }
  p_deque_data = ds_queue_deque(q);
  if (p_deque_data != NULL)
  {
    printf("Dequeed data from queue is %d\n", p_deque_data->val);
  }
  p_deque_data = ds_queue_deque(q);
  if (p_deque_data != NULL)
  {
    printf("Dequeed data from queue is %d\n", p_deque_data->val);
  }
  p_deque_data = ds_queue_deque(q);
  if (p_deque_data != NULL)
  {
    printf("Dequeed data from queue is %d\n", p_deque_data->val);
  }

  ds_queue_delete(q);

  return 0;
}

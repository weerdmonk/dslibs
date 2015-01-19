
/*
 * dslibs v0.1
 * queue example v0.1
 * weerdmonk Dec2014
 *
 */

#include <queue.h>

int main(void)
{
   Queue q = ds_queue_new();
   printf("queue occupancy = %d\n", q->length);
   ds_queue_enque_val(q, 10);
   printf("queue occupancy = %d\n", q->length);
   ds_queue_enque_val(q, 20);
   printf("queue occupancy = %d\n", q->length);
   ds_queue_enque_val(q, 30);
   printf("queue occupancy = %d\n", q->length);
   ds_queue_enque_val(q, 40);
   printf("queue occupancy = %d\n", q->length);
   ds_queue_enque_val(q, 50);
   printf("queue occupancy = %d\n", q->length);
   ds_queue_enque_val(q, 60);
   printf("queue occupancy = %d\n", q->length);
   printf("dequeed data = %u\n", ds_queue_deque_val(q));
   printf("dequeed data = %u\n", ds_queue_deque_val(q));
   printf("dequeed data = %u\n", ds_queue_deque_val(q));
   printf("dequeed data = %u\n", ds_queue_deque_val(q));
   printf("dequeed data = %u\n", ds_queue_deque_val(q));
   printf("dequeed data = %u\n", ds_queue_deque_val(q));
   printf("dequeed data = %u\n", ds_queue_deque_val(q));

   return 0;
}


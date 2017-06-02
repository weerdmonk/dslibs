
/*
 * dslibs v0.1
 * list example v0.1
 * weerdmonk Dec2014
 *
 */

#include <stdio.h>
#include <list.h>

typedef struct
{
  int val;
} integer_data_t;

int print_list_node_data(List l, void *node_data, void *cb_data)
{
  printf("Data of node is %d\n", ((integer_data_t*)(node_data))->val);
  return 0;
}

int main(void)
{
   LNode node;
   integer_data_t int_data[10],
                  insert_data,
                  update_data,
                  *p_data = NULL;
   List l = ds_list_new(NULL);

   ds_list_callback_add(l, print_list_node_data, NULL);

   int_data[0].val = 10;
   ds_list_append(l, &int_data[0]);
   int_data[1].val = 20;
   ds_list_append(l, &int_data[1]);
   int_data[2].val = 30;
   ds_list_append(l, &int_data[2]);
   int_data[3].val = 40;
   ds_list_append(l, &int_data[3]);
   int_data[4].val = 50;
   ds_list_append(l, &int_data[4]);
   int_data[5].val = 100;
   ds_list_prepend(l, &int_data[5]);
   int_data[6].val = 200;
   ds_list_prepend(l, &int_data[6]);
   int_data[7].val = 300;
   ds_list_prepend(l, &int_data[7]);
   int_data[8].val = 400;
   ds_list_prepend(l, &int_data[8]);
   int_data[9].val = 500;
   ds_list_prepend(l, &int_data[9]);

   printf("Printing integer data from list:\n");

   ds_list_traverse_forward(l, NULL);

   printf("************************\n");

   printf("Printing integer data from list in reverse order:\n");

   ds_list_traverse_reverse(l, NULL);

   printf("************************\n");

   printf("Number of nodes in the list is %d\n", ds_list_count(l));

   printf("************************\n");

   node = ds_list_search(l, &int_data[6]);
   if ( node != NULL )
   {
     insert_data.val = 23;
     ds_list_insert_after(l, node, &insert_data);
     ds_list_get_data(node, (void*)&p_data);
     if (p_data != NULL)
     {
       printf("Inserted value %d after value %d\n", insert_data.val, p_data->val);
     }
   }

   printf("************************\n");

   node = ds_list_search(l, &int_data[2]);
   if ( node != NULL )
   {
     ds_list_delete_node(l, node, (void*)&p_data);
   }
   if (p_data != NULL)
   {
     printf("Data from node deleted is %d\n", p_data->val);
   }

   printf("************************\n");

   node =  ds_list_search(l, &int_data[0]);
   if ( node != NULL )
   {
     update_data.val = 72;
     ds_list_update_node(l, node, &update_data, (void*)&p_data);
   }
   if (p_data != NULL)
   {
     printf("Updated value from %d to %d\n", int_data[0].val, update_data.val);
   }

   printf("************************\n");

   ds_list_delete_tail(l, (void*)&p_data);

   printf("Deleted tail node, data from node is %d\n", p_data->val);

   printf("************************\n");

   printf("Printing integer data from list:\n");

   ds_list_traverse_forward(l, NULL);

   printf("************************\n");

   printf("Number of nodes in the list is %d\n", ds_list_count(l));

   printf("************************\n");
   printf("************************\n");

   node = ds_list_get_head(l);
   ds_list_get_data(node, (void*)&p_data);
   printf("Head iterator gives data %d\n", p_data->val);

   ds_list_delete(l, 0);

   return 0;
}

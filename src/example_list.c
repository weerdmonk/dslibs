
/*
 * dslibs v0.1
 * list example v0.1
 * weerdmonk Dec2014
 *
 */

 #include <list.h>

int main(void)
{
   LNode ln;
   int i, j;

   List l = ds_list_new(NULL);
   ds_list_append_val(l, 10);
   ds_list_append_val(l, 20);
   ds_list_append_val(l, 30);
   ds_list_append_val(l, 40);
   ds_list_append_val(l, 50);

   ds_list_prepend_val(l, 100);
   ds_list_prepend_val(l, 200);
   ds_list_prepend_val(l, 300);
   ds_list_prepend_val(l, 400);

//   ds_list_insert_pos(l, 23, 2);

//   ds_list_delete_pos(l, &j, 4);

//   ds_list_update_pos(l, 72,  &i, 6);

   for(ln=l->head;ln!=NULL;ln=ln->next)
   {
      printf("list node data = %d\n", *(int*)ln->data);
   }

//   printf("data from deleted node is = %d\n", j);

//   printf("data from updated node is = %d\n", i);

   ds_list_search(l, 23, &i);

   printf("%d is at pos = %d\n", 23, i);

   printf("number of nodes is %d\n", ds_list_count(l));

   return 0;
}

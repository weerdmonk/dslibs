
/*
 * dslibs v0.1
 * list example v0.1
 * weerdmonk Dec2014
 *
 */

 #include <list.h>

int main(void)
{
   int i;

   List l = ds_list_new(10);
   ds_list_append(l, 20);
   ds_list_append(l, 30);
   ds_list_append(l, 40);
   ds_list_append(l, 50);

   ds_list_prepend(l, 100);
   ds_list_prepend(l, 200);
   ds_list_prepend(l, 300);
   ds_list_prepend(l, 400);

   ds_list_insert_pos(l, 23, 9);
   ds_list_insert_pos(l, 62, 18);

   ds_list_delete_pos(l, &i, 1);

   LNode ln;
   for(ln=l->head;ln!=NULL;ln=ln->next)
   {
      printf("list node data = %d\n", (int)ln->data);
   }

   ds_list_search(l, 100, &i);

   printf("%d is at pos = %d\n", 100, i);

   return 0;
}

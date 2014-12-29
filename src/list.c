
/*
 * dslibs v0.1
 * list implementation v0.1
 * weerdmonk Dec2014
 *
 */

/* TODO:
 * improve error handling macros
 * make fucntions static
 * optimize design
 */

#include <list.h>

LNode _ds_list_node_new(void *data)
{
   LNode ln = calloc(1, DS_LIST_NODE_SIZE);
   if (!ln)
   {
      DS_C_ERR(__func__);
      return NULL;
   }

   if (!data)
   {
      DS_LIB_ERR("_ds_list_node_new: no data to supplied!");
      free(ln);
      return NULL;
   }

   ln->data = data;

   return ln;
}

List ds_list_new(void *data)
{
	List l = calloc(1, DS_LIST_ALLOC_SIZE);
	if (!l)
	{
		DS_C_ERR(__func__);
		return NULL;
	}

	l->head = _ds_list_node_new(data);
	if (!l->head)
	{
		DS_LIB_ERR("ds_list_new: failed to create new list node!");
		free(l);
		return NULL;
		
	}

   l->tail = l->head;

   return l;
}

List ds_list_append(List l, void *data)
{
	if (!l)
	{
		DS_LIB_ERR("ds_list_append: supplied argument 1 is not a valid List!");
		return NULL;
	}

	if (!data)
	{
		DS_LIB_ERR("ds_list_append: no data to append!");
		return l;
	}

   LNode ln = _ds_list_node_new(data);
   if (!ln)
   {
		DS_LIB_ERR("ds_list_append: failed to create new list node!");
      return l;
   }

   l->tail->next = ln;
   l->tail = ln;

	return l;
}

List ds_list_prepend(List l, void *data)
{
	if (!l)
	{
		DS_LIB_ERR("ds_list_prepend: supplied argument 1 is not a valid List!");
		return NULL;
	}

	if (!data)
	{
		DS_LIB_ERR("ds_list_prepend: no data to prepend!");
		return l;
	}

   LNode ln = _ds_list_node_new(data);
   if (!ln)
   {
      DS_LIB_ERR("ds_list_prepend: failed to create new list node!");
      return l;
   }

   ln->next = l->head;
   l->head = ln;

	return l;
}

List ds_list_insert_pos(List l, void *data, int pos)
{
	if (!l)
	{
		DS_LIB_ERR("ds_list_insert_pos: supplied argument 1 is not a valid List!");
		return NULL;
	}

	if (!data)
	{
		DS_LIB_ERR("ds_list_insert_pos: no data to prepend!");
		return l;
	}

   LNode ln;
   int i = 0;
   for(ln=l->head;
}

//this is to test list only
int main(void)
{
   List l = ds_list_new(10);
   ds_list_append(l, 20);
   ds_list_append(l, 30);
   ds_list_append(l, 40);
   ds_list_append(l, 50);

   ds_list_prepend(l, 100);
   ds_list_prepend(l, 200);
   ds_list_prepend(l, 300);
   ds_list_prepend(l, 400);

   LNode ln;
   for(ln=l->head;ln!=NULL;ln=ln->next)
   {
      printf("list node data = %d\n", (int)ln->data);
   }

   return 0;
}

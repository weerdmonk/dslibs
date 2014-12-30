
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
   LNode dest, tmp;
   int _pos;

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

   tmp = _ds_list_node_new(data);
   if (!tmp)
   {
      DS_C_ERR(__func__);
      return l;
   }

   if (!pos)
   {
      tmp->next = l->head;
      l->head = tmp;

      return l;
   }
   else
   {
      for(dest = l->head, _pos = 1; dest != NULL; dest = dest->next)
      {
         if (_pos++ == pos)
         {
            tmp->next = dest->next;
            dest->next = tmp;
            break;
         }
      }
   }

   return l;
}

List ds_list_delete_pos(List l, void **data, int pos)
{
   LNode prev, tmp;
   int _pos;

	if (!l)
	{
		DS_LIB_ERR("ds_list_delete_pos: supplied argument 1 is not a valid List!");
		return NULL;
	}

	if (!data)
	{
		DS_LIB_ERR("ds_list_delete_pos: no variabe to save data from node to be deleted!");
		return l;
	}

   if (!pos)
   {
      tmp = l->head;
      l->head = tmp->next;
      *data = tmp->data;
      free(tmp);
      return l;
   }
   else
   {
      for(prev = l->head, _pos = 1; prev->next != NULL; prev = prev->next)
      {
         if (_pos++ == pos)
         {
            tmp = prev->next;
            prev->next = tmp->next;
            *data = tmp->data;
            free(tmp);
            break;
         }
      }
   }

   return l;
}

int ds_list_search(List l, void *data)
{
   LNode dest;
   int _pos;

	if (!l)
	{
		DS_LIB_ERR("ds_list_search: supplied argument 1 is not a valid List!");
		return -1;
	}

	if (!data)
	{
		DS_LIB_ERR("ds_list_search: no data to search for!");
		return -1;
	}

   for(dest = l->head, _pos = 0; dest != NULL; dest = dest->next)
   {
      if (dest->data == data) return _pos;
      _pos++;
   }

   return -1;
}

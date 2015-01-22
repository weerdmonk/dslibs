
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
 * implement memory clean up code
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

	if (data)
   {
      l->head = _ds_list_node_new(data);
	   if (!l->head)
	   {
		   DS_LIB_ERR("ds_list_new: failed to create new list node!");
		   free(l);
		   return NULL;
		
	   }
   }
   else
      l->head = NULL;

   l->tail = l->head;

   return l;
}

void ds_list_del(List l)
{
   LNode ln, tmp;

   if (!l)
   {
      DS_LIB_ERR("ds_list_del: supplied argument 1 is not a valid List!");
      return;
   }

   if (!l->head) return;

   for(ln = l->head; ln != NULL; )
   {
      tmp = ln;
      if (tmp->data) free(tmp->data);
      ln = ln->next;
      l->head = ln;
      free(tmp);
   }

   l->tail = l->head;
}

void ds_list_free(List *p_l)
{
   if (!*p_l)
   {
      DS_LIB_ERR("ds_list_free: supplied argument 1 is not a valid List!");
      return;
   }

   ds_list_del(*p_l);

   free(*p_l);
   *p_l = NULL;
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

   if (l->head == NULL)
   {
      l->head = ln;
      l->tail = l->head;
   }
   else
   {
      l->tail->next = ln;
      l->tail = ln;
   }

	return l;
}

List ds_list_append_val(List l, unsigned int data)
{
	if (!l)
	{
		DS_LIB_ERR("ds_list_append_val: supplied argument 1 is not a valid List!");
		return NULL;
	}

   void *p_data = malloc(sizeof(int));
   if (!p_data)
   {
      DS_C_ERR(__func__);
      return l;
   }

   *(int*)p_data = (int)data;

   LNode ln = _ds_list_node_new(p_data);
   if (!ln)
   {
      free(p_data);
		DS_LIB_ERR("ds_list_append_val: failed to create new list node!");
      return l;
   }


   if (l->head == NULL)
   {
      l->head = ln;
      l->tail = l->head;
   }
   else
   {
      l->tail->next = ln;
      l->tail = ln;
   }

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

   if (l->head == NULL)
   {
      l->head = ln;
      l->tail = l->head;
   }
   else
   {
      ln->next = l->head;
      l->head = ln;
   }


	return l;
}

List ds_list_prepend_val(List l, unsigned int data)
{
	if (!l)
	{
		DS_LIB_ERR("ds_list_prepend_val: supplied argument 1 is not a valid List!");
		return NULL;
	}

   void *p_data = malloc(sizeof(int));
   if (!p_data)
   {
      DS_C_ERR(__func__);
      return l;
   }

   *(int*)p_data = (int)data;

   LNode ln = _ds_list_node_new(p_data);
   if (!ln)
   {
      DS_LIB_ERR("ds_list_prepend_val: failed to create new list node!");
      return l;
   }

   if (l->head == NULL)
   {
      l->head = ln;
      l->tail = l->head;
   }
   else
   {
      ln->next = l->head;
      l->head = ln;
   }

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
      if (l->head == NULL) l->tail = tmp;
      l->head = tmp;

      return l;
   }
   else
   {
      for (dest = l->head, _pos = 1; dest != NULL; dest = dest->next)
      {
         if (_pos++ == pos)
         {
            tmp->next = dest->next;
            dest->next = tmp;
            if (dest == l->tail) l->tail = tmp;
            break;
         }
      }
   }

   return l;
}

List ds_list_insert_pos_val(List l, unsigned int data, int pos)
{
   LNode dest, tmp;
   int _pos;

   if (!l)
   {
       DS_LIB_ERR("ds_list_insert_pos_val: supplied argument 1 is not a valid List!");
       return NULL;
   }

   void *p_data = malloc(sizeof(int));
   if (!p_data)
   {
      DS_C_ERR(__func__);
      return l;
   }

   *(int*)p_data = data;

   tmp = _ds_list_node_new(p_data);
   if (!tmp)
   {
      DS_C_ERR(__func__);
      return l;
   }

   if (!pos)
   {
      tmp->next = l->head;
      if (l->head == NULL) l->tail = tmp;
      l->head = tmp;

      return l;
   }
   else
   {
      for (dest = l->head, _pos = 1; dest != NULL; dest = dest->next)
      {
         if (_pos++ == pos)
         {
            tmp->next = dest->next;
            dest->next = tmp;
            if (dest == l->tail) l->tail = tmp;
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
		DS_LIB_ERR("ds_lis_delete_pos: no variabe to save data from node to be deleted!");
		return l;
	}

   if (!pos)
   {
      tmp = l->head;
      l->head = tmp->next;
      *data = tmp->data;
      if (tmp == l->tail) l->tail = l->head;
      free(tmp);
      return l;
   }
   else
   {
      for (prev = l->head, _pos = 1; prev->next != NULL; prev = prev->next)
      {
         if (_pos++ == pos)
         {
            tmp = prev->next;
            prev->next = tmp->next;
            *data = tmp->data;
            if (tmp == l->tail) l->tail = prev;
            free(tmp);
            break;
         }
      }
   }

   return l;
}

List ds_list_delete_pos_val(List l, unsigned int *data, int pos)
{
   LNode prev, tmp;
   int _pos;

	if (!l)
	{
		DS_LIB_ERR("ds_list_delete_pos_val: supplied argument 1 is not a valid List!");
		return NULL;
	}

	if (!data)
	{
		DS_LIB_ERR("ds_lis_delete_pos_val: no variabe to save data from node to be deleted!");
		return l;
	}

   if (!pos)
   {
      tmp = l->head;
      l->head = tmp->next;
      *data = *(int*)tmp->data;
      if (tmp == l->tail) l->tail = l->head;
      free(tmp->data);
      free(tmp);
      return l;
   }
   else
   {
      for (prev = l->head, _pos = 1; prev->next != NULL; prev = prev->next)
      {
         if (_pos++ == pos)
         {
            tmp = prev->next;
            prev->next = tmp->next;
            *data = *(int*)tmp->data;
            // FIXME in case pos is equal to count of nodes handle it elegantly
            if (tmp == l->tail) l->tail = prev;
            free(tmp->data);
            free(tmp);
            break;
         }
      }
   }

   return l;
}

List ds_list_delete_start(List l, void **data)
{
   LNode tmp;

	if (!l)
	{
		DS_LIB_ERR("ds_list_delete_start: supplied argument 1 is not a valid List!");
		return NULL;
	}

	if (!data)
	{
		DS_LIB_ERR("ds_lis_delete_start: no variabe to save data from node to be deleted!");
		return l;
	}

   tmp = l->head;
   l->head = tmp->next;
   if (tmp == l->tail) l->tail = l->head;
   *data = tmp->data;
   free(tmp);

   return l;
}

List ds_list_delete_start_val(List l, unsigned int *data)
{
   LNode tmp;

	if (!l)
	{
		DS_LIB_ERR("ds_list_delete_start: supplied argument 1 is not a valid List!");
		return NULL;
	}

	if (!data)
	{
		DS_LIB_ERR("ds_lis_delete_start: no variabe to save data from node to be deleted!");
		return l;
	}

   tmp = l->head;
   l->head = tmp->next;
   *data = *(int*)tmp->data;
   if (tmp == l->tail) l->tail = l->head;
   free(tmp->data);
   free(tmp);

   return l;
}

List ds_list_delete_end(List l, void **data)
{
   LNode prev, tmp;

	if (!l)
	{
		DS_LIB_ERR("ds_list_delete_start: supplied argument 1 is not a valid List!");
		return NULL;
	}

	if (!data)
	{
		DS_LIB_ERR("ds_lis_delete_start: no variabe to save data from node to be deleted!");
		return l;
	}

   for (prev = l->head; prev->next != NULL; prev = prev->next)
   {
      if (prev->next == l->tail)
      {
         tmp = prev->next;
         prev->next = tmp->next;
         l->tail = prev;
         *data = tmp->data;
         free(tmp);
         return l;
      }
   }

   l->tail = prev->next;
   l->head = l->tail;
   *data = prev->data;
   free(prev);

   return l;
}

List ds_list_delete_end_val(List l, unsigned int *data)
{
   LNode prev, tmp;

	if (!l)
	{
		DS_LIB_ERR("ds_list_delete_start: supplied argument 1 is not a valid List!");
		return NULL;
	}

	if (!data)
	{
		DS_LIB_ERR("ds_lis_delete_start: no variabe to save data from node to be deleted!");
		return l;
	}

   for (prev = l->head; prev->next != NULL; prev = prev->next)
   {
      if (prev->next == l->tail)
      {
         tmp = prev->next;
         prev->next = tmp->next;
         l->tail = prev;
         *data = *(int*)tmp->data;
         free(tmp->data);
         free(tmp);
         return l;
      }
   }

   l->tail = prev->next;
   l->head = l->tail;
   *data = *(int*)prev->data;
   free(prev->data);
   free(prev);

   return l;
}

List ds_list_free_pos(List l, int pos)
{
   void *data;

   if (!l)
   {
      DS_LIB_ERR("ds_list_free_pos: supplied argument 1 is not a valid List!");
      return NULL;
   }

   ds_list_delete_pos(l, &data, pos);

   free(data);

   return l;
}

LNode ds_list_search(List l, void *data, int *pos)
{
   LNode dest;
   int _pos;

	if (!l)
	{
		DS_LIB_ERR("ds_list_search: supplied argument 1 is not a valid List!");
		return NULL;
	}

   for (dest = l->head, _pos = 0; dest != NULL; dest = dest->next, _pos++)
   {
      if (dest->data == data)
      {
         if (pos) *pos = _pos;
         return dest;
      }
   }

   if (pos) *pos = -1;
   return NULL;
}

LNode ds_list_search_val(List l, unsigned int data, int *pos)
{
   LNode dest;
   int _pos;

	if (!l)
	{
		DS_LIB_ERR("ds_list_search: supplied argument 1 is not a valid List!");
		return NULL;
	}

   for (dest = l->head, _pos = 0; dest != NULL; dest = dest->next, _pos++)
   {
      if (*(int*)dest->data == data)
      {
         if (pos) *pos = _pos;
         return dest;
      }
   }

   if (pos) *pos = -1;
   return NULL;
}

List ds_list_update_pos(List l, void *data_new, void **data_old, int pos)
{
	LNode dest;
	int _pos;

	if (!l)
	{
		DS_LIB_ERR("ds_list_update_pos: supplied argument 1 is not a valid List!");
		return NULL;
	}

	if (!data_old)
	{
		DS_LIB_ERR("ds_list_update_pos: no variable to save data from updated node!");
		return l;
	}

	if (!data_new)
	{
		DS_LIB_ERR("ds_list_update_pos: no data to update!");
		return l;
	}

   for (dest = l->head, _pos = 0; dest != NULL; dest = dest->next, _pos++)
   {
      if (_pos == pos)
      {
        *data_old= dest->data;
	dest->data = data_new;
	break;
      }
   }

	return l;
}

List ds_list_update_pos_val(List l, unsigned int data_new, unsigned int *data_old, int pos)
{
	LNode dest;
	int _pos;

	if (!l)
	{
		DS_LIB_ERR("ds_list_update_pos_val: supplied argument 1 is not a valid List!");
		return NULL;
	}

	if (!data_old)
	{
		DS_LIB_ERR("ds_list_update_pos_val: no variable to save data from updated node!");
		return l;
	}

   for (dest = l->head, _pos = 0; dest != NULL; dest = dest->next, _pos++)
   {
      if (_pos == pos)
      {
        *data_old= *(int*)dest->data;
	*(int*)dest->data = data_new;
	break;
      }
   }

	return l;
}

int ds_list_count(List l)
{
	LNode tmp;
	int cnt;

	if (!l)
	{
		DS_LIB_ERR("ds_list_update_pos: supplied argument 1 is not a valid List!");
		return -1;
	}

	for (tmp = l->head, cnt = 0; tmp != NULL; tmp = tmp->next, cnt++);

	return cnt;
}






















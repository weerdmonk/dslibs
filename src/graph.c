
/*
 * dslibs v0.1
 * graph implementation v0.1
 * weerdmonk Dec2014
 *
 */

/* TODO:
 * improve error handling macros
 * make fucntions static
 * optimize design
 * implement memory clean up code
 */

/* TODO
 * dynamic stack (predifined max capacity)
 * stack free API 
 * graph API to return list of adjacent vertices
 *
 */
#include <graph.h>

Graph ds_graph_new(int v, unsigned char directed)
{
   if (v < 0)
   {
      DS_LIB_ERR("ds_graph_new: invalid number of vertices!");
      return NULL;
   }

   Graph g = malloc(DS_GRAPH_ALLOC_SIZE);
   if (!g)
   {
      DS_C_ERR(__func__);
      return NULL;
   }

   g->v = v;
   g->directed = !!directed;

   g->adjlist = malloc(v * DS_LIST_ALLOC_SIZE);
   if (!g->adjlist)
   {
      free(g);
      return NULL;
   }

   return g;
}

Graph ds_graph_edge_add(Graph g, int src, int dest)
{
   if (!g)
   {
      DS_LIB_ERR("ds_graph_edge_add: supplied argument 1 is not a valid graph!");
      return NULL;
   }

   if ((src < 0) || (dest < 0))
   {
      DS_LIB_ERR("ds_graph_edge_add: invalid source and destination arguments!");
      return g;
   }

   int *_src, *_dest;

   _dest = malloc(sizeof(int));
   *_dest = dest;

   List l = &(g->adjlist[src]);
   ds_list_append(l, _dest);

   if (!g->directed)
   {
      _src = malloc(sizeof(int));
      *_src = src;
      l = &(g->adjlist[dest]);
      ds_list_append(l, _src);
   }

   return g;
}

Graph ds_graph_dfs(Graph g)
{
	int v = 0;

   if (!g)
   {
      DS_LIB_ERR("ds_graph_dfs: supplied argument 1 is not a valid graph!");
      return NULL;
   }

   Stack open = ds_stack_new(g->v);
   if (!open) return g;

   List visited = ds_list_new(NULL);
   if (!visited)
   {
      free(open->sptr);
      free(open);
      return NULL;
   }

   LNode tmp,ln;

   ds_stack_push_val(open, 0);

   while (open->top != open->sptr)
   {
      v = ds_stack_pop_val(open);
      if (!ds_list_search_val(visited, v, NULL))
        {
           ds_list_append_val(visited, v);
           printf("visited vertex %d\n", v);
           for(tmp = g->adjlist[v].head; tmp != NULL; tmp = tmp->next)
           {
             ds_stack_push_val(open, *(int*)tmp->data);
           }
        }

   }

   for(ln=visited->head;ln!=NULL;ln=ln->next)
     {
        printf("dfs = %d\n", *(unsigned int*)ln->data);
     }

   return g;
}

void dfs_recurse(Graph g, int v, unsigned char visited[])
{
   LNode tmp;

   visited[v] = 1;
   printf(" %d\n", v);

   for(tmp = g->adjlist[v].head; tmp != NULL; tmp = tmp->next)
   {
      if (visited[*(unsigned int*)tmp->data] == 0)
         dfs_recurse(g, *(unsigned int*)tmp->data, visited);
   }

}

Graph ds_graph_dfs2(Graph g)
{
   int i = 0;

   printf("dfs2\n");
   if (!g)
   {
      DS_LIB_ERR("ds_graph_dfs2: supplied argument 1 is not a valid graph!");
      return NULL;
   }

   unsigned char *visited = calloc(g->v, sizeof(unsigned char));
   if (!visited)
   {
      DS_C_ERR(__func__);
      return g;
   }

   for(; i < g->v; i++)
   {
      if (visited[i] == 0)
         dfs_recurse(g, i, visited);
   }

   return g;
}

// this code is to test graph only
int main(void)
{
   LNode ln;
   List l;
   int i = 0;

   Graph g = ds_graph_new(8, 1);

//   ds_graph_edge_add(g, 0, 1);
//   ds_graph_edge_add(g, 0, 7);
//   ds_graph_edge_add(g, 0, 2);
//   ds_graph_edge_add(g, 1, 4);
//   ds_graph_edge_add(g, 1, 3);
//   ds_graph_edge_add(g, 4, 6);
//   ds_graph_edge_add(g, 6, 3);
//   ds_graph_edge_add(g, 6, 5);
//   ds_graph_edge_add(g, 3, 7);
//   ds_graph_edge_add(g, 2, 3);
//   ds_graph_edge_add(g, 5, 2);

   ds_graph_edge_add(g, 0, 2);
   ds_graph_edge_add(g, 0, 1);
   ds_graph_edge_add(g, 1, 3);
   ds_graph_edge_add(g, 1, 4);
   ds_graph_edge_add(g, 3, 2);
   ds_graph_edge_add(g, 2, 5);
   ds_graph_edge_add(g, 3, 7);
   ds_graph_edge_add(g, 4, 6);
   ds_graph_edge_add(g, 5, 6);
   ds_graph_edge_add(g, 6, 3);
   ds_graph_edge_add(g, 7, 0);

   printf("directeness of graph %u\n", g->directed);

   for (l = &(g->adjlist[i]); i < 8; i++, l = &(g->adjlist[i]))
   {
      printf("printing for vertex %d\n", i);
      for(ln=l->head;ln!=NULL;ln=ln->next)
      {
         printf("list node data = %d\n", *((int*)ln->data));
      }
      ln = NULL;
   }

   ds_graph_dfs(g);
   ds_graph_dfs2(g);

   return 0;
}

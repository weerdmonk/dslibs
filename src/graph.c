
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

static void dfs_iterate(Graph g, int v, List visited)
{
   LNode tmp;

   // TODO: malloc fail should cause dfs to throw error. instead it continues which is OK for only connected graphs
   Stack open = ds_stack_new();
   if (!open) return;

   ds_stack_push_val(open, v);

   while (!_ds_stack_empty_check(open))
   {
      v = ds_stack_pop_val(open);
      if (!ds_list_search_val(visited, v, NULL))
        {
           ds_list_append_val(visited, v);
           /* fucntion to process graph node */   // TODO: inclue function ptr and data ptr in dfs API
           if (g->dee_foo) g->dee_foo(&v);
           for(tmp = g->adjlist[v].head; tmp != NULL; tmp = tmp->next)
           {
             ds_stack_push_val(open, *(int*)tmp->data);
           }
        }

   }

   ds_list_free(&open->l);
   free(open);
}

Graph ds_graph_dfs(Graph g)
{
   int v = 0;

   if (!g)
   {
      DS_LIB_ERR("ds_graph_dfs: supplied argument 1 is not a valid graph!");
      return NULL;
   }

   List visited = ds_list_new(NULL);
   if (!visited)
   {
      return g;
   }

   for(; v < g->v; v++)
   {
      dfs_iterate(g, v, visited);
   }

   ds_list_free(&visited);

   return g;
}

void dfs_recurse(Graph g, int v, unsigned char visited[])
{
   LNode tmp;

   visited[v] = 1;
   /* fucntion to process graph node */   // TODO: inclue function ptr and data ptr in dfs API
   if(g->dee_foo) g->dee_foo(&v);

   for(tmp = g->adjlist[v].head; tmp != NULL; tmp = tmp->next)
   {
      if (visited[*(unsigned int*)tmp->data] == 0)
         dfs_recurse(g, *(unsigned int*)tmp->data, visited);
   }

}

Graph ds_graph_dfs2(Graph g)
{
   int i = 0;

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

   free(visited);

   return g;
}

Graph ds_graph_bfs(Graph g)
{
   int v = 0;
   LNode tmp;

   if (!g)
   {
      DS_LIB_ERR("ds_graph_dfs2: supplied argument 1 is not a valid graph!");
      return NULL;
   }

   // list of visited vertices
   List visited = ds_list_new(NULL);
   if (!visited)
   {
      return g;
   }

   // queue to be used for traversal
   Queue open = ds_queue_new();
   if (!open)
   {
      return g;
   }

   // let us start with bfs from vertex 0 only
   ds_list_append_val(visited, 0);

   ds_queue_enque_val(open, 0);

   while (!_ds_queue_empty_check(open))
   {
      v = ds_queue_deque_val(open);
      /* add processor function here */
      if (g->dee_foo) g->dee_foo(&v);
      for(tmp = g->adjlist[v].head; tmp != NULL; tmp = tmp->next)
      {
         if (!ds_list_search_val(visited, *(int*)tmp->data, NULL))
         {
            ds_list_append_val(visited, *(int*)tmp->data);
            ds_queue_enque_val(open, *(int*)tmp->data);
         }
      }
   }

   ds_list_free(&open->l);
   free(open);

   ds_list_free(&visited);

   return g;
}


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

   if (g->directed)
   {
      _src = malloc(sizeof(int));
      *_src = src;
      l = &(g->adjlist[dest]);
      ds_list_append(l, _src);
   }

   return g;
}

// this code is to test graph only
int main(void)
{
   LNode ln;
   List l;
   int i = 0;

   Graph g = ds_graph_new(4, 1);

   ds_graph_edge_add(g, 0, 1);

   printf("directeness of graph %u\n", g->directed);

   for (l = &(g->adjlist[i]); i < 4; i++, l = &(g->adjlist[i]))
   {
      printf("printing for vertex %d\n", i);
      for(ln=l->head;ln!=NULL;ln=ln->next)
      {
         printf("list node data = %d\n", *((int*)ln->data));
      }
      ln = NULL;
   }

   return 0;
}

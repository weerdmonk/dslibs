
/*
 * dslibs v0.1
 * graph example v0.1
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

// function to process graph nodes
extern dfs_proc_func dee_foo;

// printf graph nodes
int dfs_print(void *data)
{
   int *p_v = data;
   printf("visited vertex %d\n", *p_v);

   return 0;
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

   dee_foo = dfs_print;

   printf("dfs\n");
   ds_graph_dfs(g);

   printf("dfs2\n");
   ds_graph_dfs2(g);

   return 0;
}

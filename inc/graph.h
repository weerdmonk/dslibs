
/*
 * dslibs v0.1
 * graph implementation v0.1
 * weerdmonk Dec2014
 *
 */

#ifndef GRAPH_H
#define GRAPH_H

#include <stdlib.h>
#include <stack.h>
#include <queue.h>
#include <list.h>
#include <error.h>

#define DS_GRAPH_ALLOC_SIZE		sizeof(struct _Graph)

typedef struct _Graph *Graph;

typedef int (*ds_graph_proc_func)(void *data);

struct _Graph {
   int v;
   unsigned char directed;
   List adjlist;
   ds_graph_proc_func dee_foo;
};

Graph ds_graph_new(int v, unsigned char directed);

Graph ds_graph_edge_add(Graph g, int src, int dest);

Graph ds_graph_edge_del(Graph g, int src, int dest);

Graph ds_graph_dfs_iterative(Graph g);

Graph ds_graph_dfs_recursive(Graph g);

Graph ds_graph_bfs(Graph g);

static inline void ds_graph_proc_func_add(Graph g, ds_graph_proc_func func)
{
   if (!g || !func)
      return;
   else
      g->dee_foo = func;

   return;
}

static inline void ds_graph_proc_func_del(Graph g)
{
   if (!g || !g->dee_foo)
      return;
   else
      g->dee_foo = NULL;

   return;
}

#endif /* GRAPH_H */

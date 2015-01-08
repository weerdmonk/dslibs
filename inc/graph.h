
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
#include <list.h>
#include <error.h>

#define DS_GRAPH_ALLOC_SIZE		sizeof(struct _Graph)

typedef struct _Graph *Graph;

struct _Graph {
   int v;
   unsigned char directed;
   List adjlist;
};

typedef int (*dfs_proc_func)(void *data);

Graph ds_graph_new(int v, unsigned char directed);

Graph ds_graph_edge_add(Graph g, int src, int dest);

Graph ds_graph_edge_del(Graph g, int src, int dest);

Graph ds_graph_dfs(Graph g);

Graph ds_grpah_dfs2(Graph g);

#endif /* GRAPH_H */
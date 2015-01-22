
/*
 * dslibs v0.1
 * binary tree implementation v0.1
 * weerdmonk Dec2014
 *
 */

#ifndef BTREE_H
#define BTREE_H

#include <stdlib.h>
#include <stack.h>
#include <queue.h>
#include <list.h>
#include <error.h>

#define DS_GRAPH_ALLOC_SIZE		sizeof(struct _Graph)

typedef struct _BLeaf *BLeaf;

struct _BLeaf {
   struct _BLeaf *left;
   struct _BLeaf *right;
   void *data;
};

typedef struct _BTree *BTree;

struct _BTree {
   int depth;
   BLeaf root;
};

#endif /* BTREE_H */

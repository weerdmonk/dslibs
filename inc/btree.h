
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

#define DS_BTREE_ALLOC_SIZE		sizeof(struct _BTree)
#define DS_BTREE_NODE_SIZE		   sizeof(struct _BTree)

typedef struct _BLeaf *BLeaf;

struct _BLeaf {
   struct _BLeaf *left;
   struct _BLeaf *right;
   int key;
};

typedef struct _BTree *BTree;

struct _BTree {
   int depth;
   BLeaf root;
};

BTree ds_btree_new(void);

BTree ds_btree_leaf_insert(BTree tree, int data);

BTree ds_btree_leaf_remove(BTree tree, int data);

#endif /* BTREE_H */

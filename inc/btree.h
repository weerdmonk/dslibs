
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

typedef struct _BTree *BTree;

typedef int (*ds_btree_proc_func)(BTree tree, BLeaf leaf, void *data);

struct _BLeaf {
   struct _BLeaf *left;
   struct _BLeaf *right;
   int key;
};

struct _BTree {
   int depth;
   BLeaf root;
   ds_btree_proc_func dee_foo;
   void *dee_foo_data;
};

static inline void ds_btree_proc_func_add(BTree tree, ds_btree_proc_func func)
{
   if (!tree || !func)
      return;
   else
      tree->dee_foo = func;

   return;
}

static inline void ds_btree_proc_func_del(BTree tree)
{
   if (!tree || !tree->dee_foo)
      return;
   else
      tree->dee_foo = NULL;

   return;
}

BTree ds_btree_new(void);

BTree ds_btree_leaf_insert(BTree tree, int data);

BTree ds_btree_leaf_remove(BTree tree, int data);

BTree ds_btree_inorder(BTree tree);

BTree ds_btree_levelorder(BTree tree);

#endif /* BTREE_H */


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
#include <btree.h>


BTree ds_btree_new(void)
{
   BTree bt = calloc(1, DS_BTREE_ALLOC_SIZE);
   if (!bt)
   {
      DS_C_ERR(__func__);
      return NULL;
   }

   return bt;
}

BTree ds_btree_leaf_insert(BTree tree, int data)
{
   if (!tree)
   {
      DS_LIB_ERR("ds_btree_leaf_insert: supplied argument is not a valid BTree!");
      return NULL;
   }

   BLeaf crawl = tree->root;

   while (crawl != NULL)
   {
      if (data < crawl->key)
        crawl = crawl->left;
      else if (data > crawl->key)
        crawl = crawl->right;
   }

   crawl = calloc(1, DS_BTREE_NODE_SIZE);
   if (crawl)
   {
      crawl->key = data;
   }

   return tree;
}



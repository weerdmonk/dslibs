
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

   BLeaf *p_crawl = &tree->root;

   while (*p_crawl != NULL)
   {
      if (data < (*p_crawl)->key)
        p_crawl = &((*p_crawl)->left);
      else if (data > (*p_crawl)->key)
        p_crawl = &((*p_crawl)->right);
      else
        return tree;
   }

   *p_crawl = calloc(1, DS_BTREE_NODE_SIZE);
   if (*p_crawl)
   {
      (*p_crawl)->key = data;
   }

   return tree;
}

BTree ds_btree_inorder(BTree tree)
{
   if (!tree)
   {
      DS_LIB_ERR("ds_btree_inorder: supplied argument is not a valid BTree!");
      return NULL;
   }

   BLeaf crawl = tree->root;
   unsigned char done = 0;

   Stack s = ds_stack_new();
   if (!s)
   {
      DS_LIB_ERR("ds_btree_inorder: failed to create stack");
      return tree;
   }

   while (!done)
   {
      if (crawl != NULL)
      {
         ds_stack_push(s, crawl);
         crawl = crawl->left;
      }
      else if (!_ds_stack_empty_check(s))
      {
         crawl = ds_stack_pop(s);
         /* insert processor function here */
         if (tree->dee_foo) tree->dee_foo(&crawl);

         crawl = crawl->right;
      }
      else
      {
         done = 1;
      }
   }

   free(s->l);
   free(s);

   return tree;
}













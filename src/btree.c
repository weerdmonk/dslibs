
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
   int _depth = 0;

   while (*p_crawl != NULL)
   {
      if (data < (*p_crawl)->key)
        p_crawl = &((*p_crawl)->left);
      else if (data > (*p_crawl)->key)
        p_crawl = &((*p_crawl)->right);
      else
        return tree;

      _depth++;
   }

   *p_crawl = calloc(1, DS_BTREE_NODE_SIZE);
   if (*p_crawl)
   {
      (*p_crawl)->key = data;
   }

   (*p_crawl)->depth = _depth;
   tree->depth = (_depth > tree->depth) ? _depth : tree->depth ;

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
         if (tree->dee_foo) tree->dee_foo(tree, crawl, tree->dee_foo_data);

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

BTree ds_btree_levelorder(BTree tree)
{
   if (!tree)
   {
      DS_LIB_ERR("ds_btree_levelorder: supplied argument is not a valid BTree!");
      return NULL;
   }

   BLeaf leaf = tree->root;
   Queue q = ds_queue_new();
   int nextlvlcount = 0, currlvlcount = 1;

   while (leaf)
   {
      if (tree->dee_foo) tree->dee_foo(tree, leaf, tree->dee_foo_data);

      if (leaf->left)
      {
         ds_queue_enque(q, leaf->left);
         nextlvlcount++;
      }

      if (leaf->right)
      {
         ds_queue_enque(q, leaf->right);
         nextlvlcount++;
      }

      leaf = ds_queue_deque(q);
      currlvlcount--;

      if (currlvlcount == 0)
      {
         currlvlcount = nextlvlcount;
         nextlvlcount = 0;
      }
   }

   free(q->l);
   free(q);
}











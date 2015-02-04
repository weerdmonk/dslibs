
/*
 * dslibs v0.1
 * btree example v0.1
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

int btree_print(void *data)
{
   BLeaf *p_lf = data;
   printf("visited leaf: %d\n", (*p_lf)->key);

   return 0;
}

int main(void)
{
   BTree bt;
   BLeaf lf;

   bt = ds_btree_new();

   ds_btree_proc_func_add(bt, btree_print);

   ds_btree_leaf_insert(bt, 10);
   ds_btree_leaf_insert(bt, 42);
   ds_btree_leaf_insert(bt, 17);
   ds_btree_leaf_insert(bt, 3);
   ds_btree_leaf_insert(bt, 99);
   ds_btree_leaf_insert(bt, 62);
   ds_btree_leaf_insert(bt, 21);
   ds_btree_leaf_insert(bt, 8);
   ds_btree_leaf_insert(bt, 21);

   printf("depth of btree = %d\n", bt->depth);

   printf("inorder\n");
   ds_btree_inorder(bt);

   return 0;
}

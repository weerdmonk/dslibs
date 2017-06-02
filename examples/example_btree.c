
/*
 * dslibs v0.1
 * binary search tree example v0.1
 * weerdmonk Dec2014
 *
 */

#include <stdio.h>
#include <btree.h>

typedef struct
{
  int val;
} integer_data_t;

static int btree_print_leaf_data_cb(BTree tree, void *leaf_key, void *cb_data)
{
  if (leaf_key == NULL)
  {
    return -1;
  }

  integer_data_t *p_data = leaf_key;
  printf("Data in visited leaf is %d\n", p_data->val);

  return 0;
}

static int btree_compare_cb(BTree tree, void *leaf1_key, void *leaf2_key)
{
  if ( (leaf1_key == NULL) ||
       (leaf2_key == NULL) )
  {
    return 0;
  }

  integer_data_t *p_data1 = leaf1_key,
                 *p_data2 = leaf2_key;

  if (p_data1->val < p_data2->val)
  {
    return -1;
  }
  else if (p_data1->val > p_data2->val)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

int main(void)
{
  integer_data_t int_data[10], *p_int_data;
  BTree bt;
  BLeaf leaf;

  bt = ds_btree_new();

  ds_btree_callback_add(bt, btree_print_leaf_data_cb, NULL);
  ds_btree_compare_callback_add(bt, btree_compare_cb);

  int_data[0].val = 10;
  ds_btree_leaf_insert(bt, &int_data[0]);
  int_data[1].val = 3;
  ds_btree_leaf_insert(bt, &int_data[1]);
  int_data[2].val = 42;
  ds_btree_leaf_insert(bt, &int_data[2]);
  int_data[3].val = 17;
  ds_btree_leaf_insert(bt, &int_data[3]);
  int_data[4].val = 99;
  ds_btree_leaf_insert(bt, &int_data[4]);
  int_data[5].val = 62;
  ds_btree_leaf_insert(bt, &int_data[5]);
  int_data[6].val = 21;
  ds_btree_leaf_insert(bt, &int_data[6]);
  int_data[7].val = 8;
  ds_btree_leaf_insert(bt, &int_data[7]);
  int_data[8].val = 21;
  ds_btree_leaf_insert(bt, &int_data[8]);

  /**
   *              10
   *           /      \
   *          3         42
   *           \      /    \
   *            8   17      99
   *                  \    /
   *                  21  62
   */

  printf("Depth of btree = %d\n", ds_btree_get_depth(bt));

  printf("*******************\n");

  leaf = ds_btree_search(bt, &int_data[4]);
  if (leaf != NULL)
  {
    printf("Depth of node containing value %d is %d\n", \
           int_data[4].val, ds_btree_get_leaf_depth(leaf));
  }

  printf("*******************\n");

  printf("Preorder\n");
  ds_btree_preorder(bt);

  printf("*******************\n");

  printf("Inorder\n");
  ds_btree_inorder(bt);

  printf("*******************\n");

  printf("Postorder\n");
  ds_btree_postorder(bt);

  printf("*******************\n");

  printf("Levelorder\n");
  ds_btree_levelorder(bt);

  printf("*******************\n");

  printf("Removing %d from tree\n", 10);
  ds_btree_leaf_remove(bt, &int_data[0]);

  printf("*******************\n");

  printf("Levelorder\n");
  ds_btree_levelorder(bt);

  ds_btree_delete(bt);

  return 0;
}

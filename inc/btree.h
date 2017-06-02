
/*
 * dslibs v0.1
 * binary search tree implementation v0.1
 * weerdmonk Dec2014
 *
 */

#ifndef BTREE_H
#define BTREE_H

typedef struct BLeaf_t *BLeaf;

typedef struct BTree_t *BTree;

typedef int (*ds_btree_callback)(BTree tree, void *leaf_key, void *cb_data);

typedef int (*ds_btree_compare_callback)(BTree, void *leaf1_key, void *leaf2_key);

void ds_btree_callback_add(BTree tree, ds_btree_callback cb, void *cb_data);

void ds_btree_callback_remove(BTree tree);

void ds_btree_compare_callback_add(BTree tree, ds_btree_compare_callback compare_cb);

void ds_btree_compare_callback_remove(BTree tree);

BTree ds_btree_new(void);

void ds_btree_delete(BTree tree);

BLeaf ds_btree_search(BTree, void *p_data);

BTree ds_btree_leaf_insert(BTree tree, void *p_data);

BTree ds_btree_leaf_remove(BTree tree, void *p_data);

unsigned int ds_btree_get_depth(BTree tree);

unsigned int ds_btree_get_leaf_depth(BLeaf leaf);

void ds_btree_get_leaf_data(BLeaf leaf, void **p_data);

void ds_btree_preorder(BTree tree);

void ds_btree_inorder(BTree tree);

void ds_btree_postorder(BTree tree);

void ds_btree_levelorder(BTree tree);

#endif /* BTREE_H */

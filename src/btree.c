
/*
 * dslibs v0.1
 * binary search tree implementation v0.1
 * weerdmonk Dec2014
 *
 */

#include <stdlib.h>
#include <error.h>
#include <list.h>
#include <stack.h>
#include <queue.h>
#include <btree.h>

#define DS_BTREE_ALLOC_SIZE   sizeof(struct BTree_t)
#define DS_BTREE_NODE_SIZE    sizeof(struct BLeaf_t)

struct BLeaf_t {
  struct BLeaf_t *left;
  struct BLeaf_t *right;
  void *key;
  int depth;
};

struct BTree_t {
  int depth;
  BLeaf root;
  ds_btree_callback cb;
  void *cb_data;
  ds_btree_compare_callback compare_cb;
  unsigned char delete_tree;
};

void ds_btree_callback_add(BTree tree, ds_btree_callback cb, void *cb_data)
{
  if (!tree || !cb)
  {
    return;
  }
  else
  {
    tree->cb = cb;
    if (cb_data != NULL)
    {
      tree->cb_data = cb_data;
    }
  }

  return;
}

void ds_btree_callback_remove(BTree tree)
{
  if (!tree || !tree->cb)
  {
    return;
  }
  else
  {
    tree->cb = NULL;
    tree->cb_data = NULL;
  }

  return;
}

void ds_btree_compare_callback_add(BTree tree, ds_btree_compare_callback compare_cb)
{
  if (!tree || !compare_cb)
  {
    return;
  }
  else
  {
    tree->compare_cb = compare_cb;
  }
}

void ds_btree_compare_callback_remove(BTree tree)
{
  if (!tree || !tree->compare_cb)
  {
    return;
  }
  else
  {
    tree->compare_cb = NULL;
  }
}

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

static int ds_btree_delete_cb(BTree tree, void *leaf_key, void *cb_data)
{
  if ( leaf_key == NULL )
  {
    return -1;
  }

  BLeaf leaf = leaf_key;

  free(leaf);
  return 0;
}

void ds_btree_delete(BTree tree)
{
  if (!tree)
  {
    DS_LIB_ERR("ds_btree_leaf_delete: supplied argument is not a valid BTree!");
    return;
  }

  ds_btree_callback_remove(tree);
  ds_btree_callback_add(tree, ds_btree_delete_cb, NULL);

  tree->delete_tree = 1;

  ds_btree_postorder(tree);

  free(tree);
}

BLeaf ds_btree_search(BTree tree, void *p_data)
{
  if (!tree)
  {
    DS_LIB_ERR("ds_btree_search: supplied argument is not a valid BTree!");
    return NULL;
  }

  if (!p_data)
  {
    DS_LIB_ERR("ds_btree_search: no data passed to search for!");
    return NULL;
  }

  BLeaf crawl = tree->root;

  while (crawl != NULL)
  {
    if ( tree->compare_cb(tree, p_data, crawl->key) < 0 )
    {
      crawl = crawl->left;
    }
    else if ( tree->compare_cb(tree, p_data, crawl->key) > 0 )
    {
      crawl = crawl->right;
    }
    else
    {
      return crawl;
    }
  }
  return crawl;
}

BTree ds_btree_leaf_insert(BTree tree, void *p_data)
{
  if (!tree)
  {
    DS_LIB_ERR("ds_btree_leaf_insert: supplied argument is not a valid BTree!");
    return NULL;
  }

  if (!p_data)
  {
    DS_LIB_ERR("ds_btree_leaf_insert: no data passed to insert!");
    return NULL;
  }

  BLeaf *p_crawl = &(tree->root);
  int _depth = 0;

  while (*p_crawl != NULL)
  {
    if ( tree->compare_cb(tree, p_data, (*p_crawl)->key) < 0)
    {
      p_crawl = &((*p_crawl)->left);
    }
    else if ( tree->compare_cb(tree, p_data, (*p_crawl)->key) > 0 )
    {
      p_crawl = &((*p_crawl)->right);
    }
    else
    {
      return tree;
    }

    _depth++;
  }

  *p_crawl = calloc(1, DS_BTREE_NODE_SIZE);
  if (*p_crawl)
  {
    (*p_crawl)->key = p_data;
  }

  (*p_crawl)->depth = _depth;
  tree->depth = (_depth > tree->depth) ? _depth : tree->depth ;

  return tree;
}

BTree ds_btree_leaf_remove(BTree tree, void *p_data)
{
  if (!tree)
  {
    DS_LIB_ERR("ds_btree_leaf_remove: supplied argument is not a valid BTree!");
    return NULL;
  }

  if (!p_data)
  {
    DS_LIB_ERR("ds_btree_leaf_remove: no data passed to remove!");
    return NULL;
  }

  BLeaf *p_node_to_remove = &(tree->root),
        parent = NULL,
        child = NULL,
        min_node = NULL;

  while (*p_node_to_remove != NULL)
  {
    if ( tree->compare_cb(tree, p_data, (*p_node_to_remove)->key) == 0 )
    {
      break;
    }
    else
    {
      parent = *p_node_to_remove;
      if ( tree->compare_cb(tree, p_data, (*p_node_to_remove)->key) < 0 )
      {
        p_node_to_remove = &((*p_node_to_remove)->left);
      }
      else if ( tree->compare_cb(tree, p_data, (*p_node_to_remove)->key) > 0 )
      {
        p_node_to_remove = &((*p_node_to_remove)->right);
      }
    }
  }

  if ( ((*p_node_to_remove)->left == NULL) &&                      // node to be removed is leaf node
            ((*p_node_to_remove)->right == NULL) )
  {
    free(*p_node_to_remove);
    *p_node_to_remove = NULL;
  }
  else if ( ((*p_node_to_remove)->left == NULL) ||                 // node to be removed has one child
            ((*p_node_to_remove)->right == NULL) )
  {
    child = ( (*p_node_to_remove)->left != NULL ) ? \
            ( (*p_node_to_remove)->left ) : \
            ( (*p_node_to_remove)->right );

    free(*p_node_to_remove);
    *p_node_to_remove = child;
  }
  else                                                             // node to be removed has two children
  {
    /* find the node with minimum value in right subtree */
    parent = *p_node_to_remove;
    min_node = (*p_node_to_remove)->right;
    while ( min_node->left != NULL )
    {
      parent = min_node;
      min_node = min_node->left;
    }

    /* copy key from minimum node to the node to be removed */
    (*p_node_to_remove)->key = min_node->key;

    ( parent->left == min_node ) ? \
    ( parent->left = min_node->right ) : \
    ( parent->right = min_node->right );

    free(min_node);
  }

  return tree;
}

unsigned int ds_btree_get_depth(BTree tree)
{
  if (!tree)
  {
    DS_LIB_ERR("ds_btree_get_depth: supplied argument is not a valid BTree!");
    return -1;
  }

  return tree->depth;
}

unsigned int ds_btree_get_leaf_depth(BLeaf leaf)
{
  if (!leaf)
  {
    DS_LIB_ERR("ds_btree_get_leaf_depth: supplied argument is not a valid BLeaf!");
    return -1;
  }

  return leaf->depth;
}

void ds_btree_get_leaf_data(BLeaf leaf, void **p_data)
{
  if (!leaf)
  {
    DS_LIB_ERR("ds_btree_get_leaf_data: supplied argument 1 is not a valid BLeaf!");
    return;
  }

  if (!p_data)
  {
    DS_LIB_ERR("ds_btree_get_leaf_data: no variable passed to get data!");
    return;
  }

  *p_data = (void*)leaf->key;

}

void ds_btree_preorder(BTree tree)
{
  if (!tree)
  {
    DS_LIB_ERR("ds_btree_preorder: supplied argument is not a valid BTree!");
    return;
  }

  BLeaf crawl = tree->root;
  unsigned char done = 0;

  Stack s = ds_stack_new();
  if (!s)
  {
    DS_LIB_ERR("ds_btree_preorder: failed to create stack!");
    return;
  }

  while (!done)
  {
    if (crawl != NULL)
    {
      /* insert processor function here */
      if (tree->cb)
      {
        tree->cb(tree, (void*)crawl->key, tree->cb_data);
      }
      ds_stack_push(s, crawl);
      crawl = crawl->left;
    }
    else if (!ds_stack_empty_check(s))
    {
      crawl = ds_stack_pop(s);
      crawl = crawl->right;
    }
    else
    {
      done = 1;
    }
  }

  ds_stack_delete(s);
}

void ds_btree_inorder(BTree tree)
{
  if (!tree)
  {
    DS_LIB_ERR("ds_btree_inorder: supplied argument is not a valid BTree!");
    return;
  }

  BLeaf crawl = tree->root;
  unsigned char done = 0;

  Stack s = ds_stack_new();
  if (!s)
  {
    DS_LIB_ERR("ds_btree_inorder: failed to create stack!");
    return;
  }

  while (!done)
  {
    if (crawl != NULL)
    {
      ds_stack_push(s, crawl);
      crawl = crawl->left;
    }
    else if (!ds_stack_empty_check(s))
    {
      crawl = ds_stack_pop(s);
      /* insert processor function here */
      if (tree->cb)
      {
        tree->cb(tree, (void*)crawl->key, tree->cb_data);
      }
      crawl = crawl->right;
    }
    else
    {
      done = 1;
    }
  }

  ds_stack_delete(s);
}

void ds_btree_postorder(BTree tree)
{
  if (!tree)
  {
    DS_LIB_ERR("ds_btree_postorder: supplied argument is not a valid BTree!");
    return;
  }

  BLeaf crawl = tree->root, last_visited = NULL;
  unsigned char done = 0;

  Stack s = ds_stack_new();
  if (!s)
  {
    DS_LIB_ERR("ds_btree_postorder: failed to create stack!");
    return;
  }

  while (!done)
  {
    if (crawl != NULL)
    {
      ds_stack_push(s, crawl);
      crawl = crawl->left;
    }
    else if (!ds_stack_empty_check(s))
    {
      crawl = ds_stack_peek(s);
      if ( (crawl->right != NULL) &&
           (last_visited != crawl->right) )
      {
        crawl = crawl->right;
      }
      else
      {
        last_visited = ds_stack_pop(s);
        if (tree->cb)
        {
          if (tree->delete_tree)
          {
            tree->cb(tree, (void*)last_visited, tree->cb_data);
          }
          else
          {
            tree->cb(tree, (void*)last_visited->key, tree->cb_data);
          }
        }
        crawl = NULL;
      }
    }
    else
    {
      done = 1;
    }

  }

  ds_stack_delete(s);
}

void  ds_btree_levelorder(BTree tree)
{
  if (!tree)
  {
    DS_LIB_ERR("ds_btree_levelorder: supplied argument is not a valid BTree!");
    return;
  }

  BLeaf crawl = tree->root;
  unsigned char done = 0;

  Queue q = ds_queue_new();
  if (!q)
  {
    DS_LIB_ERR("ds_btree_leveltorder: failed to create queue!");
    return;
  }

  while (!done)
  {
    if (crawl != NULL)
    {
      if (tree->cb)
      {
        tree->cb(tree, (void*)crawl->key, tree->cb_data);
      }
      if (crawl->left != NULL)
      {
        ds_queue_enque(q, crawl->left);
      }
      if (crawl->right != NULL)
      {
        ds_queue_enque(q, crawl->right);
      }
      crawl = NULL;
    }
    else if (!ds_queue_empty_check(q))
    {
      crawl = ds_queue_deque(q);
    }
    else
    {
      done = 1;
    }
  }

  ds_queue_delete(q);
}

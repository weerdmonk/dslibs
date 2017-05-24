
/*
* dslibs v0.1
* maxheap implementation v0.1
* weerdmonk May2017
*
*/

#include <maxheap.h>
#include <error.h>

ds_maxheap ds_maxheap_new(int size)
{
  ds_maxheap mh = (ds_maxheap)malloc(DS_MAXHEAP_SIZE);
  if (!mh)
  {
    DS_LIB_ERR("ds_maxheap_new: could not create maxheap!");
    return DS_MAXHEAP_EMPTY;
  }

  mh->size = size;
  mh->N = -1;

  mh->arr = (int*)malloc(size * sizeof(int));
  if (!mh->arr)
  {
    free(mh);
    DS_LIB_ERR("ds_maxheap_new: could not create array for_maxheap!");
    return DS_MAXHEAP_EMPTY;
  }
  mh->is_arr_external = 0;

  return mh;
}

void ds_maxheap_delete(ds_maxheap mh)
{
  if (!mh || !mh->arr)
  {
    DS_LIB_ERR("ds_maxheap_delete: invalid maxheap passed!");
    return;
  }

  if (mh->is_arr_external == 0)
  {
    free(mh->arr);
  }

  free(mh);

}

void ds_maxheap_adjust(ds_maxheap mh, int idx)
{
  if (!mh || !mh->arr)
  {
    DS_LIB_ERR("ds_maxheap_adjust: invalid maxheap passed!");
    return;
  }

#ifdef OPTIMAL_ALGO
  int max_child_idx = left(idx);                                   // let left child be larger child
  /* cache value of root node */
  int tmp = mh->arr[idx];

  while ( max_child_idx <= mh->N )                                 // check if larger child's index is valid
  {
    if ( (max_child_idx < mh->N) &&                                // right child exits
         (mh->arr[max_child_idx] < mh->arr[max_child_idx + 1]) )   // left child is smaller than right child
    {
      max_child_idx++;                                             // right child is larger child
    }

    if ( tmp >= mh->arr[max_child_idx] )
    {
      break;                                                       // parent is already larger than children
    }
    else
    {
      /* swap parent with larger child */
      mh->arr[parent(max_child_idx)] = mh->arr[max_child_idx];
    }
    max_child_idx = left(max_child_idx);                           // let left child be larger child
  }
  /* value of root node should be placed at parent of the invalid leaf index */
  mh->arr[parent(max_child_idx)] = tmp;
#else
  int max_child_idx = left(idx);                                   // let left child be larger child

  while ( is_node(mh, idx) )
  {
    int tmp = mh->arr[idx];

    if ( (max_child_idx < mh->N) &&                                // right child exists
         (mh->arr[max_child_idx] < mh->arr[max_child_idx + 1]) )   // left child is smaller than right child
    {
      max_child_idx++;                                             // right child is larger child
    }

    if ( tmp >= mh->arr[max_child_idx] )
    {
      break;                                                       // parent is already larger than children
    }
    else
    {
      /* swap parent with larger child */
      mh->arr[idx] = mh->arr[max_child_idx];
      mh->arr[max_child_idx] = tmp;

      /* repeat with swapped node */
      idx = max_child_idx;
    }
    max_child_idx = left(max_child_idx);                           // let left child be larger child
  }
#endif
}

void ds_maxheap_insert(ds_maxheap mh, int data)
{
  int i, j;
  if (!mh || !mh->arr || (mh->size == 0))
  {
    DS_LIB_ERR("ds_maxheap_insert: invalid maxheap passed!");
    return;
  }

  ++mh->N;
  j = mh->N;
  i = parent(mh->N);
  mh->arr[j] = data;

  /* now adjust the heap to satisfy maxheap property */
  while ((i >= 0) && (mh->arr[i] < data))
  {
    mh->arr[j] = mh->arr[i];
    j = i;
    i = parent(i);
  }
  mh->arr[j] = data;

}

int ds_maxheap_remove_root(ds_maxheap mh)
{
  int tmp;
  if (!mh || !mh->arr || (mh->size == 0))
  {
    DS_LIB_ERR("ds_maxheap_remove_root: invalid maxheap passed!");
    return -1;
  }

  tmp = mh->arr[0];
  mh->arr[0] = mh->arr[mh->N];
  mh->arr[mh->N] = tmp;

  --mh->N;

  ds_maxheap_adjust(mh, 0);
}

void ds_maxheap_build_heap(ds_maxheap mh)
{
  int i;
  if (!mh || !mh->arr)
  {
    DS_LIB_ERR("ds_maxheap_build_heap: invalid maxheap passed!");
    return;
  }

  for (i = parent(mh->N); i >= 0; i--)
  {
    ds_maxheap_adjust(mh, i);
  }
}

ds_maxheap ds_maxheap_from_array(int *array, int arr_size)
{
  ds_maxheap mh;
  if (!array)
  {
    DS_LIB_ERR("ds_maxheap_from_array: invalid array passed!");
    return DS_MAXHEAP_EMPTY;
  }

  mh  = (ds_maxheap)malloc(DS_MAXHEAP_SIZE);
  if (!mh)
  {
    DS_LIB_ERR("ds_maxheap_from_array: could not create maxheap from array!");
    return DS_MAXHEAP_EMPTY;
  }

  mh->arr = array;
  mh->is_arr_external = 1;
  mh->size = arr_size;
  mh->N = arr_size - 1;

  ds_maxheap_build_heap(mh);

  return mh;
}

void ds_maxheap_heapsort(ds_maxheap mh)
{
  int i;
  if (!mh || !mh->arr || (mh->size == 0))
  {
    DS_LIB_ERR("ds_maxheap_heapsort: invalid maxheap passed!");
    return;
  }

  for (i = mh->N; i > 0; i--)
  {
    ds_maxheap_remove_root(mh);
  }
}

void ds_maxheap_heapsort_array(int *array, int arr_size)
{
  int i, tmp;
  if (!array)
  {
    DS_LIB_ERR("ds_maxheap_heapsort_array: invalid array passed!");
    return;
  }

  ds_maxheap mh = ds_maxheap_from_array(array, arr_size);
  if (!mh)
  {
    DS_LIB_ERR("ds_maxheap_from_array: could not create maxheap from array!");
    return;
  }

  for (i = mh->N; i > 0; i--)
  {
    ds_maxheap_remove_root(mh);
  }

  free(mh);
}

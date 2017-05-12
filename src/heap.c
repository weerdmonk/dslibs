
/*
 * dslibs v0.1
 * heap implementation v0.1
 * weerdmonk May2017
 *
 */

#include <heap.h>

void ds_maxheap_heapsort(int *A, int n)
{
    int i, tmp;
    if (!A) return;

    maxHeap mh = ds_maxheap_from_arr(A, n);
    if (!mh) return;

    ds_maxheap_heapify(mh);

    for (i = mh->N; i > 0; i--)
    {
        tmp = mh->arr[i];
        mh->arr[i] = mh->arr[0];
        mh->arr[0] = tmp;
        --mh->N;
        ds_maxheap_adjust(mh, 0);  
    }

    free(mh);
}

maxHeap ds_maxheap_from_arr(int *A, int n)
{
    maxHeap mh;
    if (!A) return NULL;

    mh  = (maxHeap)malloc(sizeof(struct max_heap));
    if (!mh)
    {
        return NULL;
    }

    mh->arr = A;
    mh->size = n;
    mh->N = n-1;

    ds_maxheap_heapify(mh);

    return mh;
}
    

maxHeap ds_maxheap_new(int size)
{
    maxHeap mh = (maxHeap)malloc(sizeof(struct max_heap));
    if (!mh)
    {
        return NULL;
    }

    mh->size = size;
    
    mh->arr = (int*)malloc(size * sizeof(int));
    if (!mh->arr)
    {
        free(mh);
        return NULL;
    }

    mh->N = 0;

    return mh;
}

void ds_maxheap_adjust(maxHeap mh, int idx)
{
    if (!mh || !mh->arr) return;

    int j = _left(idx);
    int item = mh->arr[idx];

    while (j <= mh->N)
    {
        if ((j < mh->N) && (mh->arr[j] < mh->arr[j + 1]))
        {
            j++;
        }
        if (item > mh->arr[j])
        {
            break;
        }
        else
        {
            mh->arr[_parent(j)] = mh->arr[j];
        }
        j = _left(j);
    }
    mh->arr[_parent(j)] = item;
}

void ds_maxheap_insert(maxHeap mh, int data)
{
    int i, j;
    if (!mh || !mh->arr) return;
    if (mh->N == (mh->size - 1)) return;

    j = mh->N;
    i = _parent(mh->N);
    mh->arr[j] = data;
    
    //now we have the adjust the heap to satisfy max heap property
    while ((i > 0) && (mh->arr[i] < data))
    {
        mh->arr[j] = mh->arr[i];
        j = i;
        i = _parent(i);
    }
    mh->arr[j] = data;
    ++mh->N;
}

void ds_maxheap_heapify(maxHeap mh)
{
    int i;
    if (!mh || !mh->arr) return;

    for (i = _parent(mh->N); i >= 0; i--)
    {   
        ds_maxheap_adjust(mh, i);
    }
}

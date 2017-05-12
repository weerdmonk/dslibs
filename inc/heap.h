
/*
 * dslibs v0.1
 * heap implementation v0.1
 * weerdmonk May2017
 *
 */

#ifndef HEAP_H
#define HEAP_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define _parent(i)  (int)floor(((i) - 1) / 2)
#define _left(i)    (2 * (i)) + 1
#define _right(i)   (2 * (i)) + 2


struct max_heap {
    int *arr;
    int size;
    int N;
};

typedef struct max_heap *maxHeap;

void ds_maxheap_heapsort(int *A, int n);

maxHeap ds_maxheap_from_arr(int *A, int n);

maxHeap ds_maxheap_new(int size);

void ds_maxheap_adjust(maxHeap mh, int idx);

void ds_maxheap_insert(maxHeap mh, int data);

void ds_maxheap_heapify(maxHeap mh);

#endif /* HEAP_H */

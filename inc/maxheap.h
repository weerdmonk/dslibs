
/*
 * dslibs v0.1
 * maxheap implementation v0.1
 * weerdmonk May2017
 *
 */

#ifndef MAXHEAP_H
#define MAXHEAP_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define _parent(i)  (int)floor(((i) - 1) / 2)
#define _left(i)    (2 * (i)) + 1
#define _right(i)   (2 * (i)) + 2


struct ds_max_heap_t {
    int *arr;
    int size;
    int N;
};

typedef struct ds_max_heap_t *ds_max_heap;

void ds_maxheap_heapsort(int *A, int n);

ds_max_heap ds_maxheap_from_arr(int *A, int n);

ds_max_heap ds_maxheap_new(int size);

void ds_maxheap_adjust(ds_max_heap mh, int idx);

void ds_maxheap_insert(ds_max_heap mh, int data);

void ds_maxheap_heapify(ds_max_heap mh);

#endif /* MAXHEAP_H */

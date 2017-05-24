
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

#define parent(i)      (int)((((int)i) - 1) >> 1)
#define left(i)        ((((int)i) << 1) + 1)
#define right(i)       ((((int)i) << 1) + 2)
#define is_leaf(mh, i) (left((i)) > (mh)->N)
#define is_node(mh, i) (left((i)) <= (mh)->N)

struct ds_maxheap_t {
    int *arr;
    unsigned char is_arr_external;
    int size;
    int N;
};

typedef struct ds_maxheap_t* ds_maxheap;

#define DS_MAXHEAP_SIZE  sizeof(struct ds_maxheap_t)
#define DS_MAXHEAP_EMPTY NULL

ds_maxheap ds_maxheap_new(int size);

void ds_maxheap_delete(ds_maxheap mh);

void ds_maxheap_adjust(ds_maxheap mh, int idx);

void ds_maxheap_insert(ds_maxheap mh, int data);

int ds_maxheap_remove_root(ds_maxheap mh);

void ds_maxheap_build_heap(ds_maxheap mh);

ds_maxheap ds_maxheap_from_array(int *array, int arr_size);

void ds_maxheap_heapsort(ds_maxheap mh);

void ds_maxheap_heapsort_array(int *array, int arr_size);

#endif /* MAXHEAP_H */

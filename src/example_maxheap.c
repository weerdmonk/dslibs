
/*
 * dslibs v0.1
 * maxheap example v0.1
 * weerdmonk May2017
 *
 */

#include <maxheap.h>
#include <time.h>

void generate_sequence(int A[], int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        A[i] = rand();
    }
}

void print_array(int A[], int n)
{
    int i;
    for(i = 0; i < n; i++)
    {
        printf("A[%d] = %d\n", i, A[i]);
    }
}

int main(int argc, char **argv)
{
  int i;
  ds_maxheap heap;
  int seq[1000000];
  int arr[] = {101, 45, 2, 17, 11, 21, 79, 31};
  clock_t begin, end;
  double time_taken;
  int n_elements = sizeof(arr) / sizeof(int);

  printf("Create maxheap from array:\n");
  /* create maxheap from array */
  heap = ds_maxheap_from_array(arr, 8);

  print_array(heap->arr, heap->N + 1);

  ds_maxheap_delete(heap);
  printf("*************\n");

  printf("Sort an array using maxheap:\n");
  /* sort an array using maxheap */
  ds_maxheap_heapsort_array(arr, n_elements);
  print_array(arr, n_elements);
  printf("*************\n");

  printf("Run heapsort on large array:\n");
  generate_sequence(seq, 1000000);

  begin = clock();
  ds_maxheap_heapsort_array(seq, 1000000);
  end = clock();
  time_taken = end - begin;
  time_taken /= CLOCKS_PER_SEC;

  //print_array(seq, 1000000);
  printf("time_taken = %f\n", time_taken);
  printf("*************\n");

  printf("Inserting elements to empty heap:\n");
  heap = ds_maxheap_new(10);

  ds_maxheap_insert(heap, 1);
  print_array(heap->arr, heap->N + 1);
  printf("*************\n");

  ds_maxheap_insert(heap, 5);
  print_array(heap->arr, heap->N + 1);
  printf("*************\n");

  ds_maxheap_insert(heap, 9);
  print_array(heap->arr, heap->N + 1);
  printf("*************\n");

  ds_maxheap_insert(heap, 12);
  print_array(heap->arr, heap->N + 1);
  printf("*************\n");

  ds_maxheap_insert(heap, 3);
  print_array(heap->arr, heap->N + 1);
  printf("*************\n");

  ds_maxheap_insert(heap, 41);
  print_array(heap->arr, heap->N + 1);
  printf("*************\n");

  ds_maxheap_insert(heap, 27);
  print_array(heap->arr, heap->N + 1);
  printf("*************\n");

  ds_maxheap_insert(heap, 22);
  print_array(heap->arr, heap->N + 1);
  printf("*************\n");

  n_elements = heap->N + 1;
  printf("Sorted heap:\n");
  ds_maxheap_heapsort(heap);
  print_array(heap->arr, n_elements);
  ds_maxheap_delete(heap);
  printf("*************\n");

	return 0;
}


/*
 * dslibs v0.1
 * heap example v0.1
 * weerdmonk May2017
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

void print_arr(int A[], int n)
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
    ds_max_heap h;
    int seq[1000000];
    int arr[] = {101, 45, 2, 17, 11, 21, 79, 31};
    clock_t begin, end;
    double time_taken;
    generate_sequence(seq, 1000000);
    //h = ds_maxheap_from_arr(arr, 8);

    begin = clock();
    ds_maxheap_heapsort(seq, 1000000);
    end = clock();
    time_taken = end - begin;
    time_taken /= CLOCKS_PER_SEC;

    //print_arr(seq, 1000000);
    printf("time_taken = %f\n", time_taken);

/*
    ds_maxheap_insert(h, 1);
    for(i = 0; i < 10; i++)
    {
        printf("data = %d\n", h->arr[i]);
    }
    printf("*************\n");

    ds_maxheap_insert(h, 5);
    for(i = 0; i < 10; i++)
    {
        printf("data = %d\n", h->arr[i]);
    }
    printf("*************\n");

    ds_maxheap_insert(h, 9);
    for(i = 0; i < 10; i++)
    {
        printf("data = %d\n", h->arr[i]);
    }
    printf("*************\n");

    ds_maxheap_insert(h, 12);
    for(i = 0; i < 10; i++)
    {
        printf("data = %d\n", h->arr[i]);
    }
    printf("*************\n");

    ds_maxheap_insert(h, 3);
    for(i = 0; i < 10; i++)
    {
        printf("data = %d\n", h->arr[i]);
    }
    printf("*************\n");

    ds_maxheap_insert(h, 41);
    for(i = 0; i < 10; i++)
    {
        printf("data = %d\n", h->arr[i]);
    }
    printf("*************\n");

    ds_maxheap_insert(h, 27);
    for(i = 0; i < 10; i++)
    {
        printf("data = %d\n", h->arr[i]);
    }
    printf("*************\n");

    ds_maxheap_insert(h, 22);
    for(i = 0; i < 10; i++)
    {
        printf("data = %d\n", h->arr[i]);
    }
    printf("*************\n");
*/

    return 0;
}

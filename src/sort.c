
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
 * algorithm is to take each element
 * and insert it among elements preceding it
 * such that the array till current element's
 * position is sorted.
 */

void insertion_sort(int A[], int n)
{
   int i,j,t;
   for(i = 1; i < n; i++)
   {
      t = A[i];
      j = i;
      while((j > 0) && (A[j - 1] > t))
      {
         A[j] = A[j - 1];
         j--;
      }
      A[j] = t;
   }
}

void shell_sort(int A[], int n)
{

}

/*
 * algorithm is to take each element and
 * compare with succeding elements so as
 * to find the minimum of them and swap
 * current element with this minimum.
 */
void selection_sort(int A[], int n)
{
   int i,j,minI,t;
   for(i = 0; i < n; i++)
   {
      minI = i;
      for(j = i; j < n; j++)
      {
         if (A[j] < A[minI]) minI = j;
      }
      if (minI != i)
      {
         t = A[i];
         A[i] = A[minI];
         A[minI] = t;
      }
   }
}

/*
 * algorithm is to swap consecutive
 * elements by comparison until entire
 * array gets sorted
 * modification: get index from which array is sorted
 * to avoid.
 */
void bubble_sort(int A[], int n)
{
   int i,j,t,newI;
   for(i = n; i > 0; i--)
   {
      newI = 0;
      for(j = 0; j < n; j++)
      {
         if (A[j - 1] > A[j])
         {
            t = A[j - 1];
            A[j - 1] = A[j];
            A[j] = t;
            newI = j;
         }
      }
      i = newI;
   }
}

/* algorithm is to chose a pivot element and partition
 * other elements in comparision to it and recursively
 * apply to all partitons until only one element remains.
 * NOTE: choice of pivot determines the efficiency
 */
void quick_sort(int A[], int lo, int hi)
{
   int P,p,i,t;
   if (lo < hi)
   {
      /* partition the array into two sub array */
      P = hi; /* choose pivot as last index */
      p = lo; /* choose an index variable to calculate position of pivot */
      /* start moving elements based on comparision with pivot */
      for(i = lo; i <= hi; i++)
      {
         if (A[i] < A[P])
         {
            if (i != p)
            {
               t = A[i];
               A[i] = A[p];
               A[p] = t;
            }
            p++;
         }
      }
      /* bring pivot element to its right place */
      t = A[P];
      A[P] = A[p];
      A[p] = t;
      /* recursive calls on subarrays */
      quick_sort(A, lo, p - 1);
      quick_sort(A, p + 1, hi);
   }
}

/* almost quick sort, only that for smaller ranges of
 * elements, an insertion sort is used instead of
 * recursing further.
 */
void quicker_sort(int A[], int lo, int hi)
{
   int P,p,i,t;
   if ((hi - lo) == 10)
   {
      insertion_sort(A, hi - lo);
   }   
   else if (lo < hi)
   {
      /* partition the array into two sub array */
      P = hi; /* choose pivot as last index */
      p = lo; /* choose an index variable to calculate position of pivot */
      /* start moving elements based on comparision with pivot */
      for(i = lo; i <= hi; i++)
      {
         if (A[i] < A[P])
         {
            if (i != p)
            {
               t = A[i];
               A[i] = A[p];
               A[p] = t;
            }
            p++;
         }
      }
      /* bring pivot element to its right place */
      t = A[P];
      A[P] = A[p];
      A[p] = t;
      /* recursive calls on subarrays */
      quicker_sort(A, lo, p - 1);
      quicker_sort(A, p + 1, hi);
   }
}

void generate_sequence(int A[], int n) {
   int i;
   for(i = 0; i < n; i++)
   {
      A[i] = rand();
   }
}

int main(int argc, char ** argv)
{
   int arr[] = {5, 10, 9, 6, 4, 7, 3, 2, 8, 1};
   int seq[1000000];
   int i;
   clock_t begin, end;
   double time_taken;

   generate_sequence(seq, 1000000);

   begin = clock();

   //insertion_sort(seq, 1000000);
   //selection_sort(seq, 1000000);
   //bubble_sort(arr, 10);
   quicker_sort(seq, 0, 999999);

   end = clock();
   time_taken = end - begin;
   time_taken /= CLOCKS_PER_SEC;

   //for(i = 0; i < 1000000; i++)
   // {
   //    printf("%d\n", seq[i]);
   // }

   printf("time_taken = %f\n", time_taken);

   return 0;
}

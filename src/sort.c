
#include <stdio.h>
#include <stdlib.h>

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

int main(int argc, char ** argv)
{
   int arr[] = {5, 10, 9, 6, 4, 7, 3, 2, 8, 1};
   int i;

   //insertion_sort(arr, 10);
   //selection_sort(arr, 10);
   //bubble_sort(arr, 10);
   quick_sort(arr, 0, 9);

   for(i = 0; i < 10; i++)
    {
       printf("%d\n", arr[i]);
    }

   return 0;
}

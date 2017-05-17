
/*
 * dslibs v0.1
 * sort implementation v0.1
 * weerdmonk May2017
 *
 */

#include <sort.h>

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
	if ((hi - lo) == 32)
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


/*
 * dslibs v0.1
 * sort example v0.1
 * weerdmonk may2017
 *
 */

#include <sort.h>
#include <time.h>

static struct timeval t_start;

static inline void start()
{
   gettimeofday(&t_start, NULL);
}

static inline void stop()
{
   struct timeval t_end;
   gettimeofday(&t_end, NULL);
   unsigned long long t = 1000 * (t_end.tv_sec - t_start.tv_sec) + (t_end.tv_usec - t_start.tv_usec) / 1000;
   printf("time taken = %llu\n", t);
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

   generate_sequence(seq, 1000000);

   start();

   //insertion_sort(seq, 1000000);
   //selection_sort(seq, 1000000);
   //bubble_sort(seq, 10);
   quick_sort(seq, 0, 999999); 
   //quicker_sort(seq, 0, 999999);

   stop();


   return 0;
}

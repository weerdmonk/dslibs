
/*
* dslibs v0.1
* sort example v0.1
* weerdmonk may2017
*
*/

#include <sort.h>
#include <time.h>
#include <stdlib.h>
#include <sys/time.h>

static struct timeval t_start;
int seq[1000000];

static inline void start(char choice)
{
  gettimeofday(&t_start, NULL);

  switch(choice)
  {
    case '0':
      printf("Running insertion sort!\n");
      insertion_sort(seq, 999999);
      break;
    case '1':
      printf("Running selection sort!\n");
      selection_sort(seq, 999999);
      break;
    case '2':
      printf("Running bubble sort!\n");
      bubble_sort(seq, 999999);
      break;
    case '3':
      printf("Running quick sort!\n");
      quick_sort(seq, 0, 999999);
      break;
    case '4':
      printf("Running quicker sort!\n");
      quicker_sort(seq, 0, 999999);
      break;
    default:
      printf("Invalid choice!\n");
  }
}

static inline void stop()
{
  struct timeval t_end;
  gettimeofday(&t_end, NULL);
  unsigned long long t = 1000 * (t_end.tv_sec - t_start.tv_sec) + (t_end.tv_usec - t_start.tv_usec) / 1000;
  printf("time taken = %llu\n", t);
}

void generate_sequence(int A[], int size)
{
  int i;
  for(i = 0; i < size; i++)
  {
    A[i] = rand();
  }
}

void print_help(char path_to_exe[])
{
  printf("Usage: %s <sort type>\n", path_to_exe);
  printf("0 - Insertion sort\n");
  printf("1 - Selection sort\n");
  printf("2 - Bubble sort\n");
  printf("3 - Quick sort\n");
  printf("4 - Quicker sort\n");
  printf("\n");
}

int main(int argc, char ** argv)
{
  int arr[] = {5, 10, 9, 6, 4, 7, 3, 2, 8, 1};

  char sort_type = '0';
  if (argc == 2)
  {
    sort_type = argv[1][0];
  }
  else
  {
    print_help(argv[0]);
    return 1;
  }

  generate_sequence(seq, 1000000);

  start(sort_type);
  stop();

  return 0;
}

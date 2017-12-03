/* Partition of a range is the main part of the quicksort algorithm.
   This video http://www.youtube.com/watch?v=MZaf_9IZCrc
   explains the partition concept very well.

   For partitioning you need to have:
   1) a pivot - usually the right most element of the range
   2) a i,j position - usually the left most element of the range

   In a for loop over j position compare element at j if less then pivot:
   If elem[j] < pivot then swap elem[j] with elem[i] and increment i,
   otherwise continue the loop with incrementing j position.

   At the end of the loop all elements less the pivot will be at the left of i.
   The i position is where the pivot should be. The partitioning ends with
   swapping pivot with elem[i].

   Repeating the partitioning for the entire range for couple of times will
   reorder all elements accordingly. The best however is to recursively call
   parition, one time for each of the ranges [l, i] & [i+1, r].
*/
#include <stdio.h>

void swap(int v[], int l, int r);
void printv(int v[], int size);

main()
{
    int v[5] = {6, 3, 5, 4, 2};
    int p, i, j;                  /* pivot p, i and j */
                                  /* <-- start of paritioning */
    p = 4;
    i = 0;
    j = 0;

    for (; j < p; ++j)
        if (v[j] < v[p])
            swap(v, j, i++);
    swap(v, p, i);
                                  /* <-- end of paritioning */
    printv(v, 5);
}

void swap(int v[], int l, int r)
{
    int t = v[l];
    v[l] = v[r];
    v[r] = t;
}

void printv(int v[], int size)
{
    int i;
    for (i = 0; i < size; ++i)
        printf("%d ", v[i]);
    printf("\n");
}
/*
  2 3 5 4 6
*/

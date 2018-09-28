/* Partition of a range is the main part of the quicksort algorithm.
   This video http://www.youtube.com/watch?v=MZaf_9IZCrc
   explains the partition concept very well.

   For partitioning you need to have:
   1) p the pivot: usually the right most element of the range
   2) i,j position: usually j the first element of the range and i=j-1

   Loop over j position and compare elem[j] with elem[p]:
   If elem[j] < elem[p] then increment i and swap elem[i] with elem[j];
   Else continue with next j position.

   When finished, increment i and swap it with the pivot element.
   At this point all elements less than the pivot are to the left.

   This must be repeated recursively for the range [l, i-1] and [i+1, r]
   where l is the left and r is the right most element of the range,
   and i is the pivot.
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
    j = 0;
    i = j-1;

    for (; j < p; ++j)
        if (v[j] < v[p])
            swap(v, ++i, j);
    swap(v, ++i, p);
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

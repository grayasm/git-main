/* Cap.4 Functions and Program Structure, pag.87

   Another good example of recursion is quicksort, a sorting algorithm developed
   by C. A. R. Hoare in 1962. Given an array, one element is chosen and the
   others are partitioned into two subsets - those less than the partition
   element and those greater than or equal to it. The same process is then
   applied recursively to the two subsets. When a subset has fewer than two
   elements, it doesn't need any sorting; this stops the recusion.
*/

#include <stdio.h>

/* qsort: sort v[left]...v[right] into increasing order */
void qsort(int v[], int left, int right)
{
    int i, last;
    void swap(int v[], int i, int j);

    if (left >= right)    /* do nothing if array constains */
        return;           /* fewer than two elements */

    swap (v, left, (left + right)/2);    /* move partition elem to v[0] */

    last = left;
    for (i = left + 1; i <= right; i++)  /* partition */
        if (v[i] < v[left])
            swap (v, ++last, i);

    swap (v, left, last);                /* restore partition element */
    qsort (v, left, last -1 );
    qsort (v, last+1, right);
}

/* swap: intechange v[i] and v[j] */
void swap(int v[], int i, int j)
{
    int temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}


main()
{
    int i;
    int v[10] = {50, 44, 32, 21, 13, -10, -22, -34, -45, -50};
    qsort(v, 0, 9);

    for (i = 0; i < 10; ++i)
        printf("%d ", v[i]);
    printf("\n");
}
/*
  -50 -45 -34 -22 -10 13 21 32 44 50

  We can write a shorter version of qsort like this:

  void qsort(int v[], int l, int r)
  {
    int i, j, p;                // i, j and the p(pivot)
    
    if(l >= r)
      return;

    i = l-1;
    j = l;
    p = r;

    for(; j < p; ++j)           // <-- start paritioning
        if(v[j] < v[p])
            swap(v, ++i, j);
    swap(v, ++i, p);            // <-- end partitioning

    qsort(v, l, i-1);           // sort left side
    qsort(v, i+1, r);           // sort right side
  }
*/

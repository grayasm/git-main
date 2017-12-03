/* Cap.3 Control Flow, pag.58

   Binary search first compares the input value x to the middle element of the
   array v. If x is less then the middle value, searching focuses on the lower
   half of the table, otherwise on the upper half. In either case, the next
   step is to compare x to the middle element of the selected half. This process
   of dividing the range in two continues until the value is found or the range
   is empty.
   The fundamental decision is whether x is less than, greater than, or equal
   to the middle element v[mid] at each step; this is natural for else-if.
*/

#include <stdio.h>

/* binsearch: find x in v[0] <= v[1] <= ... <= v[n-1] */
int binsearch (int x, int v[], int n)
{
    int low, high, mid;

    low = 0;
    high = n - 1;
    while (low <= high) {
        mid = (low + high) / 2;
        if (x < v[mid])
            high = mid - 1;
        else if (x > v[mid])
            low = mid + 1;
        else    /* found match */
            return mid;
    }
    return -1;  /* no match */
}


main()
{
    int v[10] = {100, 122, 133, 144, 155, 166, 177, 188, 199, 200 };
    printf ("binsearch(%d, v[10], %d)=%d\n", 177, 10, binsearch(177, v, 10));
}

/*
  binsearch(177, v[10], 10)=6
*/

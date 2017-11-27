/* Cap.3 Control Flow, pag.62

   The basic idea of this sorting algorithm, which was invented in 1959
   by D.I.Shell is that in early stages, far-apart elements are compared,
   rather than adjacent ones as in simpler interchange sorts. This tends
   to eliminate large amounts of disorder quickly, so later stages have less
   work to do. The interval between compared elements is gradually decreased
   to one, at which point the sort effectively becomes ad adjacent interchange
   method.
*/

#include <stdio.h>

/* shellsort: sort v[0] ... v[n-1] into increasing order */
void shellsort (int v[], int n)
{
	int gap, i, j, temp;
	
	for (gap = n/2; gap > 0; gap /= 2)
		for (i = gap; i < n; i++)
			for (j = i - gap; j >= 0 && v[j] > v[j+gap]; j -= gap) {
				temp = v[j];
				v[j] = v[j + gap];
				v[j + gap] = temp;
			}
}

main()
{
	int i;
	int v[10] = {5, 4, 3, 2, 1, -1, -2, -3, -4, -5};
	
	shellsort(v, 10);
	for (i = 0; i < 10; ++i)
		printf("%d  ", v[i]);	
	printf("\n");
}

/*
-5  -4  -3  -2  -1  1  2  3  4  5
*/
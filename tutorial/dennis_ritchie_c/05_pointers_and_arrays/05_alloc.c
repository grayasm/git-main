/* Cap.5 Pointers and Arrays, pag.100

   C is consistent and regular in its approach to address arithmetic;
   its integration of pointers, arrays and address arithmetic is one of the
   strengths of the language. Let us illustrate by writing a rudimentary
   storage allocator.
*/

#include <stdio.h>


#define ALLOCSIZE 10000   /* size of available space */

static char allocbuf[ALLOCSIZE];        /* storage for alloc */
static char *allocp = allocbuf;         /* next free position */

char *alloc(int n)    /* return a pointer to n characters */
{
    if(allocbuf + ALLOCSIZE - allocp >= n) { /* it fits */
        allocp += n;
        return allocp - n;                   /* old p */
    } else            /* not enough room */
        return 0;
}


void afree(char *p)   /* free storage pointed to by p */
{
    if(p > allocbuf && p < allocbuf + ALLOCSIZE)
        allocp = p;
}


main()
{
    char *s, *q, *r;

    s = alloc(9);
    q = alloc(9);
    r = alloc(9);

    strcpy(s, "string s");
    strcpy(q, "string q");
    strcpy(r, "string r");

    printf("s=%s, q=%s, r=%s\n", s, q, r);
}

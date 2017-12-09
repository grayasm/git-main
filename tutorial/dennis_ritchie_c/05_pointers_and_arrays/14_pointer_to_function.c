/* Cap.5 Pointers and Arrays, pag.118

   In C, a function itself is not a variable, but it is possible to define
   pointers to functions, which can be assigned, placed in arrays, passed to
   functions, returned by functions, ans so on. We will illustrate this by
   modifying the sorting procedure written earlier in this chapter so that
   if the optional argument -n is given, it will sort the input lines numerically
   instead of lexicographically.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINES 5000     /* max #lines to be sorted */
char *lineptr[MAXLINES];  /* pointers to text lines */

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);

void qsort_ (void *lineptr[], int left, int right, int (*comp)(void*,void*));

int numcmp(char*, char*);

/* sort input lines */
main(int argc, char *argv[])
{
    int nlines;
    int numeric;

    if (argc > 1 && strcmp(argv[1], "-n") == 0)
        numeric = 1;
    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        qsort_ ((void**)lineptr, 0, nlines - 1,
               (int (*)(void*,void*)) (numeric ? numcmp : strcmp));
        writelines (lineptr, nlines);
        return 0;
    }
    else {
        printf("input too big to sort\n");
        return 1;
    }
}


/* qsort: sort v[left]...v[right] into increasing order */
void qsort_(void *v[], int left, int right, int (*comp)(void*, void*))
{
    int i, last;
    void swap(void *v[], int, int);

    if(left >= right)
        return;

    swap(v, left, (left + right)/2);
    last = left;
    for (i = left+1; i <= right; i++)
        if((*comp)(v[i], v[left]) < 0)
            swap(v, ++last, i);

    swap(v, left, last);
    qsort_ (v, left, last-1, comp);
    qsort_ (v, last+1, right, comp);
}

/* numcmp: compare s1 and s2 numerically */
int numcmp(char *s1, char *s2)
{
    double v1, v2;

    v1 = atof(s1);
    v2 = atof(s2);
    if (v1 < v2)
        return -1;
    else if (v1 > v2)
        return 1;
    return 0;
}

void swap(void *v[], int i, int j)
{
    void *temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}


int _getline(char s[], int lim)
{
    int c, i;

    for (i=0; i<lim-1 && (c = getchar())!= EOF && c!='\n'; ++i)
        s[i] = c;
    if (c == '\n') {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
}

#define MAXLEN 1000

/* readlines: read input lines */
int readlines(char *lineptr[], int maxlines)
{
    int len, nlines;
    char *p, line[MAXLEN];

    nlines = 0;
    while ((len = _getline(line, MAXLEN)) > 0)
        if(nlines >= maxlines || (p = (char*)malloc(len)) == NULL)
            return -1;
        else {
            line[len-1] = '\0';
            strcpy(p, line);
            lineptr[nlines++] = p;
        }
    return nlines;
}


/* writelines: write output lines */
void writelines(char *lineptr[], int nlines)
{
    int i;

    for (i=0; i < nlines; ++i)
        printf("%s\n", lineptr[i]);
}

/*
  cat file.txt
  5
  55
  6

  program -n < file.txt
  5
  6
  55
 */

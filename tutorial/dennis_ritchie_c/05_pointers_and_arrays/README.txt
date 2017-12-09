.
                      Cap.5 Pointer and Arrays
                      pag.93 - 126

  1. a "pointer to void" is used to hold any type of pointer but cannot be
     dereferenced itself
  2. in C arguments to functions are passed "by value" - in temporary copies
  3. int a[10]; int *pa; pa = &a[0]; After the assignment we say that pa and a
     have identical values.
  4. a reference to a[i] can be written as *(a+i); the 2 forms are equivalent
  5. a pointer int *pa; is a variable but an array name int a[10]; is not a
     variable, therefore pa=a; pa++; are legal and a=pa; a++; are illegal
  6. when an array name is passed to a function, what is passed is the location
     of the initial element
  7. it is possible to index backwards p[-1] or p[-2] for for positions that
     precede p[0]
  8. it is illegal to refer to objects that are not within the array bounds
  9. pointers and integers are not interchangeable. Zero is the sole exception
 10. for 2 pointers to members of the same array, the relations == != < >= etc
     work properly, comparing the addresses of the 2.
 11. there is one exception: the address of the first element past the end
     of an array can be used in pointer arithmetic
 12. pointer arithmetic operations are: p=q, p=q+2, p=q-3, p=0, p!=0, p==0
     all other operations are illegal
 13. char array[] = "...";  can modify the string, array[14] = 'm';
     char *pointer = "..."; cannot modify the string (illegal)
 14. the short version of strcpy(char *s, char *t) { while(*s++ = *t++); }
 15. f(int daytab[2][13]) is a function declaration receiving a pointer to 2
     objects that are arrays of 13 ints
 16. f(int (*daytab)[13]) is similar with the above signature
 17. int *daytab[13] is an array of 13 pointers to integers
 18. int a[10][20]; -- true 2 dimensional array, 200 int location set aside
     int *b[10];    -- only 10 pointers are set aside and not initialized
     a[3][4] and b[3][4] are both syntactically legal references to a single int
 19. The advantage of pointer array is that the rows of the array may be of
     different length. Compare the 2 declarations:
     char *name[] = { "one", "two", "five" };
     char aname[][5] = { "one", "two", "five"};
     name[0] * -> "one"
         [1] * -> "tow"
         [2] * -> "five"
     aname: one\0  two\0  five\0
           [0      5      10     ]
 20. int (*comp)(void*, void*);
     the (*comp) parantheses are needed so the components are correctly
     associated.
 21. any pointer can be cast to void* and back without loss of information
 22. x is a function returning a pointer to an array of pointers to functions
     returning char
     x () * [] * () char
     to:
     char (*(*x())[])()

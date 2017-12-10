.
                      Cap.6 Structures
                      pag. 127 - 150

  1. An optional name called a structure tag may follow the word struct.
     ex: struct point { int x; int y; };
  2. struct point pt; defines a variable pt of type struct point.
  3. struct point maxpt = { 320, 200 }; list of initializers, each a const expr.
  4. structure member operator . and -> have higher precedence than ++ -- * &
     () [] -> .     (left to right)
     ++ -- * &      (right to left)
     ------------------------------- (see more at pag.53)
     *pp.x          is  *(pp.x)
     ++p->len       is  ++(p->len)
     *p->str        is  *(p->str)
     *p++->str      is  *(p++->str)  increments p after accessing str
  5. unary operator sizeof returns a size_t <stddef.h> ; both expr are the same:
     sizeof s
     sizeof(s)
  6. Additions of 2 pointers is illegal. To find the middle between p < q use:
     m = p + (q-p)/2
  7. For a structure
     struct {
            char c;
            int ;
            };
     don't assume the size is the sum of all elements. Because of the alignment
     there might be 'holes' in a structure. It uses 8 bytes not 5.
     Always use sizeof.
  8. typedef creates new data type names. Not a new type, but a new name for an
     existing type. Ex:
     typedef int Length;
     typedef char *String;
     typedef struct tnode *Treeptr;
  9. A union is a structure in which all members have offset zero from the base.
 10. A union can be initialized with a value for its first member only.
 11. A bit-field is a set of adjacent bits within a single implementation-defined
     storage unit called a 'word'. The syntax uses a structure. Ex:
     struct {
            unsigned int is_keyword : 1;
            unsigned int is_extern  : 1;
            unsigned int is_static  : 1;
     } flags;
 12. Fields need not be named. Unnamed fields (a colon and width) are used for
     padding. Special width 0 forces alignment to next word boundary.

README is complete but the examples past pag.140 are missing.

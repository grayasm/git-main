.
                      Cap.4 Functions and Program Structure
                      pag.67 - 92

  1. if the return type is omitted, int is assumed
     dummy() {}
     main() { dummy(); }
  2. a static variable or function is valid only in the file where it is declared
  3. external static is most used for variables but can be applied to functions
     as well
  4. register variables are to be placed in machine registers, but compilers are
     free to ignore the advice
  5. external and static variables are guaranteed to be initialized to zero
  6. automatic and register variables have undefined (garbage) initial values
  7. #include "..." will search where the source program is and if not found or
  8. #include <...> search will follow and implementation-defined rule
  9. paritioning is the base concept for quicksort (see 07_parition)
 10. pay attention to calling macros like this max(a++, b++); is WRONG
 11. also #define square(x) x*x  when is called like square(z+1); is WRONG
 12. # in front of expression will expand into a quoted string
     #define dprint(expr) printf(#expr " = %g\n", expr)
     dprintf(x/y); will expand to printf("x/y " " = %g\n", x/y);

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
  5. variables may be declared at the beginning of any block structure not just
     functions
     if (n > 0) {
        int i;  /* hides any i in outer block */
  6. external and static variables are guaranteed to be initialized to zero
  7. automatic and register variables have undefined (garbage) initial values
  8. paritioning is the base concept for quicksort (see 07_parition)
  9. #include "..." will search where the source program is and if not found or
 10. #include <...> search will follow an implementation-defined rule
 11. pay attention to calling macros like this max(a++, b++); is WRONG
 12. also #define square(x) x*x  when is called like square(z+1); is WRONG
 13. # in front of expression will expand into a quoted string
     #define dprint(expr) printf(#expr " = %g\n", expr)
     dprintf(x/y); will expand to printf("x/y" " = %g\n", x/y);

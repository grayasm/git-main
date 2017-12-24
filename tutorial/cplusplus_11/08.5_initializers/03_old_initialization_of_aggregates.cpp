/* Header     : (core)
   Signature  :
   Description:

   This tutorial was found at:
   http://www.informit.com/articles/article.aspx?p=1852519

   Initialization in C++03 is tricky, to say the least, with four different
   initialization notations and far too many arbitrary restrictions and loopholes
     - no way to initialize a member array
     - no convenient way to initialize containers
     - no way to initialize dynamically allocated POD types

   Let's look at the C++03 initialization.
   Initialization of aggregates:
     - aggregate initialization requires braces, with the exception of string
       literals that may also appear between a pair of double quotes.
*/

#include <stdio.h>

struct S { int a, b; };
main()
{
    int  c1[2]  = {0, 2};
    char c2[]   = "message";
    char c3[]   = {'m','e','s','s','a','g','e','\0'};
    struct S c4 = {0, 1};

    printf("initialization of aggregates\n");
}

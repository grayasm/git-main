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

   Let's look at the C++03 initialization of fundamental types with the equal
   sign (=)
 */

#include <stdio.h>

main()
{
    int n = 0;
    void *p = 0;
    char c = 'A';

    // can use parantheses as well which are interchangeable with the (=) sign.
    int m(0);
    double d(0.5);

    printf("initialization of fundamental types\n");
}

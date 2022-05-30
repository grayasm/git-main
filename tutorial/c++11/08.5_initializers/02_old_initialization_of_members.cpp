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
   Initialization of data members in a class and objects:
     - classes with a user-defined constructor require a constructor's member
       initialization list for their data members.
 */

#include <stdio.h>

// C++03 initialization of classes and objects
class A
{
public:
    explicit A(int x, int y)
        : mx(x), my(y) {}  // mem-init

private:
    int mx, my;
};


main()
{
    A a(0, 1);  // object initializer enclosed in parantheses
    /*
    A b={0,1};  error: converting to ‘A’ from initializer list would use explicit constructor ‘A::A(int, int)’
    */

    printf("initialization of data members\n");
}

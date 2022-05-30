/* Header     : (core)
   Signature  : NX3337, pag.190
     initializer:
             brace-or-equal-initializer
             (expression-list)
     brace-or-equal-initializer:
             = initializer-clause
             braced-init-list
     initializer-clause:
             assignment-expression
             braced-init-list
     initializer-list:
             initializer-clause ...opt
             initializer-list , initializer-clause ...opt
     braced-init-list:
             { initializer-list ,opt }
             { }

   Description:

   This tutorial was found at:
   http://www.informit.com/articles/article.aspx?p=1852519

   Introducing C++11 Brace-Initialization.
   C++11 attempts to overcome the problems of C++03 initialization by
   introducing a universal initialization notation that applies to every
   type - whether:
     > a POD variable
     > a POD array
     > a class object with a user-defined constructor
     > a dynamically allocated array
     > or even a STL container.

   In C and C++03 the brace initialization uses the equal sign (={}).
   In C++11 the braces do not use the equal sign. An empty pair of brances
   indicates the default initialization. The POD types are default initialized
   to binary zeros and the non-POD types with default construction.
*/

#include <stdio.h>
#include <string>
using namespace std;


main()
{
    int n {};      // zero initialization: n is initialized to 0

    int *p {};     // initialized to nullptr

    double d {};   // initialized to 0.0

    char s[12]{};  // all 12 chars are initialized to '\0'

    string s1 {};  // same as: string s;

    char *p2 = new char[5] {};  // all five chars are initialized to '\0'

    printf("C++11 default initialization\n");
}

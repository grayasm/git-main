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

   C++11 pulls another rabbit out of its hat with class member initializers.
   Any valid initialize expression can be:
     > equal sign = 12.99
     > a pair of parantheses ("abc")
     > the new brace-init {1,2,3}
*/

#include <stdio.h>
#include <string>
using namespace std;


class C1
{
    int x = 7; // class member initializer
public:
    C1() {}
};

class C2
{
    int x[5] {1,2,3,4}; // class member initializer
public:
    C2() {}
};

class C3
{   /*
    std::string s ("abc");    error: expected identifier before string constant
    */

    double d = 0;

    char *p {nullptr};

    int x[5] {1,2,3,4}; // x[4] is initialized to zero

public:
    C3() {}
};

main()
{
    printf("C++11 class member initializers\n");
}

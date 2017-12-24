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

   The universal initializer is called a brace-init.
*/

#include <stdio.h>
#include <string>
#include <vector>
#include <map>
using namespace std;


// C++11 brace-init
class C
{
    int x[4];
public:
    C() : x {0,1,2,3} {}
};

main()
{
    int a { 0 };

    double *pa = new double[3] {0.5, 1.2, 12.99};

    string s { "Hello" };

    string s2 {s};

    map<string, string> stars {
        { "Superman", "+1 (212) 545-7890"},
        { "Batman",   "+1 (212) 545-0987"}
    };

    printf("C++11 brace init\n");
}

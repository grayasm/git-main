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

   An initializer list lets you use a sequence of values wherever an initailizer
   can appear.
*/

#include <stdio.h>
#include <vector>
using namespace std;

main()
{
    vector<int>    vi {1,2,3,4,5,6};
    vector<double> vd {0.5, 1.33, 2.66};

    printf("C++11 initializer list\n");
}

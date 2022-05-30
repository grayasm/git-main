/* C++11 N3337.pdf pag.128
   6.5.4 The range-based for statement

   Header      : none (core)
   Signature   : for ( for-range-declaration : expression ) statement
                 for ( for-range-declaration : braced-init-list ) statement
   Description :

   In each case, a range-based for statement is equivalent to:
   {
       auto && range = range-init;
       for (auto begin = begin-expr, end = end-expr; begin != end; ++begin)
       {
           for-range-declaration = *begin;
           statement
       }
   }

   range-based for requirements:
   > begin() and end() methods, either members or standalone
   > iterator must support operators: *  != and prefix ++, either as member or
   standalone functions.
*/

#include <stdio.h>
#include <vector>
using namespace std;


main()
{
    vector<int> vi { -5, -4, -3, -2, -1 };
    printf("vi = ");

    for (int x : vi)
        printf("%d ", x);
}
/*
vi = -5 -4 -3 -2 -1
*/

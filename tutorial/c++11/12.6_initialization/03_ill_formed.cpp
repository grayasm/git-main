/*  C++11 N3337.pdf pag.255

    If a constructor delegates to itself directly or indirectly, the program
    is ill-formed; no diagnostic is required.
*/

#include <stdio.h>


class C {
public:
    C(int value) { }         // #1: non-delegating constructor
    C(): C(42) { }           // #2: delegates to #1
    C(char c) : C(42.0) { }  // #3: ill-formed due to recursion with #4
    C(double d) : C('a') { } // #4: ill-formed due to recursion with #3
};

main()
{
    C c('a');
}
/*
Segmentation fault
*/

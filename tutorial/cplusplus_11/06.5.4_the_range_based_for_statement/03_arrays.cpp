/* Experimenting with range-based for loops and arrays. */

#include <iostream>
using namespace std;


main()
{
    int itab[5] = {0, 1, 2, 3, 4};
    for (int i : itab)  // OK
        cout << i << " ";
    cout << endl;

    int *ptab[5] = {itab+0, itab+1, itab+2, itab+3, itab+4};
    for (int *p : ptab)  // OK
        cout << *p << " ";
    cout << endl;


    void func(int tab[5]);
    func(itab);  // Not OK, array is passed as a pointer
}


void func(int tab[5])
{
    /* Remeber the pointers and arrays are similar but still different.
       sizeof(array) will return the number of elements.
       sizeof(pointer) does not help, you need to know the size upfront.
       Here, the formal argument is an array, but is passed to func as a pointer
       which is useless.
    */
#if 0
    // error: no matching function for call to 'begin(int*&)'
    for (int i : tab)
        cout << i << " ";
#endif
}

/*
0 1 2 3 4
0 1 2 3 4
 */

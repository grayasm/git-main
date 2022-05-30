/* Experimenting with a custom container.

   range-based for loop requirements:
   1) begin() and end() , member or standalone methods
   2) returning iterator that supports operators: *, != and prefix ++
*/

#include <iostream>
using namespace std;


class Simple10
{
    int array[10];
public:
    Simple10()
    {
        for (int i : {0,1,2,3,4,5,6,7,8,9})  /* using braced-init-list */
            array[i] = i+10;
    }

    /* int* will satisfy all iterator requirements */
    const int* begin() const { return &array[0]; }
    const int* end() const { return &array[0] + 10; }
};

main()
{
    Simple10 s10;
    for (int i : s10)
        cout << i << " ";
    cout << endl;
}
/*
  10 11 12 13 14 15 16 17 18 19
*/

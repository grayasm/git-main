/* Cap.6 Structures

   A structure can be initialized by following its definition with a list of
   initializers, each a constant expression, for the memebes.
*/

#include <stdio.h>

struct point {
    int x;
    int y;
};


main()
{
    struct point pt;
    struct point maxpt = { 320, 200 };

    pt = maxpt;

    printf("%d,%d\n", pt.x, pt.y);
}

/* Cap.6 Structures, pag.129

   Structures can be copied, assigned, used by address with & and have their
   member accessed. Structures can be passed as arguments to functions and
   returned as value from functions.
   Can be initialized by a list of constant member values.
   An automatic structure may also be initialized by an assignment.
*/

#include <stdio.h>


struct point {
    int x;
    int y;
};

struct point makepoint(int x, int y)
{
    struct point temp;
    temp.x = x;
    temp.y = y;
    return temp;
}

struct point addpoint(struct point p1, struct point p2)
{
    p1.x += p2.x;
    p1.y += p2.y;
    return p1;
}

struct rect {
    struct point ll;
    struct point ur;
};

main()
{
    struct rect screen;
    struct point middle;
    struct point makepoint(int,int);

    screen.ll = makepoint(0, 0);
    screen.ur = makepoint(540, 420);
    middle = makepoint((screen.ll.x + screen.ur.x)/2,
                       (screen.ll.y + screen.ur.y)/2);
}

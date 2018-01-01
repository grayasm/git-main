/*  https://www.cprogramming.com/c++11/c++11-nullptr-strongly-typed-enum-class.html

    C++11 enum classes support forward declaration.
*/

#include <stdio.h>

enum class Mood;
void f(Mood m);

// later on:
enum class Mood { AMUSED, ANGRY, ANNOYED, WEIRD };

void f(Mood m)
{
    if(m != Mood::AMUSED)
        printf("You're not AMUSED.\n");
    else
        printf("Why are you AMUSED?\n");
}

main()
{
    f(Mood::WEIRD);
}

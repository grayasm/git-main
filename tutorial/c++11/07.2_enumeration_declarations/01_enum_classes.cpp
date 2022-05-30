/*  http://www.learncpp.com/cpp-tutorial/4-5a-enum-classes/

    Although enumerated types are distinct types in C++, they are not type
    safe, and in some cases will allow you to do things that don't make sense.

    Consider the following case:
*/

#include <stdio.h>

main()
{
    enum Color
    {
        RED, // RED is placed in the same scope as Color
        GREEN,
        BLUE
    };

    enum Fruit
    {
        BANANA, // BANANA is placed in the same scope as Fruit
        APPLE,
        ORANGE
    };

    Color color = RED;   /* Color and RED can be accessed in the same scope, and
                            no prefix is needed
                         */
    Fruit fruit = BANANA;

    if (color == fruit)   /* The compiler will compare a and b as integers */
        printf("color and fruit are equal\n");  /* and they are EQUAL! */
    else
        printf("color and fruit are not equal\n");


    enum ExoticFruit
    {
        PAPAYA,
        COCOS,
#if 0
        // error: redeclaration of 'BANANA'
        BANANA
#endif
    };
}

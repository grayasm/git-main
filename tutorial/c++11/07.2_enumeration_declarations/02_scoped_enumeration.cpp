/*  http://www.learncpp.com/cpp-tutorial/4-5a-enum-classes/

    C++11 defines a new concept, the enum class, also called scoped enumeration
    which makes enumeration both strongly typed and strongly scoped.

    To make an enum class, we use the keyword class after the enum keyword.
    Here's an example:
*/

#include <stdio.h>

main()
{
    enum class Color
    {
        RED, /* RED is inside the scope of Color */
        GREEN,
        BLUE
     };

    enum class Fruit
    {
        BANANA,
        APPLE,
        ORANGE
    };

    Color color = Color::RED;    /* RED is not directly accessible any more */
    Fruit fruit = Fruit::BANANA; /* We have to use the full scope to access
                                    the enumeration. */

#if 0
    // error: no match for 'operator=='
    if (color == fruit)
        printf("color and fruit are equal\n");
    else
        printf("color and fruit are not equal\n");
#endif
}

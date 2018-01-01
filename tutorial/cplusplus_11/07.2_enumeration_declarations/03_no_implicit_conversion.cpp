/*  http://www.learncpp.com/cpp-tutorial/4-5a-enum-classes/

    The strong typing rules means that each enum class is considered a unique
    type. This means that the compiler will not implicitly compare enumerators
    from different enumerations. If you try to do so, the compiler will throw
    an error.

    With enum classes the compiler will no longer implicitly convert enumerator
    values to integers.
*/

#include <stdio.h>


main()
{
    enum class Color
    {
        RED,
        BLUE
    };

    Color color = Color::RED;
    /* You can still compare enumerators from within the same enum class. */
    if (color == Color::RED)
        printf("The color is red\n");
    else
        printf("The color is not red\n");


    /* You can still explicitly convert an enum class enumerator to an integer
       by using a static_cast to int:
    */
    printf("The color integer is %d\n", static_cast<int>(color));
}

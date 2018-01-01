/*  https://www.cprogramming.com/c++11/c++11-nullptr-strongly-typed-enum-class.html

    You can set the size of your enum class.
    You can use any signed or unsigned integer type. It defaults to int, but you
    can also use char, unsigned long, etc. This will ensure some measure of
    compatibility across compilers.
*/

#include <stdio.h>
#include <cstdint>


main()
{
    enum class Color : char { RED = 1, GREEN = 2, BLUE = 3 };
    enum class County : std::int16_t { KNOX = 18081, LAKE = 18089, MARSCHALL = 18099 };

    printf("sizeof(Color::RED) = %d\n", sizeof(Color::RED));
    printf("sizeof(County::KNOX= %d\n", sizeof(County::KNOX));
}
/*
sizeof(Color::RED) = 1
sizeof(County::KNOX= 2
*/

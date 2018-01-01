/*  https://www.cprogramming.com/c++11/c++11-nullptr-strongly-typed-enum-class.html

 */


/* C++03 enums are essentially integers;
   They can be compared with integers or with other enums of different types.
   C++03 enums are unscoped and they are defined at the same level of enum.
*/

#if 0 // this code won't compile!
enum Color { RED, GREEN, BLUE };
enum Feelings { EXCITED, MOODY, BLUE };
#endif


/* C++11 enum classes are scoped and the cannot be converted to other types.
   The use of word 'class' is meant to indicate that each enum type really is
   different and not comparable to other enum types.
   This code will compile with C++11.
*/
enum class Color { RED, GREEN, BLUE };
enum class Feelings { EXCITED, MOODY, BLUE };

/* To access an enum class value you must write the full qualified name. Ex: */
void func()
{
    Color color = Color::GREEN;
    if (Color::RED == color) { /* the color is red */ }
}


/* C++11 enum classes support forward declaration. */
enum class Mood;
void assessMood (Mood m);

// later on:
enum class Mood { EXCITED, MOODY, BLUE };


/* You can set the size of your enum class.
   You can use any signed or unsigned integer type. It defaults to int, but you
   can also use char, unsigned long, etc. This will ensure some measure of
   compatibility across compilers.
*/

enum class Colors : char { RED = 1, GREEN = 2, BLUE = 3 };

/* Specifying the exact size of the enum, using cstdint. */
#include <cstdint>
enum class Country : std::int8_t { USA = 1, CANADA = 2, UK = 3 };

main()
{
}

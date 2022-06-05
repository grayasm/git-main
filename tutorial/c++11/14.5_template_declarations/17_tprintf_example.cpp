/* N3337 page 319, 14.5.3 Variadic templates [temp.variadic]
   See README.txt for variadic template syntax.
   Sample code from https://en.cppreference.com/w/cpp/language/parameter_pack

   compile with:
       g++ -g -std=c++11 -o exe 17_tprintf_example.cpp


   The below example defines a function similar to std::printf, that replace
   each occurance of the character % in the format string with a value.
 */

#include <iostream>

void tprintf(const char* format) {
    std::cout << format;
}

template<typename T, typename... Targs>
void tprintf(const char* format, T value, Targs... args)
{
    for (; *format != '\0'; format++)
    {
        if (*format == '%')
        {
            std::cout << value;
            tprintf (format + 1, args...);
            return;
        }
        std::cout << *format;
    }
}


int main()
{
    tprintf("%s world% %\n", "Hello", '!', 123);
}

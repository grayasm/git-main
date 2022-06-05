/*
  see README.txt

  https://github.com/AnthonyCalandra/modern-cpp-features#user-defined-literals

  User-defined literals

  User-defined literals allow you to extend the language and add your own
  syntax. To create a literal, define a:

      T operator "" X(...) { ... }

  function that returns a type T, with a name X.
  Note that the name of this function defines the name of the literal.
  Any literal names not starting with an underscore are reserved and won't
  be invoked. There are rules on what parameters a user-defined literal
  function should accept, according to what type the literal is called on.
 */

#include <iostream>
#include <cmath>
#include <string>


long long operator "" _celsius(unsigned long long tempCelsius) {
    return std::llround(tempCelsius * 1.8 + 32);
}

int operator "" _int(const char* str, std::size_t) {
    return std::stoi (str);
}


int main(){

    // Converting Celsius to Fahrenheit
    std::cout << "24_celsius=" << 24_celsius << "\n"; // 75

    // String to integer conversion
    std::cout << "\"123\"_int=" << "123"_int << "\n"; // 123, with type 'int'

}

/* N3337 page 319, 14.5.3 Variadic templates [temp.variadic]
   See README.txt for variadic template syntax.
   Sample code from https://en.cppreference.com/w/cpp/language/parameter_pack

   compile with:
       g++ -g -std=c++11 -o exe 15_sizeof_operator.cpp


   The sizeof... operator is classified as a pack expansion as well:
 */
#include <cstddef>

template<class... Types>
struct count
{
    static const std::size_t value = sizeof...(Types);
};


int main(){

    size_t sz = count<int,short,const char*>::value; // 3 template arguments
}

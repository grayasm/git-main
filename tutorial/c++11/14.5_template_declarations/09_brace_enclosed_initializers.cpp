/* N3337 page 319, 14.5.3 Variadic templates [temp.variadic]
   See README.txt for variadic template syntax.
   Sample code from https://en.cppreference.com/w/cpp/language/parameter_pack

   compile with:
       g++ -g -std=c++11 -o exe 09_brace_enclosed_initializers.cpp


   In a braced-init-list (brace-enclosed list of initializers and other
   braced-init-lists, used in list-initialization and some other contexts),
   a pack expansion may appear as well:
 */
#include <iostream>

template<typename... Ts>
void f(Ts... args)
{
    const int size = sizeof...(args) + 2;
    int res[size] = {1, args..., 2};

    // since initializer lists guarantee sequencing, this can be used to
    // call a function on each element of a pack, in order:
    int dummy[sizeof...(Ts)] = {(std::cout << args, 0)...};
}


int main(){

    f(1, 2, 3);

}

/* N3337 page 319, 14.5.3 Variadic templates [temp.variadic]
   See README.txt for variadic template syntax.
   Sample code from https://en.cppreference.com/w/cpp/language/parameter_pack

   compile with:
       g++ -g -std=c++11 -o exe 03_position_of_parameter_pack.cpp

   In a primary class template, the template parameter pack must be the final
   parameter in the template parameter list.

   In a function template, the template parameter pack may appear earlier in
   the list provided that all following parameters can be deduced from the
   function arguments, or have default arguments:
 */

template<typename U, typename... Ts> struct valid {  // OK: can deduce U
};
valid<double, int, int> v1;   // U is dobule, Ts is {int, int}

#if 0
template<typename... Ts, typename U> struct invalid { // error: Ts... not at the end
};
#endif


template<typename... Ts, typename U, typename=void>
void func1(U u, Ts... ts) {   // OK: can deduce U
}

#if 0
template<typename... Ts, typename U, typename=void>
void func2(Ts..., U u) {      // error: Ts... cannot be used
}
#endif


int main(){
    func1(1.0, 1,2,3);        // OK: deduces U as double, Ts as {int,int,int}
}

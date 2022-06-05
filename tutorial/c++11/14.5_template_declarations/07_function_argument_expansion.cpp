/* N3337 page 319, 14.5.3 Variadic templates [temp.variadic]
   See README.txt for variadic template syntax.
   Sample code from https://en.cppreference.com/w/cpp/language/parameter_pack

   compile with:
       g++ -g -std=c++11 -o exe 07_function_argument_expansion.cpp

   A pack expansion may appear inside the parantheses of a function call
   operator, in which case the largest expression or braced-init-list
   to the left of the ellipsis in the pattern that is expanded:
 */

template<class... Args> void f (Args... args) { }

template<class... Args>
void sample(Args... args) {

    f(&args...);              // expands to f(&E1, &E2, &E3)
    f(1, ++args...);          // expands to f(n, ++E1, ++E2, ++E3)
    f(++args..., 1);          // expands to f(++E1, ++E2, ++E3, n);
    f(const_cast<const Args*>(&args)...);
    // f(const_cast<const E1*>(&X1, const_cast<const E2*>(&X2), const_cast<const E3*>(&X3))
}


int main() {
}

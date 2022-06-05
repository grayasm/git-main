/* N3337 page 319, 14.5.3 Variadic templates [temp.variadic]
   See README.txt for variadic template syntax.
   Sample code from https://en.cppreference.com/w/cpp/language/parameter_pack

   compile with:
       g++ -g -std=c++11 -o exe 08_parenthesized_initializers.cpp

   A pack expansion may appear inside the parantheses of a direct initializer,
   a function-style cast and other contexts (member initializer, new-expression,
   etc) in which case the rules are identical to the rules for a function call
   expression above:
 */
#include <utility>

template<class... Args>
class A {
public:
    A(Args... args) {
    }
};


template<class... Args>
void sample(Args... args) {

    A<> a1 (&args...);                  // calls A::A(&E1, &E2, &E3)
    A<> a2 = A<>(1, ++args...);         // calls A::A(n, ++E1, ++E2, ++E3)
    A<> a3(std::forward<Args>(args)...);
}


int main() {
}

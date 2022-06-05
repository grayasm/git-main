/* N3337 page 319, 14.5.3 Variadic templates [temp.variadic]
   See README.txt for variadic template syntax.
   Sample code from https://en.cppreference.com/w/cpp/language/parameter_pack

   compile with:
       g++ -g -std=c++11 -o exe 06_nested_pack_expansion.cpp


   If a pack expansion is nested within another pack expansion, the parameter
   packs that appear inside the innermost pack expansion are expanded by it,
   and there must be another pack mentioned in the enclosing pack expansion,
   but not in the innermost one:
 */
template<typename... Args>
void f(Args...) {
}

template<typename T, typename... Args>
T h(T t, Args... args) {
    return t;
}

template<class... Args>
void g (Args... args)
{
    f (h(args...) + args...);

    // Nested pack expansion
    // inner pack expansion is "args...", it is expanded first
    // outter pack expansion is h(E1, E2, E3) + args..., it is expanded
    // second (as h(E1, E2, E3) + E1, h(E1, E2, E3) + E2, h(E1, E2, E3) + E3)
}



int main() {
    g (1, 2, 3);
}

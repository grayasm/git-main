/* N3337 page 319, 14.5.3 Variadic templates [temp.variadic]
   See README.txt for variadic template syntax.
   Sample code from https://en.cppreference.com/w/cpp/language/parameter_pack

   compile with:
       g++ -g -std=c++11 -o exe 04_one_pack_expansion.cpp


   A pattern followed by an ellipsis, in which the name of at least one parameter
   pack appears at least once, is expanded into zero or more comma-separated
   instantiation of the pattern, where the name of the parameter pack
   is replaced by each of the elements from the pack, in order.
 */

template<class... Us> void f (Us... args) {
};

template<class... Ts> void g (Ts... args) {
    f (&args...);        // "&args..." is a pack expansion
                         // "&args"    is its pattern
};


int main() {
    g (1, 0.2, "a");     // Ts... args expand to int, double, const char*
                         // &args... expands to &int, &double, &(const char*)
                         // Us... args expand to int*, double*, const char**
}

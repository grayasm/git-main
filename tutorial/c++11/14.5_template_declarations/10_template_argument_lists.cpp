/* N3337 page 319, 14.5.3 Variadic templates [temp.variadic]
   See README.txt for variadic template syntax.
   Sample code from https://en.cppreference.com/w/cpp/language/parameter_pack

   compile with:
       g++ -g -std=c++11 -o exe 10_template_argument_lists.cpp


   Pack expansions can be used anywhere in a template argument list, provided
   the template has the parameters to match the expansion:
 */
template<class... Ts>
class container {
};

template<class A, class B, class... C>
void f(A a, B b, C... args)
{
    container<A, B, C...> t1;   // expands to container<A, B, E1, E2, E3>
    container<C..., A, B> t2;   // expands to container<E1, E2, E3, A, B>
    container<A, C..., B> t3;   // expands to container<A, E1, E2, E3, B>
}


int main(){
}

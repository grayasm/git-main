/* N3337 page 319, 14.5.3 Variadic templates [temp.variadic]
   See README.txt for variadic template syntax.
   Sample code from https://en.cppreference.com/w/cpp/language/parameter_pack

   compile with:
       g++ -g -std=c++11 -o exe 14_lambda_clause_expansion.cpp


   Lambda captures.
   Pack expansion may appear in the capture clause of a lambda expression:
 */

template<class... Args> void g (Args... args) { }

template<class... Args>
void f(Args... args)
{
    auto lm = [&, args...] { return g(args...); };
    lm();
}


int main(){
}

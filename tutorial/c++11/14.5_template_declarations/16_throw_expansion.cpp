/* N3337 page 319, 14.5.3 Variadic templates [temp.variadic]
   See README.txt for variadic template syntax.
   Sample code from https://en.cppreference.com/w/cpp/language/parameter_pack

   compile with:
       g++ -g -std=c++11 -o exe 16_throw_expansion.cpp


   The list of exceptions in a dynamic exception specification may also be a
   pack expansion:
 */


template<class... X>
void f(int arg) throw (X...)
{
    // ... throw different Xs in different situations
}


int main(){

    f(10);

}

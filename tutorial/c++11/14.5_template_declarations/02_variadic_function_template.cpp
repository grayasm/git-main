/* N3337 page 319, 14.5.3 Variadic templates [temp.variadic]
   See README.txt for variadic template syntax.
   Sample code from https://en.cppreference.com/w/cpp/language/parameter_pack

   compile with:
       g++ -g -std=c++11 -o exe 02_variadic_function_template.cpp

   A variadic function template can be called with any number of function
   arguments (the template arguments are deduced through template argument
   deducing):
 */

template<class... Types> void f(Types... args){
}

int main(){
    f();            // OK: args contains no arguments
    f(1);           // OK: args contains one argument: int
    f(2, 1.0);      // OK: args contains two arguments: int and double
}

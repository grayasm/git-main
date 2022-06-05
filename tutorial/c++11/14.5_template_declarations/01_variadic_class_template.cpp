/* N3337 page 319, 14.5.3 Variadic templates [temp.variadic]
   See README.txt for variadic template syntax.
   Sample code from https://en.cppreference.com/w/cpp/language/parameter_pack

   compile with:
       g++ -g -std=c++11 -o exe 01_variadic_class_template.cpp

   A variadic class template can be instantiated with any number of template
   arguments.
 */


template<class... Types> struct Tuple {
};

Tuple<>             t0;   // Types contains no arguments
Tuple<int>          t1;   // Types contains one argument: int
Tuple<int, float>   t2;   // Types contains two arguments: int and float
#if 0
Tuple<0>            t3;   // error: 0 is not a type
#endif


int main() {
}

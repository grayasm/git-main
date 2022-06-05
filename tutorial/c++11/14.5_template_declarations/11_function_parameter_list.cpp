/* N3337 page 319, 14.5.3 Variadic templates [temp.variadic]
   See README.txt for variadic template syntax.
   Sample code from https://en.cppreference.com/w/cpp/language/parameter_pack

   compile with:
       g++ -g -std=c++11 -o exe 11_function_parameter_list.cpp


   In a function parameter list, if an ellipsis appears in a parameter
   declaration (whether it names a function parameter pack (as in, Args... args)
   or not) the parameter declaration is the pattern:
 */

template<typename... Ts>
void f(Ts...) { }

template<typename... Ts, int... N>
void g(Ts (&...arr)[N]) { }


void sample() {

    f('a', 1);          // Ts... expands to void f(char, int)
    f(0.1);             // Ts... expands to void f(double)

    int n[1];
    g<const char, int>("a", n);    // Ts (&...arr)[N] expands to
                                   // const char (&)[2], int(&)[1]
}


int main(){
}



/*  Note: In the pattern Ts (&...arr)[N], the ellipsis is the innermost element,
          not the last element as in all other pack expansions.

    Note: Ts (&...)[N] is not allowed because the C++11 grammar requires
          the paranthesized ellipsis to have a name (e.g. "arr")
 */

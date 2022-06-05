/* N3337 page 319, 14.5.3 Variadic templates [temp.variadic]
   See README.txt for variadic template syntax.
   Sample code from https://en.cppreference.com/w/cpp/language/parameter_pack

   compile with:
       g++ -g -std=c++11 -o exe 12_template_parameter_list.cpp


   Pack expansion may appear in a template parameter list:
 */

template<typename... T>
struct value_holder
{
    template<T... Values>     // expands to a non-type template parameter
    struct apply { };         // list, such as <int, char, int(&)[5]>
};


int main(){
}

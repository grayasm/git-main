/* N3337 page 319, 14.5.3 Variadic templates [temp.variadic]
   See README.txt for variadic template syntax.
   Sample code from https://en.cppreference.com/w/cpp/language/parameter_pack

   compile with:
       g++ -g -std=c++11 -o exe 13_base_class_expansion.cpp


   A pack expansion may designate the list of base classes in a class declaration.
   Typically, this also means that the constructor needs to use a pack expansion
   in the member initializer list to call the constructor of these bases:
 */

template<class... Ts>
class A : public Ts...
{
public:
    A(const Ts&... ts) : Ts(ts)... { }
};

struct B { };
struct C { };


int main(){

    B b;
    C c;

    A<B, C> a(b, c);
}

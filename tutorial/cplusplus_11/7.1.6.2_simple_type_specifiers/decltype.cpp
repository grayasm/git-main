/* Header     : core functionality
   Signature  : decltype (entity)
                decltype (expression)
   Description: inspects the declared type of an entity or the type and value
                category of an expression

   See: http://en.cppreference.com/w/cpp/language/decltype
*/


#include <iostream>


struct A
{
    double x;
};

template<typename T, typename U>
auto add(T t, U u) -> decltype(t + u)  // type dependes on template parameters
{
    return t + u;
}


int main()
{
    int i = 33;
    decltype(i) j = i * 2;

    std::cout << "i=" << i << ", j=" << j << std::endl;

    auto f = [](int a, int b) -> int { return a * b; };

    decltype(f) g = f;
    i = f(2, 2);
    j = g(3, 3);

    std::cout << "i=" << i << ", j=" << j << std::endl;

    const A* a = new A{0};
    decltype(a->x) y;               // type double
    decltype((a->x)) z = y;         // type const double& (lvalue expression)

    std::cout << "add(100, 2.2)=" << add<int, float>(100, 2.2) << std::endl;

    return 0;
}

#include <iostream>
#include <memory>

using namespace std;

template<typename X, typename Y>
class Test
{
public:
    static const bool result = false;
};

template<typename T>
class Test<T, T>
{
public:
    static const bool result = true;
};

class A {}; class B : public A {}; class C {};

main()
{
    cout << "<A,B>=" << Test<A,B>::result << endl;
    cout << "<B,C>=" << Test<B,C>::result << endl;
    cout << "<B,B>=" << Test<B,B>::result << endl;
}

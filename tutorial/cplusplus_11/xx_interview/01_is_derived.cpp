#include <iostream>
#include <memory>

using namespace std;


template<typename D, typename B>
class Ask
{
    static void Test_(B*) { cout << "derived\n"; }
    static void Test_(...) { cout << "not-derived\n"; }

public:
    static void Test(D* d, B* b)
    {
        Test_(d);
    }
};

class A {}; class B : public A {}; class C {};

main()
{
    A *a = new A;
    B *b = new B;
    C* c = new C;

    Ask<B,A>::Test(b, a);
    Ask<C,A>::Test(c, a);
    Ask<A,A>::Test(a, a);
    Ask<A,B>::Test(a, b);
}

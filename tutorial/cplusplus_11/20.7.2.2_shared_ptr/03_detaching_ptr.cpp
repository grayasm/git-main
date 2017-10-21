/* http://thispointer.com/learning-shared_ptr-part-1-usage-details/
   Detaching the associated raw pointer

*/

#include <iostream>
#include <string>
#include <memory>    // shared_ptr

using namespace std;

int main()
{
    std::shared_ptr<string> p1(new string("new shared_ptr"));
    std::shared_ptr<string> p2 = p1;
    std::shared_ptr<string> p3 = p2;

    cout << "p1.use_count=" << p1.use_count() << '\n';  // 3
    cout << "*p3 =" << *p3 << '\n';

    p1.reset();

    cout << "p1.reset()" << '\n';
    cout << "p1.use_count=" << p1.use_count() << '\n';  // 0
    cout << "p3.use_count=" << p3.use_count() << '\n';  // 2

    p1.reset(new string("reset to new string"));

    cout << "p1.reset(new string(..))" << '\n';
    cout << "*p1=" << *p1 << '\n';

    p1 = nullptr;

    cout << "p1 = nullptr" << '\n';
    cout << "p1.use_count=" << p1.use_count() << '\n';

    return 0;
}

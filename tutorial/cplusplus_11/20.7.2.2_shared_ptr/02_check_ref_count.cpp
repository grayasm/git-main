/* http://thispointer.com/learning-shared_ptr-part-1-usage-details/

   Checking reference count of a shared_ptr object
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

    cout << "p1.use_count=" << p1.use_count() << '\n';
    cout << "p2.use_count=" << p2.use_count() << '\n';
    cout << "p3.use_count=" << p3.use_count() << '\n';

    p1 = std::make_shared<string>("make_shared");

    cout << "*p1=" << *p1 << '\n';
    cout << "*p2=" << *p2 << '\n';
    cout << "*p3=" << *p3 << '\n';

    cout << "p1.use_count=" << p1.use_count() << '\n';
    cout << "p2.use_count=" << p2.use_count() << '\n';
    cout << "p3.use_count=" << p3.use_count() << '\n';

    return 0;
}

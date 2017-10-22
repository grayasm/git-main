/* http://thispointer.com/c11-tutorial/
   http://thispointer.com/learning-shared_ptr-part-1-usage-details/

   Creating a shared_ptr object
*/

#include <iostream>
#include <string>
#include <memory>  // shared_ptr


using namespace std;

int main()
{
    std::shared_ptr<string> p1(new string("new string"));
    std::shared_ptr<string> p2 = p1;
    std::shared_ptr<string> p3 = std::make_shared<string>("make_shared");
    // std::shared_ptr<string> p4 = new string("error");

    cout << "*p1=" << *p1 << '\n';
    cout << "*p2=" << *p2 << '\n';
    cout << "*p3=" << *p3 << '\n';

    return 0;
}

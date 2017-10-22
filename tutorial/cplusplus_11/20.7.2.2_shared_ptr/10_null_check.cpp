/* http://thispointer.com/c11-tutorial/
   http://thispointer.com/how-shared_ptr-object-is-different-from-a-raw-pointer/

   NULL check
*/

#include <iostream>
#include <memory>

using namespace std;

int main()
{
    std::shared_ptr<int> p3;

    if (!p3)
        cout << "p3 is empty\n";
    if (p3 == NULL)
        cout << "p3 is empty\n";
    if (p3 == nullptr)
        cout << "p3 is empty\n";

    return 0;
}

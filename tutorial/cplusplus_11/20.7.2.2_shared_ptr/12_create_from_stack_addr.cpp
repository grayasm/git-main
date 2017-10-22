/* http://thispointer.com/c11-tutorial/
   http://thispointer.com/create-shared_ptr-objects-carefully/

   Don't create shared_ptr object from addresses on stack.
*/

#include <iostream>
#include <memory>

using namespace std;

int main()
{
    int x = 12;

    std::shared_ptr<int> p(&x);

    return 0;

    // program will crash
}

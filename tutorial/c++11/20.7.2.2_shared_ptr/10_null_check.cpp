/* Header     : <memory>
   Signature  : see README.txt for complete signature
   Description:
        - shared_ptr is a smart pointer that retains shared ownership of an
          object through a pointer. Several shared_ptr objects may own the same
          object. The object is detroyed and its memory deallocated when either
          of the following happens:
             * the last remaining shared_ptr owning the object is detroyed
             * the last remaining shared_ptr owning the object is assigned
               another pointer via operator= or reset()
        - the object is detroyed using delete-expression or a custom deleter
          that is supplied to shared_ptr during construction
        - shared_ptr can be accessed safely from multiple thread only by using
          std::atomic...<std::shared_ptr> functions, defined in header <atomic>

   -----------------------------------------------------------------------------
   http://thispointer.com/c11-tutorial/
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

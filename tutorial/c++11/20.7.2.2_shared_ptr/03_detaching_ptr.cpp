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
   http://thispointer.com/learning-shared_ptr-part-1-usage-details/

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

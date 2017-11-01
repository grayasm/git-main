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

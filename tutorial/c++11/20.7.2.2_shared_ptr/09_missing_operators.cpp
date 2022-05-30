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

   Let's compare shared_ptr and raw pointer based on following aspects.
*/

#include <iostream>
#include <memory>

using namespace std;

struct Sample
{
    void dummy()
    {
        cout << __FUNCTION__ << '\n';
    }
};


int main()
{
    std::shared_ptr<Sample> p1 = std::make_shared<Sample>();

    (*p1).dummy(); // Will work
    p1->dummy();    // Will work

    /* --- this will not compile ---
       p1[0]->dummy();
       p1++;
       p1--;
    */

    std::shared_ptr<Sample> p2(p1);
    if (p1 == p2)   // Will work
        cout << "p1 and p2 are equal\n";

    return 0;
}

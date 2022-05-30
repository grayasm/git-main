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
   http://thispointer.com/shared_ptr-and-custom-deletor/

   Custom deleter as lambda function
*/


#include <iostream>
#include <memory>

using namespace std;

struct Sample
{
    Sample()
    {
        cout << "CONSTRUCTOR\n";
    }
    ~Sample()
    {
        cout << "DESTRUCTOR\n";
    }
};

int main()
{
    std::shared_ptr<Sample> p4(new Sample[12],
                               [](Sample* x)
                               {
                                   cout << "DELETER LAMBDA CALLED\n";
                                   delete[] x;
                               });
    return 0; 
}

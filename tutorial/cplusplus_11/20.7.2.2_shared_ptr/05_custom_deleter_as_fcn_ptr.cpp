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

   Custom deleter as function pointer
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

// function that calls the delete[] on received pointer
void deleter(Sample* x)
{
    cout << "DELETER FUNCTION CALLED\n";
    delete[] x;
}

int main()
{
    // creating a shared_ptr with a custom deleter
    std::shared_ptr<Sample> p3(new Sample[12], deleter);
    return 0;
}

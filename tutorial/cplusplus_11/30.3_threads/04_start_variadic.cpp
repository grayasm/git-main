/* This tutorial is copied from:
   http://thispointer.com/c11-multithreading-part-3-carefully-pass-arguments-to-threads
   http://thispointer.com/c11-tutorial

   Pass the pointer to member function as callback function and pass pointer
   to object as second argument.
*/

#include <iostream>
#include <thread>


class Dummy
{
public:
    Dummy(){ }
    Dummy(const Dummy& obj){ }
    void sample_fcn(int x)
    {
        std::cout << __FUNCTION__ << ", x = " << x << std::endl;
    }
};


int main()
{
    Dummy dummy;
    int x = 10;

    std::thread t(&Dummy::sample_fcn, &dummy, x);
    t.join();

    return 0;
}

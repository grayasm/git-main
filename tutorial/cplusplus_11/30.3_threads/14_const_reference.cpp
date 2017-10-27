/* This tutorial is copied from:
   http://thispointer.com/c11-multithreading-part-3-carefully-pass-arguments-to-threads
   http://thispointer.com/c11-tutorial

   How to pass references to thread.
   As arguments are copied to new threads stack, so you pass the references
   in common way.
*/

#include <iostream>
#include <thread>


void new_thread(int const& val)
{
    int& y = const_cast<int&>(val);
    y++;
    std::cout << __FUNCTION__ << ", y = " << y << std::endl;
}


int main()
{
    int val = 9;
    std::cout << "before, val = " << val << std::endl;

    std::thread threadObj (new_thread, val);
    threadObj.join();

    std::cout << "after, val = " << val << std::endl;

    return 0;
}

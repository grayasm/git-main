/* This tutorial is copied from:
   http://thispointer.com/c11-multithreading-part-3-carefully-pass-arguments-to-threads
   http://thispointer.com/c11-tutorial

   Even if new_thread accepts arguments as reference still changes done inside
   it are not visible outside the thread. It's because the arg in the thread
   function is reference to the temporary value copied at the new thread's
   stack. To fix this use std::ref()
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

    std::thread threadObj (new_thread, std::ref(val));
    threadObj.join();

    std::cout << "after, val = " << val << std::endl;

    return 0;
}

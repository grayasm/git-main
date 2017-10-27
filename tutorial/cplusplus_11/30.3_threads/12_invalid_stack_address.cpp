/* This tutorial is copied from:
   http://thispointer.com/c11-multithreading-part-3-carefully-pass-arguments-to-threads
   http://thispointer.com/c11-tutorial

   Don't pass addresses of variables from local stack to thread's callback
   function, because it might be possible that local variable in thread1
   goes out of scope and thread2 to still try to access it trough it's address.
   In such scenario accessing invalid address can cause unexpected behavior.
*/

#include <iostream>
#include <thread>
#include <chrono>


void new_thread (int* p)
{
    std::cout << __FUNCTION__ << "(" << *p << ")\n";

    std::chrono::milliseconds ms(1000);
    std::this_thread::sleep_for (ms);

    *p = 19;
}

void start_new_thread()
{
    int i = 10;
    std::cout << __FUNCTION__ << ", before i = " << i << std::endl;

    std::thread t(new_thread, &i);
    t.detach();

    std::cout << __FUNCTION__ << ", after i = " << i << std::endl;
}


int main()
{
    start_new_thread ();

    std::chrono::milliseconds ms (2000);
    std::this_thread::sleep_for (ms);

    return 0;
}

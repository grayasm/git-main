/* This tutorial is copied from:
   http://thispointer.com/c11-multithreading-part-3-carefully-pass-arguments-to-threads
   http://thispointer.com/c11-tutorial

   Similarly as in the previous example (invalid stack address), be careful
   while passing pointer to memory located on heap to thread. Because it might
   be possible that some thread deletes that memory before new thread tries to
   access it. In such scenario accessing an invalid pointer may cause unexpected
   behaviour.
*/

#include <iostream>
#include <thread>
#include <chrono>

void new_thread (int* p)
{
    std::cout << __FUNCTION__ << ", *p = " << *p << std::endl;

    std::chrono::milliseconds ms(1000);
    std::this_thread::sleep_for (ms);

    *p = 19;
}

void start_new_thread()
{
    int* p = new int();
    *p = 10;
    std::cout << __FUNCTION__ << " *p = " << *p << std::endl;

    std::thread t (new_thread, p);
    t.detach();
    delete p;
    p = NULL;
}

int main()
{
    start_new_thread ();

    std::chrono::milliseconds ms (2000);
    std::this_thread::sleep_for (ms);

    return 0;
}

/* This tutorial is copied from:
   http://www.cplusplus.com/reference/thread/thread/join/

   Other c++-11 topics on the site are at:
   http://thispointer.com/c11-tutorial/

   In C++ 11 we can create additional threads by creating objects of std::thread
   class. Each of std::thread object can be associated with a thread.

   A new std::thread will start just after the creation and will execute the
   passed callback in parallel to the thread that started it.
   Any thread can wait for another to exit by calling join() function on that
   thread's object.
*/

#include <iostream>  // std::cout
#include <thread>    // std::thread, std::this_thread::sleep_for
#include <chrono>    // std::chrono::seconds


void pause_thread(int n)
{
    std::this_thread::sleep_for (std::chrono::seconds(n));
    std::cout << __FUNCTION__ << ": pause of " << n << " seconds ended\n";
}

int main()
{
    std::cout << "Spawning 3 threads ...\n";

    std::thread t1 (pause_thread, 1);
    std::thread t2 (pause_thread, 2);
    std::thread t3 (pause_thread, 3);

    std::cout << "Done spawning threads. Now waiting for them to join:\n";

    t1.join();
    t2.join();
    t3.join();

    std::cout << "All threads joined!\n";

    return 0;
}

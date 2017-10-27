/* This tutorial is copied from:
   http://thispointer.com/c11-multithreading-part-2-joining-and-detaching-threads
   http://thispointer.com/c11-tutorial

   Detaching threads is also called daemon / background threads.
   To detach a thread we need to call detach() function on std::thread object.
   After a call to this function, the thread object becomes non-joinable and
   can be destroyed safely.
*/

#include <iostream>  // std::cout
#include <thread>    // std::thread, std::this_thread::sleep_for
#include <chrono>    // std::chrono::seconds

void pause_thread(int n)
{
    std::this_thread::sleep_for (std::chrono::seconds(n));
    std::cout << "pause of " << n << " seconds ended\n";
}


int main()
{
    std::cout << "Spawning and detaching 3 threads...\n";

    std::thread (pause_thread, 1).detach();
    std::thread (pause_thread, 2).detach();
    std::thread (pause_thread, 3).detach();

    std::cout << "(the main thread will now pause for 5 seconds)\n";

    // give the detached threads time to finish (but not guaranteed!)
    pause_thread (5);

    return 0;
}

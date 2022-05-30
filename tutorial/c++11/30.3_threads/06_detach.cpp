/* Header     : <thread>
   Signature  :           thread() noexcept;
                template<class Fn, class... Args>
                explicit  thread(Fn&& fn, Args&&... args);
                          thread(const thread&) = delete;
                          thread(thread&& x) noexcept;

   Description:
       - thread represents a single thread of execution
       - begins execution immediately upon construction, starting at the
         top-level function provided as a constructor argument
       - the return value is ignored, and if it terminates by throwing exception
         std::terminate is called
       - the top-level function may communicate the return valu or an exception
         to the caller via std::promise (or other ways - shared variables)
       - thread looses its state after join(), detach(), default ctor(), moved
       - no 2 thread object may represent the same thread

   See also : http://en.cppreference.com/w/cpp/thread/thread
   -----------------------------------------------------------------------------

   This tutorial is copied from:
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

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

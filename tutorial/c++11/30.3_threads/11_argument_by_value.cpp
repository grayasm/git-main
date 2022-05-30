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

   To pass arguments to thread's associated callable object or function just
   pass additional arguments to the std::thread constructor.

   By default all arguments are copied into the internal storage of the new
   thread.
*/

#include <iostream>
#include <string>
#include <thread>

void thread_callback (std::string name, int age, float weight, double height)
{
    std::cout << __FUNCTION__ << "(" << name << ", " << age << ", " << weight
              << ", " << height << ")\n";
}

int main()
{
    std::string name("Bob");
    int age = 32;
    float weight = 120;
    float height = 188;

    std::thread threadObj (thread_callback, name, age, weight, height);
    threadObj.join();

    std::cout << "Exit main thread\n";

    return 0;
}

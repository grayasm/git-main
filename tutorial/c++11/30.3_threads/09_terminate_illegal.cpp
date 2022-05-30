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

   Never forget to call either join() or detach() on a std::thread object with
   associated executing thread.

   If neither join() or detach() is called with a std::thread object that has
   associated an executing thread then during that object's destructor it will
   terminate the program. Inside the destructor it will check if the thread
   is still joinable then terminate the program.
*/

#include <iostream>
#include <thread>
#include <algorithm>

class Worker
{
public:
    void operator()()
    {
        std::cout << __FUNCTION__ << std::endl;
    }
};

int main()
{
    std::thread threadObj ((Worker()));

    // Program will terminate as we have not called either join() or detach()
    // with the std::thread object. Hence std::thread's object destructor will
    // terminate the program.

    return 0;
}

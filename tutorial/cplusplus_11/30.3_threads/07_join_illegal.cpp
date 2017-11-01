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

   After calling detach(), the std::thread object is no longer associated
   with the actual thread of execution. Be careful with calling detach() and
   join() on thread handles.

   Never call join() on std::thread object with no associated executing thread.
*/

#include <iostream>
#include <thread>


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
    std::thread thobj  ((Worker()));
    thobj.join();
    thobj.join();  // it will cause the program to terminate!

    return 0;
}

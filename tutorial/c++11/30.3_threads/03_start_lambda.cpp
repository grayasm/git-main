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

   This tutorial is copied from: http://thispointer.com/c11-tutorial
   http://thispointer.com/c-11-multithreading-part-1-three-different-ways-to-create-threads

   Creating a thread using Lambda functions
*/

#include <iostream>
#include <thread>

int main()
{
    int x = 9;

    std::thread thobj (
        []{
            for (int i = 0; i < 10; ++i)
                std::cout << __FUNCTION__ << std::endl;
        });

    for (int i = 0; i < 10; ++i)
        std::cout << __FUNCTION__ << std::endl;

    thobj.join();

    std::cout << "Exit main thread\n";

    return 0;
}

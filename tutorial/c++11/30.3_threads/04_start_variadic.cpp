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

   Pass the pointer to member function as callback function and pass pointer
   to object as second argument.
*/

#include <iostream>
#include <thread>


class Dummy
{
public:
    Dummy(){ }
    Dummy(const Dummy& obj){ }
    void sample_fcn(int x)
    {
        std::cout << __FUNCTION__ << ", x = " << x << std::endl;
    }
};


int main()
{
    Dummy dummy;
    int x = 10;

    std::thread t(&Dummy::sample_fcn, &dummy, x);
    t.join();

    return 0;
}

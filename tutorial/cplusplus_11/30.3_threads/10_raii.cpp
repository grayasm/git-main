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

   Similar to the previous example, we should never forget to call join() or
   detach() in case of exceptions. To prevent this we should use RAII principle
   (resource acquisition is initialization)
*/

#include <iostream>
#include <thread>

class ThreadRAII
{
public:
    ThreadRAII(std::thread& th) : m_thread (th) { }
    ~ThreadRAII()
    {
        // Check if thread is joinable then detach() the thread
        if (m_thread.joinable())
        {
            m_thread.detach();
        }
    }
private:
    std::thread& m_thread;
};

void thread_function()
{
    for (int i = 0; i < 10; ++i)
        std::cout << __FUNCTION__ << std::endl;
}


int main()
{
    std::thread threadObj (thread_function);

    // If we comment this line the program will crash
    ThreadRAII wrapperObj (threadObj);

    return 0;
}

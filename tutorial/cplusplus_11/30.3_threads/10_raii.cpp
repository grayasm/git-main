/* This tutorial is copied from:
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

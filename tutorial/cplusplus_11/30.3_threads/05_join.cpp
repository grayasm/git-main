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

   Once a thread is started then another thread can wait for this new thread
   to finish. This another thread need to call join() function on the
   std::thread object.
*/

#include <iostream>
#include <thread>
#include <algorithm>

class Worker
{
public:
    void operator()()
    {
        std::cout << __FUNCTION__ << " thread id: "
                  << std::this_thread::get_id() << std::endl;
    }
};

int main()
{
    std::vector<std::thread> threadList;

    for (int i = 0; i < 10; ++i)
        threadList.push_back (std::thread( Worker() ));

    // Now wait for all the worker threads to finish i.e.
    // call join() function on each of the std::thread object

    std::cout << "wait for all the worker thread to finish\n";

    std::for_each (threadList.begin(),
                   threadList.end(),
                   std::mem_fn( &std::thread::join ));

    std::cout << "Exit from main thread\n";

    return 0;
}

/*
operator() thread id: operator()operator() thread id:  thread id: operator()operator() thread id:  thread id: operator() thread id: 139944810313472139944818706176139944827098880139944835491584139944852276992139944843884288
operator() thread id:
operator() thread id: 139944785135360

operator() thread id: 139944776742656wait for all the worker thread to finish
139944793528064


operator() thread id: 139944801920768


Exit from main thread
*/

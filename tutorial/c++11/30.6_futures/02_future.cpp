/* This sample is inspiered from:
   http://thispointer.com/c11-multithreading-part-8-stdfuture-stdpromise-and-returning-values-from-thread/


   - std::promise.set_value(): must be called ONLY 1 time. (more-> exception)
   - std::future.get()       : must be called ONLY 1 time. (more-> exception)

   - std::future.get()       : blocks the thread until the promise sets a value
   - std::promise.set_value(): sets the std::future value and release the
                               other thread (if blocked)

   To use std::future in more than one thread, see std::shared_future.
 */

#include <iostream>
#include <thread>
#include <future>
#include <chrono>

void thread_function(std::future<int>* fuobj)
{
    int x = fuobj->get();
    std::cout << __FUNCTION__ << ", future value = " << x << std::endl;
}


int main()
{
    std::promise<int> pro;
    std::future<int> fu = pro.get_future();

    std::thread th(thread_function, &fu);

    for (int i = 0; i < 4; ++i)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << __FUNCTION__ << ", sleeping for " << i + 1 << " sec\n";
    }

    pro.set_value(10);

    th.join();

    return 0;
}
/*
main, sleeping for 1 sec
main, sleeping for 2 sec
main, sleeping for 3 sec
main, sleeping for 4 sec
thread_function, future value = 10
*/

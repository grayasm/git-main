/* This sample is copied from:
   http://thispointer.com/c11-multithreading-part-8-stdfuture-stdpromise-and-returning-values-from-thread/
   http://thispointer.com/c11-tutorial/

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

void initializer(std::promise<int>* prom)
{
    std::cout << __FUNCTION__ << std::endl;
    for (int i = 0; i < 5; ++i)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "sleeping for " << i+1 << " sec" << std::endl;
    }
    prom->set_value(35);
}

int main()
{
    std::promise<int> prom;
    std::future<int> fu = prom.get_future();
    std::thread th(initializer, &prom);
    std::cout << "future value = " << fu.get() << std::endl;
    th.join();
    return 0;
}
/*
initializer
sleeping for 1 sec
sleeping for 2 sec
sleeping for 3 sec
sleeping for 4 sec
sleeping for 5 sec
future value = 35
*/

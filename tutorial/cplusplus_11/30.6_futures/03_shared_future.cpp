/* This sample is inspired from:
   http://thispointer.com/c11-multithreading-part-8-stdfuture-stdpromise-and-returning-values-from-thread

   - std::promise.set_value(): must be called ONLY 1 time. (more-> exception)
   - std::future.get()       : must be called ONLY 1 time. (more-> exception)
   - std::shared_future.get(): can be called MORE then 1 time, e.g. more threads
                               reading the same std::promise value.


   - std::future.get()       : blocks the thread until the promise sets a value
   - std::shared_future.get(): blocks the thread until the promise sets a value.

   - std::promise.set_value(): sets the std::future, std::shared_future value
                               and releases the other threads (if blocked)
*/

#include <iostream>
#include <vector>
#include <thread>
#include <future>


void thread_function(int id, std::shared_future<int>* fu)
{
    int x = fu->get();
    std::cout << __FUNCTION__ << ", id=" << id << " shared_future value="
              << x << std::endl;
}


int main()
{
    std::promise<int> prom;
    std::shared_future<int> fu(prom.get_future());

    std::vector<std::thread> threads;
    for (int i = 0; i < 5; ++i)
        threads.push_back(std::thread(thread_function, i, &fu));

    for (int i = 0; i < 5; ++i)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << __FUNCTION__ << ", sleeping for " << i+1 << " sec\n";
    }

    prom.set_value(35);

    for (int i = 0; i < 5; ++i)
        threads[i].join();

    return 0;
}

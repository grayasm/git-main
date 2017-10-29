/*
  std::shared_future's get() function can be called from multiple threads,
  in comparison with std::future's get() that may be called only one time.
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

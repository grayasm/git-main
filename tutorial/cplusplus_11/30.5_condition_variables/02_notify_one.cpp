/* This sample is copied from:
   http://thispointer.com/c11-multithreading-part-7-condition-variables-explained
   http://thispointer.com/c11-tutorial


*/

#include <iostream>
#include <functional>
#include <thread>
#include <mutex>
#include <condition_variable>


class Application
{
public:
    Application()
    {
        m_bDataLoaded = false;
    }

    void LoadData()
    {
        std::lock_guard<std::mutex> guard(m_mutex);
        std::cout << "Loading data" << std::endl;
        m_bDataLoaded = true;
        // notify
        m_condVar.notify_one();
    }

    void MainTask()
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        std::cout << "Wait for data" << std::endl;
        // wait
        m_condVar.wait(lock, std::bind(&Application::IsDataLoaded, this));
        // work
        std::cout << "Process data" << std::endl;
    }

    bool IsDataLoaded()
    {
        return m_bDataLoaded;
    }
private:
    std::mutex              m_mutex;
    std::condition_variable m_condVar;
    bool                    m_bDataLoaded;
};


int main()
{
    Application app;
    std::thread thread_1 (&Application::MainTask, &app);
    std::thread thread_2 (&Application::LoadData, &app);

    thread_1.join();
    thread_2.join();

    return 0;
}

/* This sample is improvised based on notify_one() sample from:
   http://thispointer.com/c11-multithreading-part-7-condition-variables-explained
   http://thispointer.com/c11-tutorial

   Thread 1                         |  Thread 2,3,4,5...
   Load data.                       |  Needs data to complete.
   =============================================================================
                                    |  unique_lock(mutex)
                                    |
   (attempt to lock mutex ...)      |  (preparation ...)
                                    |
                                    |  condition_variable.wait(unique_lock)
   (mutex is released)              |
                                    |
   mutex.lock()                     |
                                    |
   (load data)                      |
                                    |
   condition_variable.notify_all()  |
                                    |  (process data ...)
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
        std::this_thread::sleep_for(std::chrono::milliseconds(2500));
        std::lock_guard<std::mutex> guard(m_mutex);
        std::cout << "Loading data" << std::endl;
        m_bDataLoaded = true;
        // notify
        m_condVar.notify_all();
    }

    void MainTask()
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        std::cout << "MainTask: Wait for data" << std::endl;
        // wait
        m_condVar.wait(lock, std::bind(&Application::IsDataLoaded, this));
        // work
        std::cout << "MainTask: Process data" << std::endl;
    }

    void SecondTask()
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        std::cout << "SecondTask: Wait for data" << std::endl;
        // wait
        m_condVar.wait(lock, std::bind(&Application::IsDataLoaded, this));
        // work
        std::cout << "SecondTask: Process data" << std::endl;
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
    std::thread thread_2 (&Application::SecondTask, &app);
    std::thread thread_3 (&Application::LoadData, &app);

    thread_1.join();
    thread_2.join();
    thread_3.join();

    return 0;
}

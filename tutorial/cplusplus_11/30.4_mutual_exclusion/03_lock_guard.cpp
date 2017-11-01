/* Header     : <mutex>
   Signature  : constexpr mutex() noexcept;
                          mutex(const mutex&) = delete;
   Description:
     - mutex is a lockable object that is designed to signal when critical
       sections of code need exclusive access, preventing other threads with
       the same protection from executing concurrently and access the same
       memory locations
     - it provides exclusive ownership

   See also:
     recursive_mutex      : http://www.cplusplus.com/reference/mutex/recursive_mutex
     timed_mutex          : http://www.cplusplus.com/reference/mutex/timed_mutex
     recursive_timed_mutex: http://www.cplusplus.com/reference/mutex/recursive_timed_mutex

   -----------------------------------------------------------------------------

   This sample is copied from:
   http://thispointer.com/c11-multithreading-part-5-using-mutex-to-fix-race-conditions
   http://thispointer.com/c11-tutorial

   std::lock_guard is a class template which implements the RAII for mutex.
   It wraps the mutex inside it's object and locks the attached mutex in its
   constructor. When it's destructor is called it releases the mutex.
*/

#include <iostream>
#include <vector>
#include <thread>
#include <mutex>



class Wallet
{
public:
    Wallet() : m_money(0) { }
    int GetMoney() { return m_money; }
    void AddMoney(int money)
    {
        std::lock_guard<std::mutex> lockGuard(m_mutex);
        // In constructor it locks the mutex

        for (int i = 0; i < money; ++i)
        {
            m_money++;
        }

        // In destructor it unlocks the mutex
    }

private:
    int m_money;
    std::mutex m_mutex;
};


int test_multithreaded_wallet()
{
    Wallet walletObj;
    std::vector<std::thread> threads;
    for (int i = 0; i < 5; ++i)
        threads.push_back (std::thread(&Wallet::AddMoney, &walletObj, 1000));

    for (int i = 0; i < threads.size(); ++i)
        threads.at(i).join();

    return walletObj.GetMoney();
}


int main()
{
    int val = 0;
    for (int k = 0; k < 1000; ++k)
    {
        if ((val = test_multithreaded_wallet()) != 5000)
        {
            std::cout << "Error at count = " << k << ", money in Wallet"
                      << val << std::endl;
        }
    }

    return 0;
}

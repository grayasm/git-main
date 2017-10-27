/* This sample is copied from:
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

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
   http://thispointer.com/c11-multithreading-part-4-data-sharing-and-race-conditions
   http://thispointer.com/c11-tutorial/

   In multithreading environment data sharing between threads is very easy.
   But this easy sharing of data can cause problems in applications. One such
   problem is Race Condition.
*/

#include <iostream>
#include <vector>
#include <thread>


class Wallet
{
public:
    Wallet() : m_money(0) { }
    int GetMoney() { return m_money; }
    void AddMoney(int money)
    {
        for (int i = 0; i < money; ++i)
            m_money++;
    }
private:
    int m_money;
};


int test_multithreaded_wallet()
{
    Wallet walletObj;
    std::vector<std::thread> threads;
    for (int i = 0; i < 5; ++i)
        threads.push_back(std::thread(&Wallet::AddMoney, &walletObj, 1000));

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
            std::cout << "Error at count = " << k << " money in Wallet = "
                      << val << std::endl;
        }
    }

    return 0;
}
/*
You need to run the program multiple times, consecutively and you will get
at some point these errors:

Error at count = 3 money in Wallet = 4000
Error at count = 187 money in Wallet = 4000
Error at count = 446 money in Wallet = 4000
Error at count = 460 money in Wallet = 4000
Error at count = 473 money in Wallet = 4000
Error at count = 559 money in Wallet = 4000
Error at count = 560 money in Wallet = 4000
Error at count = 573 money in Wallet = 4000
Error at count = 574 money in Wallet = 4000
Error at count = 649 money in Wallet = 4000
*/

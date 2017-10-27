/* This tutorial is copied from:
   http://thispointer.com/c11-multithreading-part-2-joining-and-detaching-threads
   http://thispointer.com/c11-tutorial

   Never forget to call either join() or detach() on a std::thread object with
   associated executing thread.

   If neither join() or detach() is called with a std::thread object that has
   associated an executing thread then during that object's destructor it will
   terminate the program. Inside the destructor it will check if the thread
   is still joinable then terminate the program.
*/

#include <iostream>
#include <thread>
#include <algorithm>

class Worker
{
public:
    void operator()()
    {
        std::cout << __FUNCTION__ << std::endl;
    }
};

int main()
{
    std::thread threadObj ((Worker()));

    // Program will terminate as we have not called either join() or detach()
    // with the std::thread object. Hence std::thread's object destructor will
    // terminate the program.

    return 0;
}

/* This tutorial is copied from: http://thispointer.com/c11-tutorial
   http://thispointer.com/c-11-multithreading-part-1-three-different-ways-to-create-threads/

   Creating a thread using Function Objects
*/

#include <iostream>
#include <thread>

class DisplayThread
{
public:
    void operator()()
    {
        for (int i = 0; i < 10; ++i)
            std::cout << __FUNCTION__ << std::endl;
    }
};

int main()
{
    std::thread thobj ( (DisplayThread()) );

    for (int i = 0; i < 10; ++i)
        std::cout << __FUNCTION__ << std::endl;

    std::cout << "Waiting for the thread to complete\n";

    thobj.join();

    std::cout << "Exiting from main thread\n";

    return 0;
}

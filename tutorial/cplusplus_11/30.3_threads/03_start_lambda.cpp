/* This tutorial is copied from: http://thispointer.com/c11-tutorial
   http://thispointer.com/c-11-multithreading-part-1-three-different-ways-to-create-threads

   Creating a thread using Lambda functions
*/

#include <iostream>
#include <thread>

int main()
{
    int x = 9;

    std::thread thobj (
        []{
            for (int i = 0; i < 10; ++i)
                std::cout << __FUNCTION__ << std::endl;
        });

    for (int i = 0; i < 10; ++i)
        std::cout << __FUNCTION__ << std::endl;

    thobj.join();

    std::cout << "Exit main thread\n";

    return 0;
}

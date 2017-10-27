/* This tutorial is copied from:
   http://thispointer.com/c11-multithreading-part-2-joining-and-detaching-threads
   http://thispointer.com/c11-tutorial

   After calling detach(), the std::thread object is no longer associated
   with the actual thread of execution. Be careful with calling detach() and
   join() on thread handles.

   Never call detach() on std::thread object with no associated executing thread
*/

#include <iostream>
#include <thread>


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
    std::thread thobj  ((Worker()));
    thobj.detach();
    thobj.detach();  // it will cause the program to terminate!

    return 0;
}

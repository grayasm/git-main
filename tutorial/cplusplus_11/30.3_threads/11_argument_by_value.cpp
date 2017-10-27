/* This tutorial is copied from:
   http://thispointer.com/c11-multithreading-part-3-carefully-pass-arguments-to-threads
   http://thispointer.com/c11-tutorial

   To pass arguments to thread's associated callable object or function just
   pass additional arguments to the std::thread constructor.

   By default all arguments are copied into the internal storage of the new
   thread.
*/

#include <iostream>
#include <string>
#include <thread>

void thread_callback (std::string name, int age, float weight, double height)
{
    std::cout << __FUNCTION__ << "(" << name << ", " << age << ", " << weight
              << ", " << height << ")\n";
}

int main()
{
    std::string name("Bob");
    int age = 32;
    float weight = 120;
    float height = 188;

    std::thread threadObj (thread_callback, name, age, weight, height);
    threadObj.join();

    std::cout << "Exit main thread\n";

    return 0;
}

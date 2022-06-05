/*
  2.12 Keywords  [lex.key]

  thread_local is a reserved keyword.

  3.7.2 Thread storage duration  [basic.stc.thread]

  All variables declared with the thread_local keyword have thread storage duration.
  The variable shall be initialized before its first use and if constructed
  shall be destroyed on thread exit.

  https://en.cppreference.com/w/cpp/language/storage_duration

  compile with:
  g++ -pthread -std=c++11 -o main 14_thread_local.cpp
 */

#include <iostream>
#include <thread>
#include <mutex>


thread_local unsigned int count = 1;
std::mutex mtx;

void increase(){

    ++count;  // modifying outside a lock is okay; this is tread-local variable.

    std::lock_guard<std::mutex> lock(mtx);

    std::cout << "count (thread)=" << count << "\n";
}

int main(){

    std::thread t1(increase);
    std::thread t2(increase);

    {
        std::lock_guard<std::mutex> lock(mtx);
        std::cout << "count (main)=" << count << "\n";
    }

    t1.join();
    t2.join();
}

#include <iostream>
#include <chrono>
#include <thread>


void print_time_point(std::chrono::system_clock::time_point time_point)
{
  std::time_t time_stamp = std::chrono::system_clock::to_time_t(time_point);

  std::cout << std::ctime(&time_stamp) << std::endl;
}

void thread_func()
{
  std::cout << "Current Time :: ";

  print_time_point (std::chrono::system_clock::now());

  std::chrono::system_clock::time_point time_point =
    std::chrono::system_clock::now() + std::chrono::seconds(10);

  std::cout << "Going to sleep until :: ";
  print_time_point (time_point);

  std::this_thread::sleep_until (time_point);

  std::cout << "Current time :: ";
  print_time_point (std::chrono::system_clock::now());
}


int main()
{
  std::thread th (&thread_func);

  th.join();

  return 0;
}

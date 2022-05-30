#include <iostream>
#include <chrono>
#include <thread>

void thread_func()
{
  int i = 0;
  while (i < 10)
    {
      std::cout << std::this_thread::get_id() << " :: " << i++ << std::endl;

      std::this_thread::sleep_for (std::chrono::milliseconds(200));
    }
}


int main()
{
  std::thread th (&thread_func);

  th.join();

  return 0;
}

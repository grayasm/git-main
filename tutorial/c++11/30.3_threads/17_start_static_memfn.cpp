#include <iostream>
#include <thread>

class Task
{
public:
    static void test(std::string command)
    {
        for (int i = 0; i < 5; ++i)
        {
            std::cout << command << " :: " << i << std::endl;
        }
    }
};


int main()
{
    std::thread th(&Task::test, "Task");

    th.join();

    return 0;
}

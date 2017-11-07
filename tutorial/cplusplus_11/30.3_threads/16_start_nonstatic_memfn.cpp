#include <iostream>
#include <thread>

class Task
{
public:
    void execute(std::string command)
    {
        for(int i = 0; i < 5; ++i)
        {
            std::cout << command << " :: " << i << std::endl;
        }
    }
};


int main()
{
    Task* taskptr = new Task();

    std::thread th(&Task::execute, taskptr, "Sample task");

    th.join();

    delete taskptr;

    return 0;
}

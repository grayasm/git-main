/* Header     : <future>
   Signature  : template<class> class packaged_task;
                template<class R, class... Args> class packaged_task<R(Args...)>;

   Description: the class std::packaged_task wraps any callable target
                e.g. function, lambda expression, bind expression, or another
                function object, so that it can be invoked asynchronously.
                Its return value or exception thrown is stored in a shared
                state which can be accessed through std::future object.

   -----------------------------------------------------------------------------
   This sample is inspired from:
   http://thispointer.com/c11-multithreading-part-10-packaged_task-example-and-tutorial
*/

#include <iostream>
#include <string>
#include <thread>
#include <future>


struct ReadDB
{
    std::string operator()(std::string token)
    {
        std::string data = "Data from " + token;
        return data;
    }
};

int main()
{
    std::packaged_task<std::string(std::string)> task(std::move(ReadDB()));

    std::future<std::string> result = task.get_future();

    std::thread th(std::move(task), "Arg");

    th.join();

    std::string data = result.get();

    std::cout << data << std::endl;

    return 0;
}

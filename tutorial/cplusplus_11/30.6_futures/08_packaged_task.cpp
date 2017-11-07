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

std::string read_from_db(std::string token)
{
    std::string data = "Data fetched from DB by Filter :: " + token;
    return data;
}

int main()
{
    std::packaged_task<std::string(std::string)> task(read_from_db);

    std::future<std::string> result = task.get_future();

    /* Normally we would let the task be executed by a thread, but
       for this example I call directly the
       void operator()(Args... args);
       member

       std::thread th(std::move(task), "Arg");
       th.join();
    */

    task("Arg");

    std::string data = result.get();
    std::cout << data << std::endl;

    return 0;
}

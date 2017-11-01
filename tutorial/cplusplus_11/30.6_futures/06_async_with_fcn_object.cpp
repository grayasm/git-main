/* Header   : <future>
   Signature: (1) template<calss Fn, class... Args>
                      future<typename result_of<Fn(Args...)>::type>
                          async (Fn&& fn, Args&&... args);

              (2) template<class Fn, class... Args>
                      future<typename result_of<Fn(Args...)>::type>
                          async (launch policy, Fn&& fn, Args&&... args);

   Description:   runs a function with an arbitrary number of arguments, in
                  the same thread or in a separate thread (see policy),
                  and returns a std::future.

                  Now std::future class/invention makes perfect sense because
                  you launch couple of asynchronous functions and wait (get
                  blocked) on returned std::future.get() call.


   This sample is copied from:
   http://thispointer.com/c11-multithreading-part-9-stdasync-tutorial-example

   Calling std::async with function object as callback.
 */

#include <iostream>
#include <string>
#include <thread>
#include <future>
#include <chrono>

class ReadDB
{
public:
	std::string operator()(std::string recvdData)
	{
		std::this_thread::sleep_for (std::chrono::seconds(4));
		return "DB_" + recvdData;
	}
};

std::string read_from_file(std::string recvdData)
{
	std::this_thread::sleep_for (std::chrono::seconds(4));
	return "File_" + recvdData;
}

int main()
{
	std::chrono::system_clock::time_point start = std::chrono::system_clock::now();

	// execute in separate thread, asynchronous
	std::future<std::string> dbResult
		= std::async(std::launch::async, ReadDB(), "Data");

	// run in this thread
	std::string fileData = read_from_file("Data");

	// lock until std::async returns
	std::string dbData = dbResult.get();

	std::chrono::system_clock::time_point end = std::chrono::system_clock::now();

	int diff = std::chrono::duration_cast<std::chrono::seconds>(end-start).count();

	std::cout << "Total time taken = " << diff << " seconds\n";
	std::cout << "Data = " << dbData + " :: " + fileData << std::endl;

	return 0;
}
/*
Total time taken = 4 seconds
Data = DB_Data :: File_Data
*/

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
                  you launch couple of function asynchronous and wait (get
                  blocked) on returned std::future.get() call.


   This sample is copied from:
   http://thispointer.com/c11-multithreading-part-9-stdasync-tutorial-example/
 */
int main()
{
	return 0;
}

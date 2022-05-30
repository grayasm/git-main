/* Header     : <memory>
   Signature  : (1) template<class T, class D = default_delete<T>>
                    class unique_ptr;
                (2) template<class T, class D> class unique_ptr<T[], D>
   Description:
       -holds a * raw pointer and releases it when goes out of scope
       -is not copyable
       -releases the internal * raw pointer on release()
       -deletes the internal * raw pointer on reset() and becomes empty


   http://thispointer.com/c11-tutorial/
   http://thispointer.com/c11-unique_ptr-tutorial-and-examples/

   Calling release() on unique_ptr object will release the ownership of
   associated * raw pointer from the object, and will return the * raw pointer.
*/

#include <iostream>
#include <memory>

using namespace std;

struct Task
{
    Task(int id) : m_id(id) { cout << __FUNCTION__ << std::endl; }
    ~Task() { cout << __FUNCTION__ << std::endl; }
    int m_id;
};


int main()
{
    std::unique_ptr<Task> ptr (new Task(52));

    if (ptr != nullptr)
        cout << "pts is not empty" << std::endl;

    Task* ptask = ptr.release();  // release the * pointer

    if (ptr == nullptr)
        cout << "ptr is empty" << std::endl;

    return 0;
}

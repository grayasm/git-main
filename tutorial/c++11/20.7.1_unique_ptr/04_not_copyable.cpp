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

   As unique_ptr<> is not copyable, only moveable therefore it cannot be created
   through copy constructor or assignament operator.
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

#if 0
    std::unique_ptr<Task> ptr2 = ptr;  // compile error

    ptr = ptr2;  // compile error
#endif

    return 0;
}

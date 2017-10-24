/* http://thispointer.com/c11-tutorial/
   http://thispointer.com/c11-unique_ptr-tutorial-and-examples/

   Calling reset() on a unique_ptr<> object will delete the associated * raw
   pointer and make unique_ptr<> object empty.
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
    std::unique_ptr<Task> ptr (new Task(23));

    ptr.reset(); // empty

    if (ptr == nullptr)
        cout << "ptr == nullptr" << std::endl;

    return 0;
}

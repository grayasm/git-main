/* http://thispointer.com/c11-tutorial/
   http://thispointer.com/shared_ptr-and-custom-deletor/

   There might be other cases when we don't need to delete any memory
   we just need to release memory or resources to a pool etc.
*/

#include <iostream>
#include <memory>

using namespace std;

struct Sample
{
    Sample()
    {
        cout << __FUNCTION__ << '\n';
    }
    ~Sample()
    {
        cout << __FUNCTION__ << '\n';
    }
};


// Memory Pool Dummy Kind of Implementation
template<typename T>
class MemoryPool
{
public:
    T* AquireMemory()
    {
        cout << __FUNCTION__ << '\n';
        return (new T());
    }
    void ReleaseMemory(T* ptr)
    {
        cout << __FUNCTION__ << '\n';
        delete ptr;
    }
};

int main()
{
    std::shared_ptr<MemoryPool<Sample> > p1 =
        std::make_shared<MemoryPool<Sample> >();
    std::shared_ptr<Sample> p2(p1->AquireMemory(),
                               std::bind(&MemoryPool<Sample>::ReleaseMemory,
                                         p1,
                                         std::placeholders::_1));
    return 0;
}
/*
AquireMemory
Sample
ReleaseMemory
~Sample
*/

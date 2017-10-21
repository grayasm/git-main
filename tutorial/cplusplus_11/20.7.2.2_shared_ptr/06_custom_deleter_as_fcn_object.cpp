/* http://thispointer.com/shared_ptr-and-custom-deletor/
   Custom deleter as function object
*/

#include <iostream>
#include <memory>

using namespace std;

struct Sample
{
    Sample()
    {
        cout << "CONSTRUCTOR\n";
    }
    ~Sample()
    {
        cout << "DESTRUCTOR\n";
    }
};

class Deleter
{
public:
    void operator()(Sample* x)
    {
        cout << "DELETER FUNCTION CALLED\n";
        delete[] x;
    }
};


int main()
{
    std::shared_ptr<Sample> p3(new Sample[12], Deleter());
    return 0;
}

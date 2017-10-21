/* http://thispointer.com/shared_ptr-and-custom-deletor/
   Custom deleter as function pointer

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

// function that calls the delete[] on received pointer
void deleter(Sample* x)
{
    cout << "DELETER FUNCTION CALLED\n";
    delete[] x;
}

int main()
{
    // creating a shared_ptr with a custom deleter
    std::shared_ptr<Sample> p3(new Sample[12], deleter);
    return 0;
}

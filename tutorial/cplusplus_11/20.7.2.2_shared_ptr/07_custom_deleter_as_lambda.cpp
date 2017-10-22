/* http://thispointer.com/c11-tutorial/
   http://thispointer.com/shared_ptr-and-custom-deletor/
   
   Custom deleter as lambda function
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

int main()
{
    std::shared_ptr<Sample> p4(new Sample[12],
                               [](Sample* x)
                               {
                                   cout << "DELETER LAMBDA CALLED\n";
                                   delete[] x;
                               });
    return 0; 
}

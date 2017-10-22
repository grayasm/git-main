/* http://thispointer.com/c11-tutorial/
   http://thispointer.com/create-shared_ptr-objects-carefully/

   The dangling pointer
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

int main()
{
    {
        Sample* pSample = new Sample();

        std::shared_ptr<Sample> p1(pSample);

        {
            std::shared_ptr<Sample> p2(pSample);
        }
        // Here p2 goes out of scope and it deletes the raw pointer pSample.
    }
    // Here p1 will crash

    cout << "return 0;\n";

    return 0;
}

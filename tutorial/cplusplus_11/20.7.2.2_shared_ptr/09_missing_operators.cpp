/* http://thispointer.com/c11-tutorial/
   http://thispointer.com/how-shared_ptr-object-is-different-from-a-raw-pointer/

   Let's compare shared_ptr and raw pointer based on following aspects.
*/

#include <iostream>
#include <memory>

using namespace std;

struct Sample
{
    void dummy()
    {
        cout << __FUNCTION__ << '\n';
    }
};


int main()
{
    std::shared_ptr<Sample> p1 = std::make_shared<Sample>();

    (*p1).dummy(); // Will work
    p1->dummy();    // Will work

    /* --- this will not compile ---
       p1[0]->dummy();
       p1++;
       p1--;
    */

    std::shared_ptr<Sample> p2(p1);
    if (p1 == p2)   // Will work
        cout << "p1 and p2 are equal\n";

    return 0;
}

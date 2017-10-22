/* http://thispointer.com/c11-tutorial/
   http://thispointer.com/learning-shared_ptr-part-1-usage-details/
   
   shared_ptr is a pseudo pointer
*/


#include <iostream>
#include  <memory> // We need to include this for shared_ptr

int main()
{
    // Creating a shared_ptr through make_shared
    std::shared_ptr<int> p1 = std::make_shared<int>();
    *p1 = 78;
    std::cout << "p1 = " << *p1 << std::endl;

    // Shows the reference count
    std::cout << "p1 Reference count = " << p1.use_count() << std::endl;

    // Second shared_ptr object will also point to same pointer internally
    // It will make the reference count to 2.
    std::shared_ptr<int> p2(p1);

    // Shows the reference count
    std::cout << "p2 Reference count = " << p2.use_count() << std::endl;
    std::cout << "p1 Reference count = " << p1.use_count() << std::endl;

    // Comparing smart pointers
    if (p1 == p2)
    {
        std::cout << "p1 and p2 are pointing to same pointer\n";
    }

    std::cout<<"Reset p1 "<<std::endl;

    p1.reset();

    // Reset the shared_ptr, in this case it will not point to any Pointer internally
    // hence its reference count will become 0.

    std::cout << "p1 Reference Count = " << p1.use_count() << std::endl;

    // Reset the shared_ptr, in this case it will point to a new Pointer internally
    // hence its reference count will become 1.

    p1.reset(new int(11));

    std::cout << "p1  Reference Count = " << p1.use_count() << std::endl;

    // Assigning nullptr will de-attach the associated pointer and make it to point null
    p1 = nullptr;

    std::cout << "p1  Reference Count = " << p1.use_count() << std::endl;

    if (!p1)
    {
        std::cout << "p1 is NULL" << std::endl;
    }
    return 0;
}

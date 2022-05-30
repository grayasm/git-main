/* Header     : <cstddef> for std::nullptr_t
   Signature  : nullptr
                std::nullptr_t

   Description: N3337, #2.14.7 Point literals [lex.nullptr], pag 29
                The pointer literal is the keyword nullptr. It is a prvalue
                of type std::nullptr_t which is a distinct type that is neither
                a pointer type nor a pointer to member type; rather, a prvalue
                of this type is a null pointer constant and can be converted
                to a null pointer value or null member pointer value.
 */


#include <iostream>
#include <cstddef>
using namespace std;


void doSomething(int* p);
void doSomething(std::nullptr_t p);

int main()
{
    // a pointer can hold (1) an address or (2) a null value.
    int *p = 0;

    // it can be used inside a conditional test
    if (p)
        cout << "p is pointing to an int value.\n";
    else
     cout << "p is a null pointer.\n";

    // C preprocessor defines the NULL macro, that is a #define to value 0.
    p = NULL;

    // When used as a literal argument, it can cause problems as compiler can't
    // tell if we mean a null pointer or the integer 0:

    // doSomething (0);     error: call of overloaded ‘doSomething(int)’ is ambiguous
    doSomething(p);

    // C++11 introduces nullptr to avoid to much confusion
    doSomething (nullptr);


    return 0;
}


void doSomething(int* p)
{
    if (p)
        cout << "You passed in " << *p << '\n';
    else
        cout << "You passed in a null pointer\n";
}

void doSomething(std::nullptr_t p)
{
    cout << "You called the overloaded method for nullptr.\n";
}

/*
p is a null pointer.
You passed in a null pointer
You called the overloaded method for nullptr.
*/

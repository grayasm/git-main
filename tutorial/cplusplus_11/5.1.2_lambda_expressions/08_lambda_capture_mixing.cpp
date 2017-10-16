/* http://thispointer.com/c11-lambda-how-to-capture-local-variables-inside-lambda/
 *
 * Mixing capturing by value and reference.
 * We can also mix the capturing mode of lambda expression by passing some
 * local variables by value and some by reference.
 *
 * auto func = [=, &counter] ( ) mutable { };
 */

#include <iostream>
#include <string>

using namespace std;

int main()
{
    string message = "Hello";
    int counter = 10;

    auto func = [=, &counter] ( ) mutable {
        /* Capturing all local variables by value except counter,
           which is capture by reference here.
        */

        cout << "message = " << message << '\n';
        cout << "counter = " << counter << '\n';

        message = "Temp";
        counter = 20;

        cout << "message = " << message << '\n';
        cout << "counter = " << counter << '\n';
    };

    func();

    cout << "message = " << message << '\n';
    cout << "counter = " << counter << '\n';

    return 0;
}

/* http://thispointer.com/c11-lambda-how-to-capture-local-variables-inside-lambda/
 *
 * Capture all local variables from outer scope by reference.
 *
 * auto func = [&] () { };
 */

#include <iostream>
#include <string>

using namespace std;

int main()
{
    string message = "Hello";
    int counter = 10;

    auto pred = [&] ( ) {
        /* all variables are captured by reference */
        cout << "message = " << message << '\n';
        cout << "counter = " << counter << '\n';

        message = "Temp";
        counter = 20;

        cout << "message = " << message << '\n';
        cout << "counter = " << counter << '\n';
    };

    pred();

    cout << "message = " << message << '\n';
    cout << "counter = " << counter << '\n';
    return 0;
}

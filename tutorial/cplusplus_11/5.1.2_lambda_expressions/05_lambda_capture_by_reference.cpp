/* http://thispointer.com/c11-lambda-how-to-capture-local-variables-inside-lambda/
 *
 * Capturing local variables by reference inside lambda expression.
 * To capture the local variables by reference, specify their name in capture
 * list with prefix &
 *
 * auto func = [&message, &counter] () { };
 */

#include <iostream>
#include <string>

using namespace std;

int main()
{
    std::string message = "Hello";
    int counter = 10;

    /* Capturing local variables by reference */
    auto func = [&message, &counter] () mutable {
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
} // main

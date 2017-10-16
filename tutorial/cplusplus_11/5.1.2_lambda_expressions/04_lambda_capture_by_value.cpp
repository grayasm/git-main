/*
 * http://thispointer.com/c11-lambda-how-to-capture-local-variables-inside-lambda/
 *
 * How to capture local variables by value from outer scope in lambda expr.
 * The variables specified in capture list will be copied inside lambda
 * by value. Inside lambda they can be accessed but can not be changed,
 * because they are const. To modify them we need to add mutable keyword.
 *
 * auto func = [msg, counter] () mutable { };
 *
 */

#include <iostream>
#include <string>

using namespace std;

int main()
{
    std::string message = "Hello";
    int counter = 10;

    /* Capturing local variables by value */
    auto func = [message, counter] () mutable {
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

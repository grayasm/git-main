/* http://thispointer.com/c11-lambda-how-to-capture-local-variables-inside-lambda/
 *
 * Capture all local variables from outer scope by value.
 *
 * auto func = [=] () { };
 */

#include <iostream>

using namespace std;

int main()
{
	string message("Hello");
	int counter = 10;

	auto func = [=] ( ) {
		/* outer variables are captured by value
		   outer variables are const (without mutable keyword)
		*/
		cout << "message = " << message << '\n';
		cout << "counter = " << counter << '\n';
	};

	func();
	return 0;
}

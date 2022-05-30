/* Header     : none (core functionality)
   Signature  : auto 'variable initializer'
                auto function -> return type
   Description:

   ISO: The auto type-specifier may appear with a function declarator with
        a trailing-return-type (8.3.5) in any context where such a declarator
        is valid.

   See: http://www.learncpp.com/cpp-tutorial/4-8-the-auto-keyword/
*/

#include <iostream>
#include <string>

/*  In this case, auto does not perform type inference, but it is just part
    of the syntax to use a trailing return type.
    Why would you want to use this?
    One nice thing is that it makes all of your function names line up:
*/
auto add(int x, int y) -> int;
auto divide(double x, double y) -> double;
auto printSomething() -> void;
auto calculateThis(int x, double d) -> std::string;


int main()
{
	int sum = add (5, 6);
	std::cout << "sum = " << sum << std::endl;

	return 0;
}

auto add(int x, int y) -> int
{
	return x + y;
}

// sample is complete, the other 3 functions are omitted.

/* Header     : core feature
   Signature  : [ captures ] (params) specifiers exception attr -> ret { body }
                [ captures ] (params) -> ret { body }
                [ captures ] (params) { body }
                [ captures ] { body }

   Description:
       captures  : [] nothing
                   [=] all by copy and *this by reference (if any)
                   [&] all by reference and *this by reference (if any)
                   [this] *this by reference
                   [a, &b] a by copy, b by reference
       specifiers: mutable   - can modify all captures by copy and call their
                               non-const member functions
                   constexpr - default, obey constexpr functions
       exception : throw
                   noexcept
       attr      : [[attr]] [[attr1, attr2(args)]] [[namespace::attr(args)]] alignas_specifier
                   ex: [[noreturn]] void f() { throw "error" ; }
                   [[carries_dependency]]
                   [[deprecated]], [[deprecated("reason")]]
                   [[fallthrough]]
                   [[nodiscard]]
                   [[maybe_unused]], etc...
       ret       : default void or explicit, e.g. auto&, int&, char*, SomeClass
       body      : function body


 http://thispointer.com/c11-lambda-how-to-capture-local-variables-inside-lambda/
 *
 * Be-aware of capturing local variables by reference in lambda
 *
 * If in lambda we are capturing local variables by reference, then we need to
 * make sure that when lambda function is accessed or called, all those captured
 * by reference are still in scope.
 *
 * If lambda will try to access or modify a local variable captured by refrence
 * which is not in scope anymore i.e. which has been destroyed due to stack
 * unwinding, then crash can happen.
 */

#include <iostream>
#include <string>
#include <functional>

using namespace std;

std::function<void()> get_callback()
{
	int counter = 10;

	/* capturing local variables by reference */
	auto func = [&counter] ( ) mutable {
		cout << "counter = " << counter << '\n';

		/* this change will affect the outer counter */
		counter = 20;

		cout << "counter = " << counter << '\n';
	};

	return func;
}


int main()
{
	std::function <void()> func = get_callback();

	/* It seems this call will corrupt the stack because the internal
	   counter was removed from stack at this point.
	   I don't fully understand how this works actually ?!?!
	*/
	func();

	return 0;
}

/*
   Header     : core feature
   Signature  : [ captures ] (params) specifiers exception attr -> ret { body };
                [ captures ] (params) -> ret { body };
                [ captures ] (params) { body };
                [ captures ] { body };

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

   -----------------------------------------------------------------------------
   Below there are few examples of assigning a lambda to a function pointer
   and using it.
*/

#include <iostream>
#include <vector>

typedef void (*fn) (int& x);
void pass_a_lambda(fn callback);


int main()
{
	std::vector<int> vec;
	for (int i = 0; i < 5; ++i)
	{
		vec.push_back(i);
		std::cout << i << " ";
	}

	// (1) Assign lambda function to a function pointer.
	//     This works for simple capture [], [=] but not for [&]
	void (*f1)(int& i) = [](int& i) { i *= 2; };

	for (int i = 0; i < vec.size(); ++i)
		f1(vec[i]);

	std::cout << std::endl;
	for (int i = 0; i < vec.size(); ++i)
		std::cout << vec[i] << " ";

	std::cout << std::endl;

	// (2) If we can assign a lambda to a function pointer, then it can be
	//     passed around as a parameter also. Here, an exercise:
	fn f2 = [] (int& i) { i *= 3; };
	pass_a_lambda ( f2 );

	return 0;
}


void pass_a_lambda(fn callback)
{
	for (int i = 0; i < 5; ++i)
	{
		int j = i;
		callback(j);
		std::cout << "i = " << i << " callback(i) = " << j << std::endl;
	}
}

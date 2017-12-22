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
*/


#include <iostream>


class A
{
public:
	A(int v) : val(v) { }
	~A() { }

	int pow2()
	{
		// int (*f)() = [this] () -> int { return val * val; };
		// error: cannot convert A::pow2()::__lambda0 to int (*)()

		// Here I have to use auto to get the correct lambda function type.
		auto f = [this] () -> int { return val * val; };
		return f();
	}
private:
	int val;
};

int main()
{
	A a(2);
	std::cout << "a = 2, a.pow2() = " << a.pow2() << std::endl;

	return 0;
}

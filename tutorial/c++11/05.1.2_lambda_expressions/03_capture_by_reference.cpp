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
#include <functional>
void capture_this();


int main()
{
	int x = 0;

	// ok, not called, x is modified also outside lambda scope
	[&] () { x = 2; };

	// ok, lambda returning value 10, not called anywhere
	[&] () { return 10; };

	// ok, x modified also outside labmda scope
	[&] () { x = 2; };

	// access *this inside lambda
	capture_this();

	// assign lambda to a function pointer
	// error: cannot convert main()::__lambda3 to void (*)()
	// void (*f)() = [&] () { x = 2; };


	// assign lambda to an std::function
	std::function<void(void)> g = [&] () { x = 2; };
	g();

	// assign lambda to auto type
	auto h = [&] () { x = 2; };
	h();
}


class A
{
public:
	A(int v) : val(v) {}
	void print()
	{
		// ok, captured this by reference, not called
		[&] () { this->val = 2; };
	}
private:
	int val;
};

void capture_this()
{
	A a(10);
	a.print();
}

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

	// ok, capture all by copy, x is read-only
	[=] () { return x * 2; };

	// error: x assignament of read-only variable x, not called, uncomment to get the error
	[=] () { /* x = 2; */ };

	// ok, x is 2 only inside lambda
	[=] () mutable { x = 2; };

	// access *this inside lambda
	capture_this();

	// assign lambda to a function pointer
	void (*f)() = [=] () { };
	f();

	// assign lambda to an std::function
	std::function<void(void)> g = [=] () { };
	g();

	// assign lambda to auto type
	auto h = [=] () { };
	h();
}


class A
{
public:
	A(int v) : val(v) {}
	void print()
	{
		// ok, not called, val modified also outside lambda scope
		[=] () { this->val = 2; };
	}
	int get() { return val; }
private:
	int val;
};

void capture_this()
{
	A a(10);
	a.print();
}

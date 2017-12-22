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
	// ok, no capture, arg x is 2 only inside lambda scope
	[] (int x) { x = 2; };

	// ok, no capture, passed argument is modified outside lambda scope
	[] (int& x) { x = 2; };

	// ok, no capture, pointer value is modified outside lambda scope
	[] (int* x) { *x = 2; };

	// access *this inside lambda
	capture_this();

	int x = 0;
	int y = 0;
	int z = 0;
	// assign lambda to a function pointer
	void (*f)(int, int&, int*) = [] (int a, int& b, int* c) { a = b + *c; };
	f(x, y, &z);

	// assign lambda to an std::function
	std::function<void(void)> g = [] () { };
	g();

	// assign lambda to auto type
	auto h = [] () { };
	h();
}


class A
{
public:
	A(int v) : val(v) {}
	void print()
	{
		// ok, capture this, passed argument is modified outside lambda scope
		[this] (int& x) { x = this->val; };
	}
private:
	int val;
};

void capture_this()
{
	A a(10);
	a.print();
}

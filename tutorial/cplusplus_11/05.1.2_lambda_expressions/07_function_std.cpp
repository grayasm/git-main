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

   see: http://www.cplusplus.com/reference/functional/function
   Header   : <functional>
   Signature: template<class T> function;   // undefined
              template <class Ret, class... Args> class function(Ret(Args...)>;
   Example  :
              std::function<bool(int*,int&)> f =
              [] (int* p, int& r) -> bool { return *p == r; };
              f(&a,b);
*/


#include <iostream>
#include <functional>


int main()
{
	int tab1[5] = {  0, 1, 2, 3, 4 };
	int tab2[5] = {  0, 1, 2, 3, 4 };
	int tab3[5] = {  0, 0, 0, 0, 0 };

	/*
	  Only for clarity I extract here the lambda signature.
	  Capture tab1 and tab2 by value, read-only, not changable.
	  Pass in one argument, pointer to int.
	*/
	auto f = [tab1, tab2] (int* tab)
	{
		for (int i = 0; i < 5; ++i)
			tab[i] = tab1[i] + tab2[i];
	};

	/*
	void (*g)(int*) = f;
	g(tab3);
	error: cannot convert 'main()::__lambda0' to void (*)(int*)
	*/

	/* Besides auto, std::function can declare the correct type of this lambda
	 */

	std::function<void(int*)> g = f;
	g(tab3);

	for (int i = 0; i < 5 ; ++i)
		std::cout << "tab[" << i << "]=" << tab3[i] << std::endl;

	return 0;
}

/*
tab[0]=0
tab[1]=2
tab[2]=4
tab[3]=6
tab[4]=8
*/

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

   -----------------------------------------------------------------------------
   This sample is copied from:
   http://thispointer.com/designing-callbacks-in-c-part-3-c11-lambda-functions

   We can traverse an int array using STL algorithm std::for_each passing a
   lambda function, without the overhead of a separate function.

   Rise of Lambda functions

   A lambda function is a kind of anonymous function which doesn't have any
   name but you can pass arguments and return results from it. All its content
   will work as in-line code.
 */


#include <iostream>
#include <algorithm>


int main()
{
    int arr[] = {1, 2, 3, 4, 5};

    size_t arrsz = sizeof(arr) / sizeof(int);
    std::for_each(arr, arr + arrsz, [](int x){ std::cout << x << " ";});

    std::cout << std::endl;

    return 0;
}

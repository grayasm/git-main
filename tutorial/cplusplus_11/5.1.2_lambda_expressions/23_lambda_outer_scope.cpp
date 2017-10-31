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
   How to pass outer scope elements inside Lambda functions.
   [=]  means all outer scope elements are read-only (rvalues).
   [&]  means all outer scope elements are passed by reference.

   Checkout this example that clearly shows how to use outer scope elements
   inside lambda functions.
 */

#include <iostream>
#include <algorithm>


int main()
{
    int arr[] = { 1, 2, 3, 4, 5 };

    int mul = 5;

    size_t arrsz = sizeof(arr) / sizeof(int);

    std::for_each(arr, arr + arrsz, [&](int x){
            std::cout << x << " ";
            // Can modify the mul inside this lambda function because
            // all outer scope elements are visible and changeable by reference.
            mul = 3;
        });

    std::cout << std::endl;

    std::for_each(arr, arr + arrsz, [=](int &x){
            x = x * mul;
            std::cout << x << " ";
            // Cannot modify the mul inside this lambda function because
            // all oter scope elements are read-only (rvalue) types.
            // mul = 9; error: assignament of read-only variable 'mul'
        });
    std::cout << std::endl;


    std::for_each(arr, arr + arrsz, [](int x){
            // No access to mul inside this lambda function because
            // all outer scope elements are not visible here.
            // std::cout << mul << " ";
        });
    std::cout << std::endl;

    return 0;
}

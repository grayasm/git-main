/*
 * How to pass outer scope elements inside Lambda functions.
 *
 * [=]  means all outer scope elements are read-only (rvalues).
 * [&]  means all outer scope elements are passed by reference.
 *
 * Checkout this example that clearly shows how to use outer scope elements
 * inside lambda functions.
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

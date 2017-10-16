/*
 * Need of Lambda functions
 *
 * We traverse an int array using STL algorithm std::for_each.
 * We can achieve this avoiding the overhead of a separate function.
 *
 * Rise of Lambda functions
 *
 * A lambda function is a kind of anonymous function which doesn't have any
 * name but you can pass arguments and return results from it. All its content
 * will work as in-line code.
 *
 * [] is used to pass the outers scope elements
 * (int x) shows argument x is passed
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

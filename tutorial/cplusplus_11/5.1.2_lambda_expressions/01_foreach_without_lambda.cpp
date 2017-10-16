/*
 * Need of Lambda functions
 *
 * I have an array of int and I want to traverse on this array and print all
 * ints using STL algorithm std::for_each.
 * Let's do that using a function pointer.
 */


#include <iostream>
#include <algorithm>

void display(int a)
{
    std::cout << a << " ";
}

int main()
{
    int arr[] = {1, 2, 3, 4, 5};

    std::for_each(arr, arr + sizeof(arr) / sizeof(int), & display);

    std::cout << std::endl;

    return 0;
}

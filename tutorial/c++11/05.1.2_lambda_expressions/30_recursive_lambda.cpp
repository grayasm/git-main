/*  https://www.codeproject.com/Articles/570638/Ten-Cplusplus-Features-Every-Cplusplus-Developer#lambdas
 */

#include <stdio.h>
#include <functional>

main()
{
/*
  A bit trickier are recursive lambdas. Imagine a lambda that represents
  a Fibonacci function. If you attempt to write it using auto, you get
  a compilation error.
*/

#if 0
    /*
      error: use of 'fib' before deduction of 'auto'
      error: cannot capture '<expression error>' by reference
    */
    auto fib = [&fib](int n) { return n < 2 ? 1 : fib(n-1) + fib(n-2); };
    fib(3);
#endif

    /* The problem is auto means the type of the object is inferred from its
       initializer, yet the initializer contains a reference to it, therefore
       needs to know its type. This is a cyclic problem. The key is to break
       this dependency cycle and explicitly specify the function's type
       using std::function.
    */

    std::function<int(int)> fib =
	    [&fib](int n) { return (n < 2 ? 1 : fib(n-1) + fib(n-2)); };

    printf("fib(5)=%d\n", fib(5));
}
/*
fib(5)=8
*/

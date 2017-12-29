/*  https://msdn.microsoft.com/en-us/library/dn457344.aspx

    In C++11, the non-copyable idiom can be implemented in a way that is more
    straightforward.
*/

#include <stdio.h>

struct noncopyable
{
    noncopyable() =default;
    noncopyable(const noncopyable&) =delete;
    noncopyable& operator=(const noncopyable&) =delete;
};


main()
{
    noncopyable ncA;
    // noncopyable ncB = ncA  - error
}

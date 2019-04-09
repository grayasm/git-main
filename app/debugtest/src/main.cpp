

#include <stdio.h>
#include <list>
#include <limits>
#include "vector.hpp"
#include <vector>


class Cx
{
public:
    Cx() { val = 0; }
    Cx(int v) { val = new int(v); }
    Cx(const Cx& c) {
        val = 0;
        *this = c;
    }
    Cx& operator=(const Cx& c) {
        if (this != &c) {
            if (val) delete val;
            val = new int(*c.val);
        }
        return *this;
    }
    ~Cx() {
        if (val)
            delete val;
    }
    bool operator == (const Cx& c) {
        if (!val || !c.val) return false;
        return (*val == *c.val);
    }
    bool operator != (const Cx& c) {
        return !(*this == c);
    }
    int* get() const { return val; }
private:
    int* val;
};


int main()
{
    char s1[] = "this string is empty                ";
    char s2[] = "this string is dirty                ";

    memmove(s1, s2, strlen(s2));

    Cx c1[5] = { -1, -2, -3, -4, -5 };
    Cx c2[5] = { +1, +2, +3, +4, +5 };
    Cx* p1[5] = { c1, c1 + 1, c1 + 2, c1 + 3, c1 + 4 };

    stl::mem_move(c1, 5, c2, 5, stl::allocator<Cx>());

    return 0;
}
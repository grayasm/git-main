

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
    

    return 0;
}
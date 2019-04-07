

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
    Cx c3[5] = { -1, -2, -3, -4, -5 };

    // void assign_(iterator, iterator);
    stl::vector<Cx> v4_, v5_;
    v4_.assign(c3, c3 + 5);
    v5_.assign(v4_.begin(), v4_.end()); // iterator

    v5_.assign(v4_.begin(), v4_.end());
    stl::vector<Cx>::reverse_iterator v5_rib = v5_.rbegin(), v5_rie = v5_.rend();
    v5_.assign(v5_rib + 2, v5_rie); // reverse_iterator (self assignment)

    for (int i = 0; i < v5_.size(); ++i)
    {
        int* p5 = v5_[i].get();
        int* p4 = v4_[v4_.size() - i - 3].get();

        //CPPUNIT_ASSERT(v5_[i] == v4_[v4_.size() - i - 3]);
    }
    //CPPUNIT_ASSERT(v5_.size() == v4_.size() - 2);
    return 0;
}
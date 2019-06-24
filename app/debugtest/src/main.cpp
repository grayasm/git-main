#include <stdio.h>
#include <iostream>
#include <list>
#include <vector>
#include <limits>
#include <vector.hpp>
#include <basic_string.hpp>
#include "list.hpp"


class A
{
public:
    A()
    {
        m_i = new int; *m_i = -1;
        printf("A(): %d %x\n", *m_i, m_i);
    }
    ~A()
    {
        printf("~A(): %d %x\n", *m_i, m_i);
        delete m_i; m_i = 0;
    }
    A(int i)
    {
        m_i = new int; *m_i = i;
        printf("A(int i): %d %x\n", *m_i, m_i);
    }

    A(const A& tc)
    {
        printf("A(A&) -> =(A&)\n");
        m_i = new int;
        *this = tc;
    }
    A& operator=(const A& tc)
    {
        if (this != &tc)
        {
            *m_i = *(tc.m_i);
        }

        printf("operator=(A&): %d %x\n", *m_i, m_i);
        return *this;
    }
    A(A&& tm)
    {
        m_i = tm.m_i;
        tm.m_i = 0;

        printf("A(A&&): %d %x\n", *m_i, m_i);
    }
    A& operator=(A&& tm)
    {
        if (this != &tm)
        {
            int* t = m_i;
            m_i = tm.m_i;
            tm.m_i = t;
        }

        printf("operator=(A&&): %d %x\n", *m_i, m_i);
        return *this;
    }
    int* get() const { return m_i; }

private:
    int* m_i;
};


int main()
{
    //{
    //    stl::list<A> lst;
    //    for (int i = -10; i <= 0; ++i)
    //        lst.push_back(A(i));

    //    for (stl::list<A>::iterator beg = lst.begin(); beg != lst.end(); ++beg)
    //        printf("A(%d)=%d\n", *(beg->get()));
    //}

    std::list<int> ilist;
    // ilist.push_back(10);
    std::list<int>::iterator beg = ilist.begin();
    printf("int [0] = %d\n", *beg);
    
    return 0;
}

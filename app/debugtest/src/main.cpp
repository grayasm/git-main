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
    typedef stl::list<int> IList;
    IList il;
    

    il.insert(il.begin(), 10);
    il.insert(il.begin(), 5);

    IList::iterator it = il.begin();
    ++it;
    
    il.insert(it, 3);
    
    // size_t size = il.size();

    IList::iterator rit = il.begin();
    int i1 = *rit;
    int i2 = *(++rit);
    int i3 = *(++rit);
    
    return 0;
}

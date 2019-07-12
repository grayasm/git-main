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
    typedef stl::list<int> ilist;
    ilist il1, il2;
    for (int i = 1; i <= 10; ++i)
        il1.push_back(i);

    ilist::iterator it = il1.begin();
    stl::advance(it, 4);
    il1.splice(it, il1, it);


    //for (int i = 4; i <= 7; ++i)
    //    il1.push_back(-1 * i);

    //for (int i = 8; i <= 10; ++i)
    //    il1.push_back(i);


    //std::list<int>::iterator it4 = il1.begin();
    //std::advance(it4, 3);
    //std::list<int>::iterator it4(it2);
    //std::advance(it4, 2);

    //il1.splice(it2, il1, it4, il1.end());

    //std::list<int>::iterator 
        it = il1.begin();
    for (; it != il1.end(); ++it)
        printf("value: %d\n", *it);
        
    return 0;
}

#include <stdio.h>
#include <list>
#include <limits>
#include <vector.hpp>

class A
{
public:
    A()
    {
        printf("A()     \n");
        m_i = new int; *m_i = -1;
    }
    ~A()
    {
        printf("~A()    \n");
        delete m_i; m_i = 0;
    }
    A(int i)
    {
        printf("A(int i)\n");
        m_i = new int; *m_i = i;
    }

    A(const A& tc)
    {
        printf("A(const A& tc)  \n");
        m_i = new int;
        *this = tc;
    }
    A& operator=(const A& tc)
    {
        printf("A& operator=(const A& tc)\n");
        if (this != &tc)
        {
            *m_i = *(tc.m_i);
        }
        return *this;
    }
    A(A&& tm)
    {
        printf("A(const A&& tm) \n");
        m_i = tm.m_i;
        tm.m_i = 0;
    }
    A& operator=(A&& tm)
    {
        printf("A& operator=(const A&& tm)  \n");
        if (this != &tm)
        {
            int* t = m_i;
            m_i = tm.m_i;
            tm.m_i = t;
        }
        return *this;
    }

private:
    int* m_i;
};


int main()
{
    
    stl::vector<A> avec;
    for (int i = 0; i < 3; ++i)
        avec.push_back(A(i));

    avec.assign(1, avec.back());

    stl::vector<char> chvec;
    for (char c = 'a'; c < 'd'; ++c)
        chvec.push_back(c);

    chvec.assign(1, chvec.back());

    return 0;
}

#include <stdio.h>
#include <iostream>
#include <list>
#include <vector>
#include <limits>
#include <vector.hpp>
#include <basic_string.hpp>


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
    std::vector<int> foo(3, 100);   // three ints with a value of 100
    std::vector<int> bar(2, 200);   // two ints with a value of 200

    if (foo == bar) std::cout << "foo and bar are equal\n";
    if (foo != bar) std::cout << "foo and bar are not equal\n";
    if (foo< bar) std::cout << "foo is less than bar\n";
    if (foo> bar) std::cout << "foo is greater than bar\n";
    if (foo <= bar) std::cout << "foo is less than or equal to bar\n";
    if (foo >= bar) std::cout << "foo is greater than or equal to bar\n";

    return 0;
}

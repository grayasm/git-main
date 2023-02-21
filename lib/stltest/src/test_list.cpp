/*
Copyright (C) 2012 Mihai Vasilian
*/

#if 0
#include "test_list.hpp"

//CppUnit
#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>


#include <list>
#include "list.hpp"
#include "time_printer.hpp"


void test_list::setUp()
{
}

void test_list::tearDown()
{
}


template<typename T>
bool is_eq(const T& x, const T& y, const T& tol)
{
    return (x < y + tol && x > y - tol);
}

class Cx
{
public:
    Cx() { val = 0; }
    // explicit: error C2440: 'initializing' : cannot convert from 'int' to 'Cx'
    //           Cx c3[5] = { -1, -2, -3, -4, -5 };
    Cx(int v) { val = new int(v); }
    Cx(const Cx& c) {
        val = 0; //!!! always zero initialize; if constructed on the place of a
        //!!! defunct Cx instance then it will automatically inherit
        //!!! whatever garbage was there before
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


// Don't shoot for performance yet. Get everything correct first!
void test_list::ctor()
{
    typedef stl::list<int> list;

    // list(const Allocator& alloc= Allocator())
    list l01;
    CPPUNIT_ASSERT(l01.empty());

    // list(size_type n, const T& value = T(), const Allocator& alloc = Allocator())
    list l02(400, 100);
    CPPUNIT_ASSERT(l02.size() == 400);
    for (list::iterator it = l02.begin(); it != l02.end(); ++it)
        CPPUNIT_ASSERT(*it == 100);

    // list(InputIterator first, InputIterator last, const Allocator& alloc = Allocator())
    list l03;
    for (int i = 0; i < 400; ++i)
        l03.push_back(i);

    list l04(l03.begin(), l03.end());
    CPPUNIT_ASSERT(l04.size() == 400);
    size_t i04 = 0;
    for (list::iterator it = l04.begin(); it != l04.end(); ++it, ++i04)
        CPPUNIT_ASSERT(*it == i04);

    list l05(l03.rbegin(), l03.rend());
    CPPUNIT_ASSERT(l05.size() == 400);
    size_t i05 = 399;
    for (list::iterator it = l05.begin(); it != l05.end(); ++it, --i05)
        CPPUNIT_ASSERT(*it == i05);

    const list& cl03 = l03;
    list l06(cl03.begin(), cl03.end());
    size_t i06 = 0;
    for (list::iterator it = l06.begin(); it != l06.end(); ++it, ++i06)
        CPPUNIT_ASSERT(*it == i06);

    list l07(cl03.rbegin(), cl03.rend());
    size_t i07 = 399;
    for (list::iterator it = l07.begin(); it != l07.end(); ++it, --i07)
        CPPUNIT_ASSERT(*it == i07);

        

    // list(const container& x)
    

    
}

void test_list::assign_op()
{
    // container& operator=(const container& tc)

}

void test_list::assign()
{
    // assign(InputIterator first, InputIterator last)

    // assign(size_type count, const value_type& value)


}

void test_list::get_allocator()
{
    // allocator_type get_allocator() const

}

void test_list::begin()
{
    // iterator begin ()

    // const_iterator begin () const

}

void test_list::end()
{
    // iterator end ()

    // const_iterator end() const
}

void test_list::rbegin()
{
    // reverse_iterator rbegin()

    // const_reverse_iterator rbegin() const

}

void test_list::rend()
{
    // reverse_iterator rend()

    // const_reverse_iterator rend() const

}

void test_list::resize()
{
    // bool empty() const

    // size_type size() const

    // size_type max_size() const

    // void resize(size_type n, value_type value = value_type())

}

void test_list::front()
{
    // reference front()

    // const_reference front() const

}

void test_list::back()
{
    // reference back()

    // const_reference back() const

}

void test_list::push_front()
{
    // void push_front(const value_type& value)

}

void test_list::pop_front()
{
    // void pop_front()

}

void test_list::push_back()
{
    // void push_back(const value_type& value)

}

void test_list::pop_back()
{
    // void pop_back()

}

void test_list::insert()
{
    // iterator insert(iterator position, const value_type& value)

    // void insert(iterator position, size_type n, const value_type& value)

    // void insert(iterator position, InputIterator first, InputIterator last)

}

void test_list::erase()
{
    // iterator erase(iterator position)

    // iterator erase(iterator first, iterator last)

}

void test_list::swap()
{
    // void swap(container& x)

}

void test_list::clear()
{
    // void clear()

}

void test_list::splice()
{
    // void splice(iterator position, container& x)

    // void splice(iterator position, container& x, iterator it)

    // void splice(iterator position, container& x, iterator first, iterator last)

}

void test_list::remove()
{
    // void remove(const value_type& value)

    // void remove_if(Predicate pred)

}

void test_list::unique()
{
    // void unique()

    // void unique(BinaryPredicate binary_pred)
}

void test_list::merge()
{
    // void merge(container& x)

    // void merge(container& x, Compare comp)

}

void test_list::sort()
{
    // void sort()

    // void sort(Compare comp)

}

void test_list::reverse()
{
    // void reverse()

}

void test_list::perf1()
{
}
#endif
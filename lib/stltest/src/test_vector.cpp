/*
  Copyright (C) 2009 Mihai Vasilian

  This program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License as published by the
  Free Software Foundation; either version 2 of the License, or (at your
  option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU General Public License for more details.

  You should have received a copy of the GNU General Public License along
  with this program. If not, see http://www.gnu.org/licenses/.

  contact: grayasm@gmail.com
*/


#include "test_vector.hpp"

//CppUnit
#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>


#include <vector>
#include "vector.hpp"
#include "time_printer.hpp"


void test_vector::setUp()
{
}

void test_vector::tearDown()
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
void test_vector::ctor()
{
    // vector()
    stl::vector<char> v0;

    // vector(size_t, const T&);
    stl::vector<short> v1((size_t)5, (short)-1);
    for (int i = 0; i < 5; ++i)
    {
        if (v1[i] != -1)
            CPPUNIT_ASSERT(false);
    }
    CPPUNIT_ASSERT(v1.size() == 5);

    Cx c2(-101);
    stl::vector<Cx> v2((size_t)3, c2);
    for (size_t i = 0; i < v2.size(); ++i)
    {
        CPPUNIT_ASSERT(v2[i] == c2);
    }
    CPPUNIT_ASSERT(v2.size() == 3);


    // vector<InputIterator>(InputIterator first, InputIterator last);
    signed char sc1[5] = { 'a', 'b', 'c', 'd', 'e' };
    stl::vector<signed char> v3(sc1, sc1 + 5);
    for (int i = 0; i < 5; ++i)
    {
        if (v3[i] != sc1[i])
            CPPUNIT_ASSERT(false);
    }
    CPPUNIT_ASSERT(v3.size() == 5);

    Cx c4[5] = { -1, -2, -3, -4, -5 };
    stl::vector<Cx> v4(c4, c4 + 5);
    for (int i = 0; i < 5; ++i)
    {
        CPPUNIT_ASSERT(v4[i] == c4[i]);
    }
    CPPUNIT_ASSERT(v4.size() == 5);


    // vector(const vector&)
    stl::vector<float> v5;
    for (float f = 1.1f; f < 6; f += 1.1f)
        v5.push_back(f);
    stl::vector<float> v6(v5);
    for (size_t i = 0; i < v5.size(); ++i)
    {
        if (!is_eq(v5[i], v6[i], 1e-4f))
            CPPUNIT_ASSERT(false);
    }
}

void test_vector::assign_op()
{
    // vector& operator=(const vector&)
    stl::vector<long> v1, v2;
    v2 = v1;

    for (long i = -1; i > -6; --i)
        v1.push_back(i);
    v2 = v1;

    for (size_t i = 0; i < v1.size(); ++i)
    {
        if (v1[i] != v2[i])
            CPPUNIT_ASSERT(false);
    }
    CPPUNIT_ASSERT(v2.size() == v1.size());

    v2 = v2; //self
}

void test_vector::assign()
{
    // vector& assign(const vector&)
    stl::vector<int> v1;
    for (int i = 1; i < 6; ++i)
        v1.push_back(i);

    stl::vector<int> v2;
    v2.assign(v1);
    for (size_t i = 0; i < v1.size(); ++i)
    {
        if (v1[i] != v2[i])
            CPPUNIT_ASSERT(false);
    }

    v2.assign(v2); // self
    for (size_t i = 0; i < v1.size(); ++i)
    {
        if (v1[i] != v2[i])
            CPPUNIT_ASSERT(false);
    }

    // void assign(size_t, const T&);
    const int i2 = 100;
    v2.assign((size_t)3, i2);
    for (int i = 0; i < 3; ++i)
    {
        if (v2[i] != 100)
            CPPUNIT_ASSERT(false);
    }
    CPPUNIT_ASSERT(v2.size() == 3);

    v2.assign((size_t)4, v2.front()); // self
    for (int i = 0; i < 4; ++i)
    {
        if (v2[i] != 100)
            CPPUNIT_ASSERT(false);
    }
    CPPUNIT_ASSERT(v2.size() == 4);

    Cx c3[5] = { -1, -2, -3, -4, -5 };
    stl::vector<Cx> v3;
    for (int i = 0; i < 2; ++i)
    {
        v3.push_back(c3[i]);
    }
    const Cx& c3addr = *v3.begin();

    // capacity must be 2; will trigger relocation for 3 and invalidate c3addr
    v3.assign((size_t)3, c3addr);

    CPPUNIT_ASSERT(v3[0] == v3[1] && v3[1] == v3[2] && v3[0] == c3[0]);
    CPPUNIT_ASSERT(v3.size() == 3);

    // void assign_(iterator, iterator);
    stl::vector<Cx> v4, v5;
    v4.assign(c3, c3 + 5);
    v5.assign(v4.begin(), v4.end()); // iterator

    for (size_t i = 0; i < v4.size(); ++i)
        CPPUNIT_ASSERT(v5[i] == v4[i]);
    CPPUNIT_ASSERT(v5.size() == v4.size());

    const stl::vector<Cx>& cv4_ = v4;
    v5.assign(cv4_.begin(), cv4_.end()); // const_iterator

    for (size_t i = 0; i < v4.size(); ++i)
        CPPUNIT_ASSERT(v5[i] == v4[i]);
    CPPUNIT_ASSERT(v5.size() == v4.size());

    v5.assign(v4.rbegin(), v4.rend()); // reverse_iterator
    for (size_t i = 0; i < v4.size(); ++i)
        CPPUNIT_ASSERT(v5[i] == v4[v4.size() - i - 1]);
    CPPUNIT_ASSERT(v5.size() == v4.size());

    v5.assign(cv4_.rbegin(), cv4_.rend()); // const_reverse_iterator
    for (size_t i = 0; i < cv4_.size(); ++i)
        CPPUNIT_ASSERT(v5[i] == cv4_[cv4_.size() - i - 1]);
    CPPUNIT_ASSERT(v5.size() == cv4_.size());

    v5.assign(v4.begin(), v4.end());
    v5.assign(v5.begin() + 2, v5.end()); // iterator (self assignment)
    for (size_t i = 0; i < v5.size(); ++i)
        CPPUNIT_ASSERT(v5[i] == v4[i + 2]);
    CPPUNIT_ASSERT(v5.size() == v4.size() - 2);


    v5.assign(v4.begin(), v4.end());
    stl::vector<Cx>::const_iterator v5_cib = v5.begin(), v5_cie = v5.end();
    v5.assign(v5_cib, v5_cie - 2); // const_iterator (self assignment)

    for (size_t i = 0; i < v5.size(); ++i)
        CPPUNIT_ASSERT(v5[i] == v4[i]);
    CPPUNIT_ASSERT(v5.size() == v4.size() - 2);

    v5.assign(v4.begin(), v4.end());
    stl::vector<Cx>::reverse_iterator v5_rib = v5.rbegin(), v5_rie = v5.rend();
    v5.assign(v5_rib + 2, v5_rie); // reverse_iterator (self assignment)

    for (size_t i = 0; i < v5.size(); ++i)
        CPPUNIT_ASSERT(v5[i] == v4[v4.size() - i - 3]);
    CPPUNIT_ASSERT(v5.size() == v4.size() - 2);

    v5.assign(v4.begin(), v4.end());
    stl::vector<Cx>::const_reverse_iterator v5_crib = v5.rbegin(),
        v5_crie = v5.rend();
    v5.assign(v5_crib, v5_crie - 2); // const_reverse_iterator (self assignment)

    for (size_t i = 0; i < v5.size(); ++i)
        CPPUNIT_ASSERT(v5[i] == v4[v4.size() - i - 1]);
    CPPUNIT_ASSERT(v5.size() == v4.size() - 2);

    v5.assign(v4.begin(), v4.end());
    v5.assign(5, v5.front());

    for (size_t i = 0; i < v5.size(); ++i)
        CPPUNIT_ASSERT(v5[i] == v4.front());
    CPPUNIT_ASSERT(v5.size() == 5);

    //assign_(InputIterator n, InputIterator value, stl::input_iterator_tag)
    int i6[5] = { -1, -2, -3, -4, -5 };
    stl::vector<int> v6;
    v6.assign(i6, i6 + 5);
    v6.assign(5, v6.front());

    for (size_t i = 0; i < v6.size(); ++i)
        CPPUNIT_ASSERT(v6[i] == -1);

    // void assign_(value_type* first, value_type* last)
    Cx c7[5] = { -1, -2, -3, -4, -5 };
    stl::vector<Cx> v7;
    v7.assign(c7, c7 + 5);

    for (size_t i = 0; i < v7.size(); ++i)
        CPPUNIT_ASSERT(v7[i] == c7[i]);
    CPPUNIT_ASSERT(v7.size() == 5);

    v7.assign(&v7.front(), &v7.back()); // self assignment
    for (size_t i = 0; i < v7.size(); ++i)
        CPPUNIT_ASSERT(v7[i] == c7[i]);
    CPPUNIT_ASSERT(v7.size() == 4);

    // void assign_(const value_type* first, const value_type* last)
    Cx c8[5] = { -1, -2, -3, -4, -5 };
    stl::vector<Cx> v8;
    v8.assign((const Cx*)c8, (const Cx*)(c8 + 5));

    for (size_t i = 0; i < v8.size(); ++i)
        CPPUNIT_ASSERT(v8[i] == c8[i]);
    CPPUNIT_ASSERT(v8.size() == 5);

    const stl::vector<Cx>& cv8 = v8;
    v8.assign(&cv8.front(), &cv8.back()); // self assignment

    for (size_t i = 0; i < v8.size(); ++i)
        CPPUNIT_ASSERT(v8[i] == c8[i]);
    CPPUNIT_ASSERT(v8.size() == 4);

    // --- other situations worth testing ---
    // I had the impression that mem_move leaks memory.
    // I already tested it and it doesn't leak.
    Cx c9[5] = { -1, -2, -3, -4, -5 };
    stl::vector<Cx> v9;
    v9.assign(c9, c9 + 5);

    // const Cx& elem4 = v9[4];
    v9.assign(v9.begin() + 2, v9.end()); // move last 3 in front
    CPPUNIT_ASSERT(v9.size() == 3); // elem4 is released - OK

    int i10[5] = { -1, -2, -3, -4, -5 };
    stl::vector<int> v10;
    v10.assign(i10, i10 + 5);

    // int& elem4_1 = v10[4];
    v10.assign(v10.begin() + 2, v10.end()); // most last 3 in front
    CPPUNIT_ASSERT(v10.size() == 3);
}

void test_vector::begin()
{
    Cx cx1[5] = { -1, -2, -3, -4, -5 };
    stl::vector<Cx> v1;
    v1.assign(cx1, cx1 + 5);

    stl::vector<Cx>::iterator beg = v1.begin();
    stl::vector<Cx>::iterator beg2 = beg;
    stl::vector<Cx>::iterator beg3;
    beg3 = beg;
    const Cx& cx = *beg3;
    const int* pint = beg3->get();
    CPPUNIT_ASSERT(*pint == -1);

    stl::vector<Cx>::iterator& beg4 = ++beg3;   //operator++()
    CPPUNIT_ASSERT(*(beg4->get()) == -2);

    stl::vector<Cx>::iterator beg5 = beg4++;    //operator++(int)
    CPPUNIT_ASSERT(*(beg5->get()) == -2);
    CPPUNIT_ASSERT(*(beg4->get()) == -3);

    stl::vector<Cx>::iterator& beg6 = --beg4;   //operator--()
    CPPUNIT_ASSERT(*(beg6->get()) == -2);

    stl::vector<Cx>::iterator beg7 = beg6--;    //operator--(int)
    CPPUNIT_ASSERT(*(beg7->get()) == -2);
    CPPUNIT_ASSERT(*(beg6->get()) == -1);

    stl::vector<Cx>::iterator& beg8 = (beg6 += 2);  //operator+=(offset)
    CPPUNIT_ASSERT(*(beg8->get()) == -3);

    stl::vector<Cx>::iterator beg9 = (beg8 + 2);    //operator+()
    CPPUNIT_ASSERT(*(beg9->get()) == -5);
    
    stl::vector<Cx>::iterator beg10 = (beg9 -= 2);  //operator-=(offset)
    CPPUNIT_ASSERT(*(beg10->get()) == -3);

    stl::vector<Cx>::iterator beg11 = (beg10 - 2);  //operator-(offset);
    CPPUNIT_ASSERT(*(beg11->get()) == -1);

    size_t diff11 = beg10 - beg11;
    CPPUNIT_ASSERT(diff11 == 2);

    CPPUNIT_ASSERT(beg == beg2);
    CPPUNIT_ASSERT(beg11 != beg10);
    CPPUNIT_ASSERT(beg11 < beg10);
    CPPUNIT_ASSERT(beg10 > beg11);
    CPPUNIT_ASSERT(beg11 <= beg10);
    CPPUNIT_ASSERT(beg >= beg2);
    
    const Cx& cx11 = beg11[2];
    CPPUNIT_ASSERT(beg11[2] == *beg10);     // operator[](offset)
}

void test_vector::end()
{
    Cx cx1[5] = { -1, -2, -3, -4, -5 };
    stl::vector<Cx> v1;
    v1.assign(cx1, cx1 + 5);

    stl::vector<Cx>::iterator end = v1.end();
    stl::vector<Cx>::iterator end2 = end;
    stl::vector<Cx>::iterator end3;
    end3 = end - 5;
    const Cx& cx = *end3;
    const int* pint = end3->get();
    CPPUNIT_ASSERT(*pint == -1);

    stl::vector<Cx>::iterator& end4 = ++end3;   //operator++()
    CPPUNIT_ASSERT(*(end4->get()) == -2);

    stl::vector<Cx>::iterator end5 = end4++;    //operator++(int)
    CPPUNIT_ASSERT(*(end5->get()) == -2);
    CPPUNIT_ASSERT(*(end4->get()) == -3);

    stl::vector<Cx>::iterator& end6 = --end4;   //operator--()
    CPPUNIT_ASSERT(*(end6->get()) == -2);

    stl::vector<Cx>::iterator end7 = end6--;    //operator--(int)
    CPPUNIT_ASSERT(*(end7->get()) == -2);
    CPPUNIT_ASSERT(*(end6->get()) == -1);

    stl::vector<Cx>::iterator& end8 = (end6 += 2);  //operator+=(offset)
    CPPUNIT_ASSERT(*(end8->get()) == -3);

    stl::vector<Cx>::iterator end9 = (end8 + 2);    //operator+()
    CPPUNIT_ASSERT(*(end9->get()) == -5);

    stl::vector<Cx>::iterator end10 = (end9 -= 2);  //operator-=(offset)
    CPPUNIT_ASSERT(*(end10->get()) == -3);

    stl::vector<Cx>::iterator end11 = (end10 - 2);  //operator-(offset);
    CPPUNIT_ASSERT(*(end11->get()) == -1);

    size_t diff11 = end10 - end11;
    CPPUNIT_ASSERT(diff11 == 2);

    CPPUNIT_ASSERT(end == end2);
    CPPUNIT_ASSERT(end11 != end10);
    CPPUNIT_ASSERT(end11 < end10);
    CPPUNIT_ASSERT(end10 > end11);
    CPPUNIT_ASSERT(end11 <= end10);
    CPPUNIT_ASSERT(end >= end2);

    const Cx& cx11 = end11[2];
    CPPUNIT_ASSERT(end11[2] == *end10);     // operator[](offset)
}

void test_vector::rbegin()
{
    Cx cx1[5] = { -1, -2, -3, -4, -5 };
    stl::vector<Cx> v1;
    v1.assign(cx1, cx1 + 5);

    stl::vector<Cx>::reverse_iterator rbeg = v1.rbegin();
    stl::vector<Cx>::reverse_iterator rbeg2 = rbeg;
    stl::vector<Cx>::reverse_iterator rbeg3;
    rbeg3 = rbeg;
    const Cx& cx = *rbeg3;
    const int* pint = rbeg3->get();
    CPPUNIT_ASSERT(*pint == -5);

    stl::vector<Cx>::reverse_iterator& rbeg4 = ++rbeg3;   //operator++()
    CPPUNIT_ASSERT(*(rbeg4->get()) == -4);

    stl::vector<Cx>::reverse_iterator rbeg5 = rbeg4++;    //operator++(int)
    CPPUNIT_ASSERT(*(rbeg5->get()) == -4);
    CPPUNIT_ASSERT(*(rbeg4->get()) == -3);

    stl::vector<Cx>::reverse_iterator& rbeg6 = --rbeg4;   //operator--()
    CPPUNIT_ASSERT(*(rbeg6->get()) == -4);

    stl::vector<Cx>::reverse_iterator rbeg7 = rbeg6--;    //operator--(int)
    CPPUNIT_ASSERT(*(rbeg7->get()) == -4);
    CPPUNIT_ASSERT(*(rbeg6->get()) == -5);

    stl::vector<Cx>::reverse_iterator& rbeg8 = (rbeg6 += 2);  //operator+=(offset)
    CPPUNIT_ASSERT(*(rbeg8->get()) == -3);

    stl::vector<Cx>::reverse_iterator rbeg9 = (rbeg8 + 2);    //operator+()
    CPPUNIT_ASSERT(*(rbeg9->get()) == -1);

    stl::vector<Cx>::reverse_iterator rbeg10 = (rbeg9 -= 2);  //operator-=(offset)
    CPPUNIT_ASSERT(*(rbeg10->get()) == -3);

    stl::vector<Cx>::reverse_iterator rbeg11 = (rbeg10 - 2);  //operator-(offset);
    CPPUNIT_ASSERT(*(rbeg11->get()) == -5);

    size_t diff11 = rbeg10 - rbeg11;
    CPPUNIT_ASSERT(diff11 == 2);

    CPPUNIT_ASSERT(rbeg == rbeg2);
    CPPUNIT_ASSERT(rbeg11 != rbeg10);
    CPPUNIT_ASSERT(rbeg11 < rbeg10);
    CPPUNIT_ASSERT(rbeg10 > rbeg11);
    CPPUNIT_ASSERT(rbeg11 <= rbeg10);
    CPPUNIT_ASSERT(rbeg >= rbeg2);

    const Cx& cx11 = rbeg11[2];
    CPPUNIT_ASSERT(rbeg11[2] == *rbeg10);     // operator[](offset)
}

void test_vector::rend()
{
    Cx cx1[5] = { -1, -2, -3, -4, -5 };
    stl::vector<Cx> v1;
    v1.assign(cx1, cx1 + 5);

    stl::vector<Cx>::reverse_iterator rend = v1.rend();
    stl::vector<Cx>::reverse_iterator rend2 = rend;
    stl::vector<Cx>::reverse_iterator rend3;
    rend3 = rend - 5;
    const Cx& cx = *rend3;
    const int* pint = rend3->get();
    CPPUNIT_ASSERT(*pint == -5);

    stl::vector<Cx>::reverse_iterator& rend4 = ++rend3;   //operator++()
    CPPUNIT_ASSERT(*(rend4->get()) == -4);

    stl::vector<Cx>::reverse_iterator rend5 = rend4++;    //operator++(int)
    CPPUNIT_ASSERT(*(rend5->get()) == -4);
    CPPUNIT_ASSERT(*(rend4->get()) == -3);

    stl::vector<Cx>::reverse_iterator& rend6 = --rend4;   //operator--()
    CPPUNIT_ASSERT(*(rend6->get()) == -4);

    stl::vector<Cx>::reverse_iterator rend7 = rend6--;    //operator--(int)
    CPPUNIT_ASSERT(*(rend7->get()) == -4);
    CPPUNIT_ASSERT(*(rend6->get()) == -5);

    stl::vector<Cx>::reverse_iterator& rend8 = (rend6 += 2);  //operator+=(offset)
    CPPUNIT_ASSERT(*(rend8->get()) == -3);

    stl::vector<Cx>::reverse_iterator rend9 = (rend8 + 2);    //operator+()
    CPPUNIT_ASSERT(*(rend9->get()) == -1);

    stl::vector<Cx>::reverse_iterator rend10 = (rend9 -= 2);  //operator-=(offset)
    CPPUNIT_ASSERT(*(rend10->get()) == -3);

    stl::vector<Cx>::reverse_iterator rend11 = (rend10 - 2);  //operator-(offset);
    CPPUNIT_ASSERT(*(rend11->get()) == -5);

    size_t diff11 = rend10 - rend11;
    CPPUNIT_ASSERT(diff11 == 2);

    CPPUNIT_ASSERT(rend == rend2);
    CPPUNIT_ASSERT(rend11 != rend10);
    CPPUNIT_ASSERT(rend11 < rend10);
    CPPUNIT_ASSERT(rend10 > rend11);
    CPPUNIT_ASSERT(rend11 <= rend10);
    CPPUNIT_ASSERT(rend >= rend2);

    const Cx& cx11 = rend11[2];
    CPPUNIT_ASSERT(rend11[2] == *rend10);     // operator[](offset)
}

void test_vector::resize()
{
    // resize(size_type sz, value_type c = value_type())
    Cx c1[5] = { -1, -2, -3, -4, -5 };
    stl::vector<Cx> v1;
    v1.assign(c1, c1 + 5);

    v1.resize(3);  // resize to smaller size
    for (size_t i = 0; i < v1.size(); ++i)
        CPPUNIT_ASSERT(v1[i] == c1[i]);
    CPPUNIT_ASSERT(v1.size() == 3);

    v1.resize(2, c1[0]); // resize to smaller size
    for (size_t i = 0; i < v1.size(); ++i)
        CPPUNIT_ASSERT(v1[i] == c1[i]);
    CPPUNIT_ASSERT(v1.size() == 2);


    v1.assign(c1, c1 + 2);
    //v1.resize(4);  // seg.fault - due to uninitialized 2nd param
    v1.resize(5, c1[0]); // resize to bigger size (default 2nd param)

    for (int i = 0; i < 2; ++i)
        CPPUNIT_ASSERT(v1[i] == c1[i]);
    for (int i = 2; i < 5; ++i)
        CPPUNIT_ASSERT(v1[i] == c1[0]);
    CPPUNIT_ASSERT(v1.size() == 5);

    v1.assign(c1, c1 + 5);
    v1.resize(5, v1.front()); // self assignment
    for (size_t i = 0; i < v1.size(); ++i)
        CPPUNIT_ASSERT(v1[i] == c1[i]);
    CPPUNIT_ASSERT(v1.size() == 5);
}

void test_vector::capacity()
{
    stl::vector<int> v1;
    CPPUNIT_ASSERT(v1.capacity() == 0);

    int i2[5] = { -1, -2, -3, -4, -5 };
    stl::vector<int> v2(i2, i2 + 5);
    CPPUNIT_ASSERT(v2.capacity() == 5);

    stl::vector<int> v3;
    for (int i = 0; i < 5; ++i)
        v3.push_back(i);
    CPPUNIT_ASSERT(v3.capacity() == 8);
}


void test_vector::reserve()
{
    stl::vector<int> v1;
    v1.reserve(0);
    CPPUNIT_ASSERT(v1.capacity() == 0);

    v1.reserve(5);
    CPPUNIT_ASSERT(v1.capacity() == 5);

    v1.reserve(3);
    CPPUNIT_ASSERT(v1.capacity() == 5);    
}

void test_vector::at_and_op()
{
    Cx cx1[] = { -1, -2, -3, -4, -5 };
    stl::vector<Cx> v1;
    v1.assign(cx1, cx1 + 5);

    for (size_t i = 0; i < v1.size(); ++i)
    {
        CPPUNIT_ASSERT(v1.at(i) == cx1[i]);
        CPPUNIT_ASSERT(v1[i] == cx1[i]);
    }
}

void test_vector::front()
{
    Cx cx1[] = { -1, -2, -3, -4, -5 };
    stl::vector<Cx> v1;
    v1.assign(cx1, cx1 + 5);

    CPPUNIT_ASSERT(v1.front() == cx1[0]);
}

void test_vector::back()
{
    Cx cx1[] = { -1, -2, -3, -4, -5 };
    stl::vector<Cx> v1;
    v1.assign(cx1, cx1 + 5);

    CPPUNIT_ASSERT(v1.back() == cx1[4]);
}

void test_vector::push_back()
{
    Cx c1[5] = { -1, -2, -3, -4, -5 };
    stl::vector<Cx> v1;
    v1.assign(c1, c1 + 5);

    // void push_back(const T&)
    v1.resize(3);
    v1.push_back(c1[3]);
    v1.push_back(c1[4]);
    for (size_t i = 0; i < v1.size(); ++i)
        CPPUNIT_ASSERT(v1[i] == c1[i]);
    CPPUNIT_ASSERT(v1.size() == 5);

    stl::vector<Cx> v2;
    for (int i = 0; i < 5; ++i)
        v2.push_back(c1[i]);

    for (int i = 0; i < 5; ++i)
        CPPUNIT_ASSERT(v2[i] == c1[i]);
    CPPUNIT_ASSERT(v2.size() == 5);
    CPPUNIT_ASSERT(v2.capacity() == 8);

    stl::vector<Cx> v3;
    v3.push_back(Cx(-1));
    v3.push_back(Cx(-2));
    v3.push_back(v3.front()); // test how grow() invalidates v3.front()!!

    CPPUNIT_ASSERT(v3[0] == Cx(-1) && v3[1] == Cx(-2) && v3[2] == Cx(-1));
}

void test_vector::pop_back()
{
    Cx c1[5] = { -1, -2, -3, -4, -5 };
    stl::vector<Cx> v1;
    v1.assign(c1, c1 + 5);

    // void pop_back()
    for (int i = 0; i < 3; ++i)
        v1.pop_back();

    for (size_t i = 0; i < v1.size(); ++i)
        CPPUNIT_ASSERT(v1[i] == c1[i]);
    CPPUNIT_ASSERT(v1.size() == 2);
    CPPUNIT_ASSERT(v1.capacity() == 5);
}

void test_vector::insert()
{
    // iterator insert(iterator position, const T& x)
    Cx c1[5] = { -1, -2, -3, -4, -5 };
    stl::vector<Cx> v1;
    v1.insert(v1.end(), c1[0]);  // other

    CPPUNIT_ASSERT(v1.size() == 1);
    CPPUNIT_ASSERT(v1.capacity() == 1);
    CPPUNIT_ASSERT(v1[0] == c1[0]);

    v1.insert(v1.begin(), v1.front()); // from self
    CPPUNIT_ASSERT(v1.size() == 2);
    CPPUNIT_ASSERT(v1[0] == c1[0] && v1[1] == c1[0]);
    
    // void insert(iterator position, size_type n, const T& x)
    stl::vector<Cx> v2;
    v2.assign(c1, c1 + 2); // capacity=2
    v2.insert(v2.begin(), 1, v2.front()); // relocate and invalidate 3rd param

    CPPUNIT_ASSERT(v2[0] == c1[0] && v2[1] == c1[0] && v2[2] == c1[1]);
    CPPUNIT_ASSERT(v2.size() == 3);

    v2.insert(v2.begin(), 1, c1[4]);
    CPPUNIT_ASSERT(v2[0] == c1[4]);
    CPPUNIT_ASSERT(v2[1] == c1[0]); //...etc
    CPPUNIT_ASSERT(v2.size() == 4);


    // void insert_(iterator& position, iterator& first, iterator& last)
    Cx c3[5] = { -1, -2, -3, -4, -5 };
    stl::vector<Cx> v3, v4;
    v3.assign(c3, c3 + 5);
    v4.insert(v4.end(), v3.begin(), v3.end()); // from other
    for (size_t i = 0; i < v4.size(); ++i)
        CPPUNIT_ASSERT(v3[i] == v4[i] && v4[i] == c3[i]);
    CPPUNIT_ASSERT(v4.size() == 5);
    v4.insert(v4.begin(), v3.begin(), v3.end());
    for (size_t i = 5; i < v4.size(); ++i)
        CPPUNIT_ASSERT(v3[i-5] == v4[i] && v4[i] == c3[i-5]);
    CPPUNIT_ASSERT(v4.size() == 10);


    v3.insert(v3.begin(), v3.begin(), v3.end()); // from self
    for (size_t i = 0; i < v3.size(); ++i)
        CPPUNIT_ASSERT(v3[i] == c3[i % 5]);
    CPPUNIT_ASSERT(v3.size() == 10);


    // void insert_(iterator& position, const_iterator& first, const_iterator& last)
    Cx c5[5] = { -1, -2, -3, -4, -5 };
    stl::vector<Cx> v5, v6;
    v5.assign(c5, c5 + 5);
    const stl::vector<Cx>& cv5 = v5;
    const stl::vector<Cx>& cv6 = v6;
    v6.insert(v6.end(), cv5.begin() + 2, cv5.end()); // from other
    
    for (size_t i = 0; i < v6.size(); ++i)
        CPPUNIT_ASSERT(v6[i] == v5[i + 2] && v6[i] == c5[i + 2]);
    CPPUNIT_ASSERT(v6.size() == 3);
    v6.insert(v6.begin(), cv5.begin(), cv5.end());
    for (size_t i = 0; i < 5; ++i)
        CPPUNIT_ASSERT(v6[i] == v5[i] && v6[i] == c5[i]);
    CPPUNIT_ASSERT(v6.size() == 8);

    v6.assign(v5);
    v6.insert(v6.end(), cv6.begin(), cv6.end()); // from self
    v6.insert(v6.begin(), cv6.begin(), cv6.end());
    for (size_t i = 0; i < v6.size(); ++i)
        CPPUNIT_ASSERT(v6[i % 5] == v5[i % 5] && v6[i % 5] == c5[i % 5]);
    CPPUNIT_ASSERT(v6.size() == 20);
    

    // void insert_(iterator& position, InputIterator& first, InputIterator& last, stl::forward_iterator_tag)
    Cx c7[5] = { -1, -2, -3, -4, -5 };
    stl::vector<Cx> v7, v8;
    v7.assign(c7, c7 + 5);
    v8.insert(v8.end(), v7.rbegin(), v7.rend()); // from other
    v8.insert(v8.begin(), v7.rbegin(), v7.rend()); // from other (moving content)

    for (size_t i = 0; i < v8.size(); ++i)
        CPPUNIT_ASSERT(v8[i] == c7[4 - i % 5]);
    CPPUNIT_ASSERT(v8.size() == 10);

    v8.insert(v8.begin(), v8.rbegin(), v8.rend()); // from self

    for (size_t i = 0; i < 10; ++i) // the first 10 are ascending :(
        CPPUNIT_ASSERT(v8[i] == c7[i % 5]);

    for (size_t i = 10; i < 20; ++i) // the following 10 are descending :(
        CPPUNIT_ASSERT(v8[i] == c7[4 - i % 5]);
    CPPUNIT_ASSERT(v8.size() == 20); // size = 20!

    // void insert_(iterator& position, value_type* first, value_type* last)
    int i9[5] = { -1, -2, -3, -4, -5 };
    stl::vector<int> v9;
    v9.insert(v9.begin(), i9, i9 + 5); // from other
    v9.insert(v9.begin(), i9, i9 + 5); // from other (move content)

    for (size_t i = 0; i < v9.size(); ++i)
        CPPUNIT_ASSERT(v9[i] == i9[i % 5]);
    CPPUNIT_ASSERT(v9.size() == 10);

    v9.insert(v9.begin(), &v9.front(), &v9.back()); // from self

    for (int i = 0; i < 9; ++i)
        CPPUNIT_ASSERT(v9[i] == i9[i % 5]);
    for (int i = 9; i < v9.size(); ++i)
        CPPUNIT_ASSERT(v9[i] == i9[(i - 9) % 5]);
    CPPUNIT_ASSERT(v9.size() == 19);

    Cx c10[5] = { -1, -2, -3, -4, -5 };
    stl::vector<Cx> v10, v11;
    v10.assign(c10, c10 + 5);

    v11.insert(v11.begin(), &v10.front(), &v10.back() + 1); // from other

    for (size_t i = 0; i < v11.size(); ++i)
        CPPUNIT_ASSERT(v11[i] == c10[i]);

    v11.insert(v11.begin(), &v11.front(), &v11.back() + 1); // from self

    for (size_t i = 0; i < v11.size(); ++i)
        CPPUNIT_ASSERT(v11[i] == c10[i % 5]);
    CPPUNIT_ASSERT(v11.size() == 10);

    // void insert_(iterator& position, const value_type* first, const value_type* last)
    stl::vector<Cx> v12;
    const stl::vector<Cx>& cv10 = v10;
    const stl::vector<Cx>& cv12 = v12;
    v12.insert(v12.begin(), &cv10.front(), &cv10.back() + 1); // from other
    v12.insert(v12.begin(), &cv12.front(), &cv12.back() + 1); // from self

    for (size_t i = 0; i < v12.size(); ++i)
        CPPUNIT_ASSERT(v12[i] == c10[i % 5]);
    CPPUNIT_ASSERT(v12.size() == 10);


    // void insert_(iterator& position, InputIterator n, InputIterator value, stl::input_iterator_tag)
    stl::vector<int> v13;
    v13.insert(v13.end(), 1, -1);
    int& i13val = v13.front();
    v13.insert(v13.begin(), 1, i13val);

    CPPUNIT_ASSERT(v13[0] == -1 && v13[1] == -1);
    CPPUNIT_ASSERT(v13.size() == 2);
}


void test_vector::erase()
{
    Cx c1[5] = { -1, -2, -3, -4, -5 };
    stl::vector<Cx> v1;
    v1.assign(c1, c1 + 5);

    v1.erase(v1.begin());       //first
    v1.erase(v1.end() - 1);     //last
    v1.erase(v1.begin() + 1);   //middle

    CPPUNIT_ASSERT(v1[0] == c1[1] && v1[1] == c1[3]);
    CPPUNIT_ASSERT(v1.size() == 2);

    stl::vector<Cx> v2;
    v2.assign(c1, c1 + 5);
    stl::vector<Cx>::iterator it = v2.begin();
    while (it != v2.end())
        it = v2.erase(it);

    v2.assign(c1, c1 + 5);
    it = v2.erase(v2.begin() + 2, v2.end());
    CPPUNIT_ASSERT(it == v2.end());
    CPPUNIT_ASSERT(v2[0] == c1[0] && v2[1] == c1[1]);
    CPPUNIT_ASSERT(v2.size() == 2);
}

void test_vector::swap()
{
    Cx cx1[5] = { -1, -2, -3, -4, -5 };
    stl::vector<Cx> v1, v2;
    v1.assign(cx1, cx1 + 5);
    
    CPPUNIT_ASSERT(v1.size() == 5);
    for (size_t i = 0; i < v1.size(); ++i)
        CPPUNIT_ASSERT(v1[i] == cx1[i]);
    CPPUNIT_ASSERT(v2.size() == 0);

    v2.swap(v1);    // vector.swap(vector)

    CPPUNIT_ASSERT(v2.size() == 5);
    for (size_t i = 0; i < v2.size(); ++i)
        CPPUNIT_ASSERT(v2[i] == cx1[i]);
    CPPUNIT_ASSERT(v1.size() == 0);

    stl::swap(v1, v2);  // stl::swap(vector, vector);

    CPPUNIT_ASSERT(v1.size() == 5);
    for (size_t i = 0; i < v1.size(); ++i)
        CPPUNIT_ASSERT(v1[i] == cx1[i]);
    CPPUNIT_ASSERT(v2.size() == 0);
}

void test_vector::clear()
{
    Cx cx1[5] = { -1, -2, -3, -4, -5 };
    stl::vector<Cx> v1;
    v1.assign(cx1, cx1 + 5);

    CPPUNIT_ASSERT(v1.size() == 5);
    for (size_t i = 0; i < v1.size(); ++i)
        CPPUNIT_ASSERT(v1[i] == cx1[i]);

    v1.clear();
    CPPUNIT_ASSERT(v1.size() == 0);
    CPPUNIT_ASSERT(v1.capacity() == 5);
}

void test_vector::get_allocator()
{
    Cx cx1[5] = { -1, -2, -3, -4, -5 };
    stl::vector<Cx> v1;
    v1.assign(cx1, cx1 + 5);

    stl::allocator<Cx> alloc = v1.get_allocator();
    Cx* ptr = alloc.allocate(5);
    alloc.deallocate(ptr, 0);
}

void test_vector::relational_op()
{
    stl::vector<int> foo(3, 100);
    stl::vector<int> bar(2, 200);

    bool op_eq = foo == bar;
    bool op_neq = foo != bar;
    bool op_lt = foo < bar;
    bool op_gt = foo > bar;
    bool op_lte = foo <= bar;
    bool op_gte = foo >= bar;

    CPPUNIT_ASSERT(!op_eq);
    CPPUNIT_ASSERT(op_neq);
    CPPUNIT_ASSERT(op_lt);
    CPPUNIT_ASSERT(!op_gt);
    CPPUNIT_ASSERT(op_lte);
    CPPUNIT_ASSERT(!op_gte);
}

void test_vector::perf1()
{
    Cx cx0[] = /* size = 10x10 = 100 */
    {
        0, -1, -2, -3, -4, -5, -6, -7, -8, -9,
        -10, -11, -12, -13, -14, -15, -16, -17, -18, -19,
        -20, -21, -22, -23, -24, -25, -26, -27, -28, -29,
        -30, -31, -32, -33, -34, -35, -36, -37, -38, -39,
        -40, -41, -42, -43, -44, -45, -46, -47, -48, -49,
        -50, -51, -52, -53, -54, -55, -56, -57, -58, -59,
        -60, -61, -62, -63, -64, -65, -66, -67, -68, -69,
        -70, -71, -72, -73, -74, -75, -76, -77, -78, -79,
        -80, -81, -82, -83, -84, -85, -86, -87, -88, -89,
        -90, -91, -92, -93, -94, -95, -96, -97, -98, -99
    };

    const char* msg1 = "\nstl::vector time=";
    const char* msg2 = "\nstd::vector time=";
    const size_t ONEMIL = 1000000;

    // stl::vector
    {
        typedef stl::vector<Cx> vector;
        time_printer tp(msg1);

#if 0
        // vector()
        for (size_t i = 0; i < ONEMIL; ++i)
        {
            vector v1, v2, v3, v4, v5;
        }

        // explicit vector(size_type n, const T& val = T())
        for (size_t i = 0; i < ONEMIL / 100; ++i)
        {
            vector v1(i % 99, cx0[i % 99]);
        }

        // vector(InputIterator first, InputIterator last)
        for (size_t i = 0; i < ONEMIL / 1000; ++i)
        {
            vector v1(cx0, cx0 + 100);
            vector v2(v1.begin(), v1.end());    // vector(iterator, ..)
            const vector& cv1 = v1;
            vector v3(cv1.begin(), cv1.end());  // vector(const_iterator, ..)
            vector v4(v1.rbegin(), v1.rend());  // vector(reverse_iterator,..)
            vector v5(cv1.rbegin(), cv1.rend());// vector(const_reverse_iterator,..)
            vector v6(cx0, cx0 + 100);          // vector(value_type*, ..)
            const Cx* ccx0 = cx0;
            vector v7(ccx0, ccx0 + 100);        // vector(const value_type*, ..)
            stl::vector<int> v8(i % 100, i % 100);  // vector(Iterator,Iterator)
        }

        // vector(const container& x)
        for (size_t i = 0; i < ONEMIL / 1000; ++i)
        {
            vector v1(cx0, cx0 + 100);
            vector v2(v1);
            vector v3(v1);
            vector v4(v1);
        }

        // container& operator=(const container& x)
        for (size_t i = 0; i < ONEMIL / 1000; ++i)
        {
            vector v1(cx0, cx0 + 100);
            vector v2, v3, v4;
            v2 = v1;
            v3 = v1;
            v4 = v1;
        }

        // container& assign(const container& x)
        for (size_t i = 0; i < ONEMIL / 1000; ++i)
        {
            vector v1(cx0, cx0 + 100);
            vector v2, v3, v4;
            v2.assign(v1);
            v3.assign(v1);
            v4.assign(v1);
        }

        // void assign(size_type n, const value_type& val)
        for (size_t i = 0; i < ONEMIL / 1000; ++i)
        {
            vector v1, v2, v3;
            v1.assign(i % 99, cx0[i % 99]);
            v2.assign(i % 99, cx0[i % 99]);
            v3.assign(i % 99, cx0[i % 99]);
        }
        
        // void assign(InputIterator first, InputIterator last)
        // inline void assign_(iterator& first, iterator& last)
        for (size_t i = 0; i < ONEMIL / 1000; ++i)
        {
            vector v1(cx0, cx0 + 100);
            vector v2, v3, v4, v5;

            v2.assign(v1.begin() + i % 99, v1.end());       // from other
            v2.assign(v2.begin() + (long)v2.size()/3, v2.end());  // from self

            v3.assign(v1.begin(), v1.end() - i % 99);       // from other
            v3.assign(v3.begin(), v3.end() - (long)v3.size() / 3);// from self

            v4.assign(v1.begin() + i % 50, v1.end() - i % 50);  // from other
            v4.assign(v4.begin()+(long)v4.size()/3, v4.end()-(long)v4.size()/3);// from self
        }

        // inline void assign_(const_iterator& first, const_iterator& last)
        for (size_t i = 0; i < ONEMIL / 1000; ++i)
        {
            vector v1(cx0, cx0 + 100);
            vector v2, v3, v4, v5;
            const vector& cv1 = v1, cv2 = v2, cv3 = v3, cv4 = v4, cv5 = v5;

            v2.assign(cv1.begin() + i % 99, cv1.end());                 // from other            
            v2.assign(cv2.begin() + (long)cv2.size() / 3, cv2.end());    // from self

            v3.assign(cv1.begin(), cv1.end() - i % 99);                 // from other
            v3.assign(cv3.begin(), cv3.end() - (long)cv3.size() / 3);   // from self

            v4.assign(cv1.begin() + i % 50, cv1.end() - i % 50);    // from other
            v4.assign(cv4.begin() + (long)cv4.size() / 3, cv4.end() - (long)cv4.size() / 3);// from self
        }

        // inline void assign_(value_type* first, value_type* last)
        for (size_t i = 0; i < ONEMIL / 1000; ++i)
        {
            vector v1(cx0, cx0 + 100);
            vector v2, v3, v4, v5;

            Cx* b1 = &*(v1.begin() + i % 99);
            Cx* e1 = &*(v1.end() - 1) + 1;
            v2.assign(b1, e1);      // from other

            Cx* b2 = &*(v2.begin() + (long)v2.size()/3);
            Cx* e2 = &*(v2.end() - 1) + 1;
            v2.assign(b2, e2);      // from self

            Cx* b3 = &*(v1.begin());
            Cx* e3 = &*(v1.end() - 1 - i % 99) + 1;
            v3.assign(b3, e3);      // from other
            
            Cx* b4 = &*(v3.begin());
            Cx* e4 = &*(v3.end() - 1 - (long)v3.size() / 3) + 1;
            v3.assign(b4, e4);      // from self

            Cx* b5 = &*(v1.begin() + i % 50);
            Cx* e5 = &*(v1.end() - 1 - i % 50) + 1;
            v4.assign(b5, e5);  // from other

            Cx* b6 = &*(v4.begin() + (long)v4.size() / 3);
            Cx* e6 = &*(v4.end() - 1 - (long)v4.size() / 3) + 1;
            v4.assign(b6, e6);// from self
        }

        // inline void assign_(const value_type* first, const value_type* last)
        for (size_t i = 0; i < ONEMIL / 1000; ++i)
        {
            vector v1(cx0, cx0 + 100);
            vector v2, v3, v4, v5;

            const Cx* b1 = &*(v1.begin() + i % 99);
            const Cx* e1 = &*(v1.end() - 1) + 1;
            v2.assign(b1, e1);      // from other

            const Cx* b2 = &*(v2.begin() + (long)v2.size() / 3);
            const Cx* e2 = &*(v2.end() - 1) + 1;
            v2.assign(b2, e2);      // from self

            const Cx* b3 = &*(v1.begin());
            const Cx* e3 = &*(v1.end() - 1 - i % 99) + 1;
            v3.assign(b3, e3);      // from other

            const Cx* b4 = &*(v3.begin());
            const Cx* e4 = &*(v3.end() - 1 - (long)v3.size() / 3) + 1;
            v3.assign(b4, e4);      // from self

            const Cx* b5 = &*(v1.begin() + i % 50);
            const Cx* e5 = &*(v1.end() - 1 - i % 50) + 1;
            v4.assign(b5, e5);  // from other

            const Cx* b6 = &*(v4.begin() + (long)v4.size() / 3);
            const Cx* e6 = &*(v4.end() - 1 - (long)v4.size() / 3) + 1;
            v4.assign(b6, e6);// from self
        }

        // inline void assign_(InputIterator& first, InputIterator& last, stl::forward_iterator_tag)
        for (size_t i = 0; i < ONEMIL / 1000; ++i)
        {
            vector v1(cx0, cx0 + 100);
            vector v2, v3, v4, v5;

            v2.assign(v1.rbegin() + i % 99, v1.rend());       // from other
            v2.assign(v2.rbegin() + (long)v2.size() / 3, v2.rend());  // from self

            v3.assign(v1.rbegin(), v1.rend() - i % 99);       // from other
            v3.assign(v3.rbegin(), v3.rend() - (long)v3.size() / 3);// from self

            v4.assign(v1.rbegin() + i % 50, v1.rend() - i % 50);  // from other
            v4.assign(v4.rbegin() + (long)v4.size() / 3, v4.rend() - (long)v4.size() / 3);// from self
        }


        // inline void assign_(InputIterator count, InputIterator value, stl::input_iterator_tag)
        for (size_t i = 0; i < ONEMIL / 100; ++i)
        {
            stl::vector<int> v1(i % 99, i % 99);
        }

        // begin() + end()
        for (size_t i = 0; i < ONEMIL / 1000; ++i)
        {
            vector v1;
            v1.assign(cx0, cx0 + 100);

            vector::iterator beg = v1.begin();
            vector::iterator beg2 = beg;
            vector::iterator beg3;
            beg3 = beg;
            const Cx& cx = *beg3;
            const int* pint = beg3->get();

            stl::vector<Cx>::iterator& beg4 = ++beg3;   //operator++()
            stl::vector<Cx>::iterator beg5 = beg4++;    //operator++(int)
            stl::vector<Cx>::iterator& beg6 = --beg4;   //operator--()
            stl::vector<Cx>::iterator beg7 = beg6--;    //operator--(int)
            stl::vector<Cx>::iterator& beg8 = (beg6 += 2);  //operator+=(offset)
            stl::vector<Cx>::iterator beg9 = (beg8 + 2);    //operator+()
            stl::vector<Cx>::iterator beg10 = (beg9 -= 2);  //operator-=(offset)
            stl::vector<Cx>::iterator beg11 = (beg10 - 2);  //operator-(offset);
            size_t diff11 = beg10 - beg11;
            bool eq = (beg == beg2);
            bool neq = (beg11 != beg10);
            bool lt = (beg11 < beg10);
            bool gt = (beg10 > beg11);
            bool lte = (beg11 <= beg10);
            bool gte = (beg >= beg2);
            const Cx& cx11 = beg11[2];
        }

        // rbegin() + rend()
        for (size_t i = 0; i < ONEMIL / 100; ++i)
        {
            vector v1;
            v1.assign(cx0, cx0 + 100);

            vector::reverse_iterator beg = v1.rbegin();
            vector::reverse_iterator beg2 = beg;
            vector::reverse_iterator beg3;
            beg3 = beg;
            const Cx& cx = *beg3;
            const int* pint = beg3->get();

            stl::vector<Cx>::reverse_iterator& beg4 = ++beg3;   //operator++()
            stl::vector<Cx>::reverse_iterator beg5 = beg4++;    //operator++(int)
            stl::vector<Cx>::reverse_iterator& beg6 = --beg4;   //operator--()
            stl::vector<Cx>::reverse_iterator beg7 = beg6--;    //operator--(int)
            stl::vector<Cx>::reverse_iterator& beg8 = (beg6 += 2);  //operator+=(offset)
            stl::vector<Cx>::reverse_iterator beg9 = (beg8 + 2);    //operator+()
            stl::vector<Cx>::reverse_iterator beg10 = (beg9 -= 2);  //operator-=(offset)
            stl::vector<Cx>::reverse_iterator beg11 = (beg10 - 2);  //operator-(offset);
            size_t diff11 = beg10 - beg11;
            bool eq = (beg == beg2);
            bool neq = (beg11 != beg10);
            bool lt = (beg11 < beg10);
            bool gt = (beg10 > beg11);
            bool lte = (beg11 <= beg10);
            bool gte = (beg >= beg2);
            const Cx& cx11 = beg11[2];
        }

        // void resize(size_type n, value_type val = value_type())
        for (size_t i = 0; i < ONEMIL / 1000; ++i)
        {
            vector v1, v2, v3, v4, v5;

            v1.resize(i % 99, cx0[i % 99]);
            v2.resize(i % 99, cx0[i % 99]);
            v3.resize(i % 99, cx0[i % 99]);
            v4.resize(i % 99, cx0[i % 99]);
            v5.resize(i % 99, cx0[i % 99]);
        }

        // void reserve(size_type n)
        for (size_t i = 0; i < ONEMIL / 1000; ++i)
        {
            vector v1, v2, v3, v4, v5;

            v1.reserve(i % 99);
            v2.reserve(i % 99);
            v3.reserve(i % 99);
            v4.reserve(i % 99);
            v5.reserve(i % 99);
        }

        // reference operator[](size_type n) const
        for (size_t i = 0; i < ONEMIL / 1000; ++i)
        {
            vector v1(cx0, cx0 + 100);

            const Cx& c1 = v1[i % 99];
            const Cx& c2 = v1[i % 99];
            const Cx& c3 = v1[i % 99];
            const Cx& c4 = v1[i % 99];
            const Cx& c5 = v1[i % 99];
        }

        // const_reference at(size_type n) const
        for (size_t i = 0; i < ONEMIL / 1000; ++i)
        {
            vector v1(cx0, cx0 + 100);

            const Cx& c1 = v1.at(i % 99);
            const Cx& c2 = v1.at(i % 99);
            const Cx& c3 = v1.at(i % 99);
            const Cx& c4 = v1.at(i % 99);
            const Cx& c5 = v1.at(i % 99);
        }

        // front() + back()
        for (size_t i = 0; i < ONEMIL / 1000; ++i)
        {
            vector v1(cx0, cx0 + 100);
            const Cx& f = v1.front();
            const Cx& b = v1.back();
        }

        // void push_back(const value_type& val)
        for (size_t i = 0; i < ONEMIL / 1000; ++i)
        {
            vector v1, v2, v3, v4;
            for (size_t j = 0; j < i % 99; ++j)
            {
                v1.push_back(cx0[j]);
                v2.push_back(cx0[j]);
                v3.push_back(cx0[j]);
                v4.push_back(cx0[j]);
            }
        }

        // void pop_back()
        for (size_t i = 0; i < ONEMIL / 1000; ++i)
        {
            vector v1(cx0, cx0 + 100);
            while (!v1.empty())
                v1.pop_back();
        }

        // iterator insert(iterator position, const value_type& val)
        for (size_t i = 0; i < ONEMIL / 1000; ++i)
        {
            vector v1;
            for (size_t j = 0; j < i % 99; ++j)
            {
                v1.insert(v1.begin(), cx0[j]);
                v1.insert(v1.end(), v1.back());
            }
        }

        // void insert(iterator position, size_type n, const value_type& val)
        for (size_t i = 0; i < ONEMIL / 1000; ++i)
        {
            vector v1;
            for (size_t j = 0; j < i % 99; ++j)
            {
                v1.insert(v1.begin(), 1, cx0[j]);
                v1.insert(v1.end(), 1, v1.back());
            }
        }

        // void insert(iterator position, InputIterator first, InputIterator last)
        // inline void insert_(iterator& position, iterator& first, iterator& last)
        for (size_t i = 0; i < ONEMIL / 1000; ++i)
        {
            vector v1(cx0, cx0 + 100);
            vector v2, v3, v4, v5;
            vector::iterator it;

            v2.insert(v2.end(), v1.begin() + i % 99, v1.end());       // from other
            it = v2.begin() + (long)v2.size() / 2;
            v2.insert(it, v2.begin() + (long)v2.size() / 3, v2.end());  // from self

            v3.insert(v3.end(), v1.begin(), v1.end() - i % 99);       // from other
            it = v3.begin() + (long)v3.size() / 2;
            v3.insert(it, v3.begin(), v3.end() - (long)v3.size() / 3);// from self

            v4.insert(v4.end(), v1.begin() + i % 50, v1.end() - i % 50);  // from other
            it = v4.begin() + (long)v4.size() / 2;
            v4.insert(it, v4.begin() + (long)v4.size() / 3, v4.end() - (long)v4.size() / 3);// from self
        }

        // inline void insert_(iterator& position, const_iterator& first, const_iterator& last)
        for (size_t i = 0; i < ONEMIL / 1000; ++i)
        {
            vector v1(cx0, cx0 + 100);
            const vector& cv1 = v1;
            vector v2, v3, v4, v5;
            vector::iterator it;
            const vector& cv2 = v2, cv3 = v3, cv4 = v4, cv5 = v5;

            v2.insert(v2.end(), cv1.begin() + i % 99, cv1.end());       // from other
            it = v2.begin() + (long)v2.size() / 2;
            v2.insert(it, cv2.begin() + (long)cv2.size() / 3, cv2.end());  // from self

            v3.insert(v3.end(), cv1.begin(), cv1.end() - i % 99);       // from other
            it = v3.begin() + (long)v3.size() / 2;
            v3.insert(it, cv3.begin(), cv3.end() - (long)cv3.size() / 3);// from self

            v4.insert(v4.end(), cv1.begin() + i % 50, cv1.end() - i % 50);  // from other
            it = v4.begin() + (long)v4.size() / 2;
            v4.insert(it, cv4.begin() + (long)cv4.size() / 3, cv4.end() - (long)cv4.size() / 3);// from self
        }

        // inline void insert_(iterator& position, value_type* first, value_type* last)
        for (size_t i = 0; i < ONEMIL / 1000; ++i)
        {
            vector v1(cx0, cx0 + 100);
            vector v2, v3, v4, v5;

            Cx* b1 = &*(v1.begin() + i % 99);
            Cx* e1 = &*(v1.end() - 1) + 1;
            v2.insert(v2.end(), b1, e1);      // from other

            Cx* b2 = &*(v2.begin() + (long)v2.size() / 3);
            Cx* e2 = &*(v2.end() - 1) + 1;
            v2.insert(v2.begin() + (long)v2.size()/2, b2, e2);      // from self

            Cx* b3 = &*(v1.begin());
            Cx* e3 = &*(v1.end() - 1 - i % 99) + 1;
            v3.insert(v3.end(), b3, e3);      // from other

            Cx* b4 = &*(v3.begin());
            Cx* e4 = &*(v3.end() - 1 - (long)v3.size() / 3) + 1;
            v3.insert(v3.begin() + (long)v3.size()/2, b4, e4);      // from self

            Cx* b5 = &*(v1.begin() + i % 50);
            Cx* e5 = &*(v1.end() - 1 - i % 50) + 1;
            v4.insert(v4.end(), b5, e5);  // from other

            Cx* b6 = &*(v4.begin() + (long)v4.size() / 3);
            Cx* e6 = &*(v4.end() - 1 - (long)v4.size() / 3) + 1;
            v4.insert(v4.begin() + (long)v4.size()/2, b6, e6);// from self
        }

        // inline void insert_(iterator& position, const value_type* first, const value_type* last)
        for (size_t i = 0; i < ONEMIL / 1000; ++i)
        {
            vector v1(cx0, cx0 + 100);
            vector v2, v3, v4, v5;

            const Cx* b1 = &*(v1.begin() + i % 99);
            const Cx* e1 = &*(v1.end() - 1) + 1;
            v2.insert(v2.end(), b1, e1);      // from other

            const Cx* b2 = &*(v2.begin() + (long)v2.size() / 3);
            const Cx* e2 = &*(v2.end() - 1) + 1;
            v2.insert(v2.begin() + (long)v2.size() / 2, b2, e2);      // from self

            const Cx* b3 = &*(v1.begin());
            const Cx* e3 = &*(v1.end() - 1 - i % 99) + 1;
            v3.insert(v3.end(), b3, e3);      // from other

            const Cx* b4 = &*(v3.begin());
            const Cx* e4 = &*(v3.end() - 1 - (long)v3.size() / 3) + 1;
            v3.insert(v3.begin() + (long)v3.size() / 2, b4, e4);      // from self

            const Cx* b5 = &*(v1.begin() + i % 50);
            const Cx* e5 = &*(v1.end() - 1 - i % 50) + 1;
            v4.insert(v4.end(), b5, e5);  // from other

            const Cx* b6 = &*(v4.begin() + (long)v4.size() / 3);
            const Cx* e6 = &*(v4.end() - 1 - (long)v4.size() / 3) + 1;
            v4.insert(v4.begin() + (long)v4.size() / 2, b6, e6);// from self
        }

        // inline void insert_(iterator& position, InputIterator& first, InputIterator& last, stl::forward_iterator_tag)
        for (size_t i = 0; i < ONEMIL / 1000; ++i)
        {
            vector v1(cx0, cx0 + 100);
            vector v2, v3, v4, v5;
            vector::iterator it;

            v2.insert(v2.end(), v1.rbegin() + i % 99, v1.rend());       // from other
            it = v2.begin() + (long)v2.size() / 2;
            v2.insert(it, v2.rbegin() + (long)v2.size() / 3, v2.rend());  // from self

            v3.insert(v3.end(), v1.rbegin(), v1.rend() - i % 99);       // from other
            it = v3.begin() + (long)v3.size() / 2;
            v3.insert(it, v3.rbegin(), v3.rend() - (long)v3.size() / 3);// from self

            v4.insert(v4.end(), v1.rbegin() + i % 50, v1.rend() - i % 50);  // from other
            it = v4.begin() + (long)v4.size() / 2;
            v4.insert(it, v4.rbegin() + (long)v4.size() / 3, v4.rend() - (long)v4.size() / 3);// from self
        }

        // inline void insert_(iterator& position, InputIterator n, InputIterator value, stl::input_iterator_tag)
        for (size_t i = 0; i < ONEMIL / 1000; ++i)
        {
            stl::vector<int> v1, v2, v3, v4, v5;
            v1.insert(v1.end(), i % 99, i % 99);
            v1.insert(v1.begin() + (long)v1.size(), i % 99, i % 99);
            v1.insert(v1.begin(), i % 99, i % 99);
        }

#endif
        // iterator erase(iterator position)
        for (size_t i = 0; i < ONEMIL / 1000; ++i)
        {
            vector v1(cx0, cx0 + 100);
            while (!v1.empty())
                v1.erase(v1.begin());
        }

        // iterator erase(iterator first, iterator last)
        for (size_t i = 0; i < ONEMIL / 100; ++i)
        {
            vector v1(cx0, cx0 + 100);
            while (!v1.empty())
            {
                v1.erase(v1.begin() + (long)v1.size() / 2, v1.end());
            }
        }

    }
}

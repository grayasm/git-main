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

    // I have the feeling that mem_move leaks memory
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

void test_vector::perf1()
{
    const char* msg1 = "\nstl::vector time=";
    const char* msg2 = "\nstd::vector time=";

    //stl::vector
    {
        typedef stl::vector<Cx> vector;
        time_printer tp(msg1);

        vector v0;
        for (int i = 0; i < 5000; ++i)
            v0.push_back(Cx(i));

        // inline void insert_(iterator& position, const_iterator& first, const_iterator& last)
        // -- stl is worse 0.81 vs 0.60 :)
        for (size_t i = 0; i < 1000; ++i)
        {
            vector v1(v0);
            vector v2(v1), v3(v1), v4(v1), v5(v1);
            const vector& cv2 = v2;
            const vector& cv3 = v3;
            const vector& cv4 = v4;
            const vector& cv5 = v5;

            v2.insert(v2.begin() + (long)i % v0.size(), cv2.begin(), cv2.end());
            v3.insert(v3.begin() + (long)i % v0.size(), cv3.begin() + (long)i % v0.size(), cv3.end());
            v4.insert(v4.begin(), cv4.begin(), cv4.end() - (long)i % v0.size());
            v5.insert(v5.end(), cv5.end(), cv5.end());
        }        
    }

    // std::vector
    {
        typedef std::vector<Cx> vector;
        time_printer tp(msg2);

        vector v0;
        for (int i = 0; i < 5000; ++i)
            v0.push_back(Cx(i));

        // inline void insert_(iterator& position, const_iterator& first, const_iterator& last)
        // -- stl is worse 0.81 vs 0.60 :)
        for (size_t i = 0; i < 1000; ++i)
        {
            vector v1(v0);
            vector v2(v1), v3(v1), v4(v1), v5(v1);
            const vector& cv2 = v2;
            const vector& cv3 = v3;
            const vector& cv4 = v4;
            const vector& cv5 = v5;

            v2.insert(v2.begin() + (long)i % v0.size(), cv2.begin(), cv2.end());
            v3.insert(v3.begin() + (long)i % v0.size(), cv3.begin() + (long)i % v0.size(), cv3.end());
            v4.insert(v4.begin(), cv4.begin(), cv4.end() - (long)i % v0.size());
            v5.insert(v5.end(), cv5.end(), cv5.end());
        }
    }
}

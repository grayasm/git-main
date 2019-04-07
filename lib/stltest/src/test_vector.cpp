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

// Don't shoot for performance yet. Get the everything correct first!
void test_vector::ctor()
{
    // vector()
    stl::vector<char> v1;
    
    // vector(size_t, const T&);
    stl::vector<short> v2((size_t)5, (short)-1);
    for (int i = 0; i < 5; ++i)
    {
        if (v2[i] != -1)
            CPPUNIT_ASSERT(false);
    }
    CPPUNIT_ASSERT(v2.size() == 5);

    Cx c2(-101);
    stl::vector<Cx> v2_((size_t)3, c2);
    for (int i = 0; i < v2_.size(); ++i)
    {
        CPPUNIT_ASSERT(v2_[i] == c2);
    }
    CPPUNIT_ASSERT(v2_.size() == 3);


    // vector<InputIterator>(InputIterator first, InputIterator last);
    signed char sc1[5] = { 'a', 'b', 'c', 'd', 'e' };
    stl::vector<signed char> v3(sc1, sc1 + 5);
    for (int i = 0; i < 5; ++i)
    {
        if (v3[i] != sc1[i])
            CPPUNIT_ASSERT(false);
    }
    CPPUNIT_ASSERT(v3.size() == 5);

    Cx c3[5] = { -1, -2, -3, -4, -5 };
    stl::vector<Cx> v3_(c3, c3 + 5);
    for (int i = 0; i < 5; ++i)
    {
        CPPUNIT_ASSERT(v3_[i] == c3[i]);
    }
    CPPUNIT_ASSERT(v3_.size() == 5);


    // vector(const vector&)
    stl::vector<float> v4;
    for (float f = 1.1f; f < 6; f += 1.1f)
        v4.push_back(f);
    stl::vector<float> v5(v4);
    for (int i = 0; i < v4.size(); ++i)
    {
        if (!is_eq(v4[i], v5[i], 1e-4f))
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
    stl::vector<Cx> v3_;
    for (int i = 0; i < 5; ++i)
    {
        v3_.push_back(c3[i]);
    }
    const Cx& c3addr = *(v3_.begin() + 3);
    v3_.assign((size_t)3, c3addr); // self
    for (int i = 0; i < v3_.size(); ++i)
    {
        CPPUNIT_ASSERT(v3_[i] == c3[3]);
    }
    CPPUNIT_ASSERT(v3_.size() == 3);
    
    // void assign_(iterator, iterator);
    stl::vector<Cx> v4_, v5_;
    v4_.assign(c3, c3 + 5);
    v5_.assign(v4_.begin(), v4_.end()); // iterator

    for (int i = 0; i < v4_.size(); ++i)
        CPPUNIT_ASSERT(v5_[i] == v4_[i]);
    CPPUNIT_ASSERT(v5_.size() == v4_.size());

    const stl::vector<Cx>& cv4_ = v4_;
    v5_.assign(cv4_.begin(), cv4_.end()); // const_iterator
    
    for (int i = 0; i < v4_.size(); ++i)
        CPPUNIT_ASSERT(v5_[i] == v4_[i]);
    CPPUNIT_ASSERT(v5_.size() == v4_.size());

    v5_.assign(v4_.rbegin(), v4_.rend()); // reverse_iterator
    for (int i = 0; i < v4_.size(); ++i)
        CPPUNIT_ASSERT(v5_[i] == v4_[v4_.size() - i - 1]);
    CPPUNIT_ASSERT(v5_.size() == v4_.size());

    v5_.assign(cv4_.rbegin(), cv4_.rend()); // const_reverse_iterator
    for (int i = 0; i < cv4_.size(); ++i)
        CPPUNIT_ASSERT(v5_[i] == cv4_[cv4_.size() - i - 1]);
    CPPUNIT_ASSERT(v5_.size() == cv4_.size());

    v5_.assign(v4_.begin(), v4_.end());
    v5_.assign(v5_.begin() + 2, v5_.end()); // iterator (self assignment)
    for (int i = 0; i < v5_.size(); ++i)
        CPPUNIT_ASSERT(v5_[i] == v4_[i + 2]);
    CPPUNIT_ASSERT(v5_.size() == v4_.size() - 2);
    

    v5_.assign(v4_.begin(), v4_.end());
    stl::vector<Cx>::const_iterator v5_cib = v5_.begin(), v5_cie = v5_.end();
    v5_.assign(v5_cib, v5_cie - 2); // const_iterator (self assignment)
    
    for (int i = 0; i < v5_.size(); ++i)
        CPPUNIT_ASSERT(v5_[i] == v4_[i]);
    CPPUNIT_ASSERT(v5_.size() == v4_.size() - 2);

    v5_.assign(v4_.begin(), v4_.end());
    stl::vector<Cx>::reverse_iterator v5_rib = v5_.rbegin(), v5_rie = v5_.rend();
    v5_.assign(v5_rib + 2, v5_rie); // reverse_iterator (self assignment)

    for (int i = 0; i < v5_.size(); ++i)
        CPPUNIT_ASSERT(v5_[i] == v4_[v4_.size() - i - 3]);
    CPPUNIT_ASSERT(v5_.size() == v4_.size() - 2);

    v5_.assign(v4_.begin(), v4_.end());
    stl::vector<Cx>::const_reverse_iterator v5_crib = v5_.rbegin(),
        v5_crie = v5_.rend();
    v5_.assign(v5_crib, v5_crie - 2); // const_reverse_iterator (self assignment)
    
    for (int i = 0; i < v5_.size(); ++i)
        CPPUNIT_ASSERT(v5_[i] == v4_[v4_.size() - i - 1]);
    CPPUNIT_ASSERT(v5_.size() == v4_.size() - 2);
    
}
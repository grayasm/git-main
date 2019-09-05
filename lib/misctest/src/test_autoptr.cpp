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





//this
#include "test_autoptr.hpp"

//c++
#include <iostream>
#include <list>
#include <vector>
#include <algorithm>

//CppUnit
#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>


//libraries
#include "string.hpp"
#include "exception.hpp"
#include "stream.hpp"
#include "misctest_util.hpp"



//////////////////////////////////////////////////////////////////////////
//////////////////// DATA USED IN AUTOPTR TEST ///////////////////////////
template<typename T>
class base
{
public:
    base(T data):m_data(data){}
    virtual ~base(){}

    virtual T getdata()const =0;

    bool operator<(const base<T>& data) const
    {
        return getdata() < data.getdata();
    }

    bool operator>(const base<T>& data) const
    {
        return getdata() > data.getdata();
    }

protected:
    T m_data ;
};//base


class deriv : public base<long>
{
public:
    deriv(long data)
        : base<long>(data)
        , m_data(-data)
    {
    }

    ~deriv()
    {
    }

    long getdata()const
    {
        return m_data;
    }
protected:
    long m_data ;
};//deriv


template<typename T>
class Tderiv : public base<T>
{
public:
    Tderiv(T data)
        : base<T>(data)
    {
    }

    ~Tderiv(){}

    T getdata()const
    {
        return base<T>::m_data;
    }
};


////////////////////////////////
//child assignament
class MyClass {
public:
    typedef stl::autoptr<MyClass> Ptr;
    MyClass(int val)
    {
        m_child=NULL;
        m_val=val;
    }


    MyClass(const MyClass& t)
    {
        m_child=t.m_child;
        m_val=t.m_val;
    }

    ~MyClass()
    {
    }

    void SetChild(const Ptr &child)
    {
        m_child = child;
    }

    const Ptr &GetChild() const
    {
        return m_child;
    }

    int getVal() const
    {
        return m_val;
    }

private:
    Ptr m_child;
    int m_val;
};


class C1
{
public:
    virtual ~C1(){}
    virtual int f(){ return 91; }
};

class C2 : public C1
{
public:
    ~C2(){}
    virtual int f(){ return 92; }
};



//###########################BEGIN TEST CLASS ####################################
void test_autoptr::setUp()
{	
}

void test_autoptr::tearDown()
{	
}

//##########################BEGIN TEST SUITE######################################
void test_autoptr::test_assignment_with_different_type()
{
	stl::cout << "\n\n\t*******************************************************";
	stl::cout <<   "\n\t* TESTING HEADER: autoptr.hpp                         *";
	stl::cout <<   "\n\t*******************************************************";	
	
	{
		const char* msg = "\n\n\tautoptr<C2>=new C1()";
		time_printer tp(msg, m_print_time);


		stl::autoptr<C2> pc2 = new C1();
		stl::autoptr<C1> pc1 = pc2;
		int _91a = pc1->f();
		int _91b = pc2->f();

		CPPUNIT_ASSERT(_91a == 91 && _91b == 91);
	}
}

void test_autoptr::test_assignment_with_different_type1()
{	
	// TEST
	{
		const char* msg = "\n\n\tautoptr<derived<long>>=autoptr<base<long>> ";
		time_printer tp(msg, m_print_time);


		stl::autoptr<base<long> > ap = NULL ;
		stl::autoptr<deriv> dv=NULL ;
		long data=10;

		Tderiv<long>* tderiv = new Tderiv<long>(data);
		ap=tderiv;
		dv=ap;

		long _10 = dv->getdata() ;
		CPPUNIT_ASSERT(_10 == 10);
	}
}

void test_autoptr::test_assignment_with_different_type3()
{

	//	TEST
	{
		const char* msg = "\n\n\tautoptr<base<long>>=new deriv(long) ";
		time_printer tp(msg, m_print_time);


		//deriv goes -: -100 -> -4
		typedef std::vector<stl::autoptr<base<long> > > lblist ;
		lblist m_list ;
		for(long i=100L; i>0; i-=8)
		{
			m_list.push_back(new deriv(i));
		}//for

		lblist::const_iterator cbeg = m_list.begin();
		lblist::const_iterator cend = m_list.end();

		for(long i=100L; cbeg != cend; i-=8, ++cbeg)
		{
			const stl::autoptr<base<long> >& obj = *cbeg;
			const long& lval = obj->getdata();
			CPPUNIT_ASSERT(lval == -i);
		}//for
	}    
}


bool std_min_element_pred(const stl::autoptr<base<long> >& left,
                          const stl::autoptr<base<long> >& right)
{
    return (*left) < (*right);
}

void test_autoptr::test_operator_less()
{
	//	TEST
	{
		//test for operators: <, >, ==, !=
		const char* msg = "\n\n\tautoptr operator <";
		time_printer tp(msg, m_print_time);


		//deriv goes negative: -100 -> -4
		typedef std::vector<stl::autoptr<base<long> > > lblist ;
		lblist m_list ;
		for(long i=100L; i>0; i-=8)
		{
			m_list.push_back(new deriv(i));
		}//for

		lblist::iterator min =std::min_element(m_list.begin(), m_list.end(), std_min_element_pred);
		long lval = (*min)->getdata();

		CPPUNIT_ASSERT(lval == -100);
	}
}


void test_autoptr::test_operator_great()
{
	//	TEST
	{
		//test for operators: <, >, ==, !=
		const char* msg="\n\n\tautoptr operator >";
		time_printer tp(msg, m_print_time);


		//deriv goes -: -100 -> -4
		typedef std::vector<stl::autoptr<base<long> > > lblist ;
		lblist m_list ;
		for(long i=100L; i>0; i-=8)
		{
			m_list.push_back(new deriv(i));
		}//for

		lblist::iterator max=std::max_element(m_list.begin(), m_list.end(), std_min_element_pred);
		long lval = (*max)->getdata();

		CPPUNIT_ASSERT(lval == -4);
	}
}


bool std_sort_pred(const stl::autoptr<base<long> >& left,
                   const stl::autoptr<base<long> >& right)
{
    return (*left) < (*right);
}



void test_autoptr::test_sort()
{
	//	TEST
	{
		const char* msg="\n\n\tautoptr sort";
		time_printer tp(msg, m_print_time);


		//deriv goes -: -100 -> -4
		typedef std::vector<stl::autoptr<base<long> > > lblist ;
		lblist m_list ;
		for(long i=100L; i>0; i-=8)
		{
			m_list.push_back(new deriv(i));
		}//for

		lblist m_list_sort=m_list ;
		stl::sort(m_list_sort.begin(), m_list_sort.end(), std_sort_pred);
		long min = (*m_list_sort.begin())->getdata();
		long max = (*(--(m_list_sort.end())))->getdata();

		CPPUNIT_ASSERT(min == -100 && max==-4);
	}    
}

void test_autoptr::test_derived_operator_less()
{
	//	TEST
	{
		const char* msg="\n\n\tautoptr operator < with tderived";
		time_printer tp(msg, m_print_time);


		typedef std::vector<stl::autoptr<base<long> > > lblist ;
		lblist m_tdlist;
		for(long i=20; i>=0; --i)
		{
			m_tdlist.push_back(new Tderiv<long>(i));
		}

		long min = (*std::min_element(m_tdlist.begin(), m_tdlist.end(), std_min_element_pred))->getdata();
		CPPUNIT_ASSERT(min == 0);
	}    
}

void test_autoptr::test_derived_operator_great()
{
	//	TEST
	{
		const char* msg="\n\n\tautoptr operator > with tderived";
		time_printer tp(msg, m_print_time);


		typedef std::vector<stl::autoptr<base<long> > > lblist ;
		lblist m_tdlist;
		for(long i=20; i>=0; --i)
		{
			m_tdlist.push_back(new Tderiv<long>(i));
		}

		long max = (*std::max_element(m_tdlist.begin(), m_tdlist.end(), std_min_element_pred))->getdata();
		CPPUNIT_ASSERT(max == 20);
	}
}

void test_autoptr::test_self_assignament()
{
	//	TEST
	{
		const char* msg="\n\n\tautoptr \"self assignamet\"";
		time_printer tp(msg, m_print_time);

		MyClass::Ptr obj01=new MyClass(-1);
		obj01=obj01;
		long lval = obj01->getVal();
		CPPUNIT_ASSERT(lval == -1);
	}
}

void test_autoptr::test_child_assignament()
{
	//	TEST
	{
		const char* msg="\n\n\tautoptr \"child assignment\"";
		time_printer tp(msg, m_print_time);


		MyClass::Ptr a = new MyClass(-1);
		a->SetChild( new MyClass(-2) );
		a = a->GetChild();

		a->SetChild( new MyClass(-3) );
		MyClass::Ptr b = a->GetChild();
		a=b;    
		CPPUNIT_ASSERT(a->getVal() == -3);
	}    
}



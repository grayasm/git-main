/*
  Copyright (C) 2012 Mihai Vasilian

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
#include "test_generic_array.hpp"


//c/c++
#include <iostream>
#include <stdlib.h>
#include <float.h>
#include <vector>
#include <list>
#include <iomanip>

//CppUnit
#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TestResult.h>

//misc
#include "math.hpp"
#include "exception.hpp"
#include "stream.hpp"
#include "misctest_util.hpp"
#include "strconv.hpp"
#include "vector.hpp"
#include "list.hpp"







/*
  TODO: implement test for misc::generic_array<class type, or struct type>
  TODO: self assignment, different version (overlapping regions, etc)
  TODO: const_iterator(iterator), const_reverse_iterator(reverse_iterator)
  TODO: test all exceptions conditions
  TODO: str.size() is 10; str[3] = '\0' -> what does it mean ?
  TODO: should I return str[str.size()] as '\0' ?  what if some change it to smth else ?
  TODO: generic_array cannot hold POD types; a new podvector is required for this; strlen(ptr) on POD ?
*/

//###########################BEGIN TEST CLASS ####################################

void test_generic_array::setUp()
{
}

void test_generic_array::tearDown()
{
}

//##########################BEGIN TEST SUITE######################################
//test begin
//Member functions

//TODO: "generic_array tests with different pod types (floats, longs, etc)"
// data type not detected as POD
// different data types

class nonpod_v0
{
public:
	nonpod_v0():m_p(0){}
	nonpod_v0(const nonpod_v0& np){ *this = np; }
	nonpod_v0(int p):m_p(p){}
	~nonpod_v0(){}
	nonpod_v0& operator=(const nonpod_v0& np)
	{
		if(this!=&np) m_p = np.m_p;
		return *this;
	}
private:
	int m_p;
};

struct non_pod_v0
{
	int val;
	float fval;
	unsigned char ucval;
	void (*f)(int argc, ...);
};
void non_pod_f_v0(int, ...){}




// begin test suite
void test_generic_array::ctor()
{

	{/* using template type misc::generic_array<char> */
		typedef misc::generic_array<char> string;

		string s0("Initial string");

		// constructors used in the same order as described above:
		string s1;
		string s2(s0);
		string s3(s0, 8, 3);
		string s4("A character sequence", 6);
		string s5("Another character sequence");
		string s6(10, 'x');
		string s7a(10, 42);
		string s7b(s0.begin(), s0.begin() + 7);

		CPPUNIT_ASSERT(s1.empty());
		CPPUNIT_ASSERT(strcmp(s2.c_str(), s0.c_str()) == 0);
		CPPUNIT_ASSERT(strcmp(s3.c_str(), "str") == 0);
		CPPUNIT_ASSERT(strcmp(s4.c_str(), "A char") == 0);
		CPPUNIT_ASSERT(strcmp(s5.c_str(), "Another character sequence") == 0);
		CPPUNIT_ASSERT(strcmp(s6.c_str(), "xxxxxxxxxx") == 0);
		CPPUNIT_ASSERT(strcmp(s7a.c_str(), "**********") == 0);
		CPPUNIT_ASSERT(strcmp(s7b.c_str(), "Initial") == 0);
	}

	{/* using other types */
		/* using MSDN samples */
		typedef misc::generic_array<char> string;

		// ctor with C-string
		const char *cstr1a = "Hello Out There.";
		string str1a(cstr1a, 5);
		CPPUNIT_ASSERT(strcmp(str1a.c_str(), "Hello") == 0);

		// ctor with a string
		string str2a("How Do You Do?");
		string str2b(str2a, 7, 7);
		CPPUNIT_ASSERT(strcmp(str2b.c_str(), "You Do?") == 0);

		// ctor with a number of characters of a specific value
		string str3a(5, '9');
		CPPUNIT_ASSERT(strcmp(str3a.c_str(), "99999") == 0);

		string str4a;
		CPPUNIT_ASSERT(str4a.empty() == true);

		// The fifth member function initializes a string from
		// another range of characters
		string str5a("Hello World");
		string str5b(str5a.begin() + 5, str5a.end());
		CPPUNIT_ASSERT(strcmp(str5b.c_str(), " World") == 0);
	}


	misc::cout << "\n\n\t*******************************************************";
	misc::cout <<   "\n\t* TESTING HEADER: generic_array.hpp                   *";
	misc::cout <<   "\n\t*******************************************************";

	misc::cout << "\n\n\tctor---------------------------------------------------";


	typedef misc::allocator<float>  fgallocator;
	typedef misc::allocator<char>   challocator;
	typedef misc::allocator<wchar_t> wchallocator;

	typedef misc::generic_array<float, fgallocator> fgarray0;
	typedef misc::generic_array<char, challocator>  charray0;
	typedef misc::generic_array<wchar_t, wchallocator> wcharray0;

	ctor<fgarray0> ("\n\tgeneric_array<float,A>                  ");
	ctor<charray0> ("\n\tgeneric_array<char,A>                   ");
	ctor<wcharray0>("\n\tgeneric_array<wchar_t,A>                ");


	typedef misc::generic_array<float, fgallocator, misc::GENERIC_ARRAY_HAS_POD_TYPE>   fgarray2;
	typedef misc::generic_array<char, challocator, misc::GENERIC_ARRAY_HAS_POD_TYPE>    charray2;
	typedef misc::generic_array<wchar_t, wchallocator, misc::GENERIC_ARRAY_HAS_POD_TYPE> wcharray2;

	ctor<fgarray2> ("\n\tgeneric_array<float,A,POD>              ");
	ctor<charray2> ("\n\tgeneric_array<char,A,POD>               ");
	ctor<wcharray2>("\n\tgeneric_array<wchar_t,A,POD>            ");

	
	typedef std::basic_string<char, std::char_traits<char>, std::allocator<char> >      charray3;
	typedef std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >  wcharray3;


	ctor<charray3> ("\n\tstd::basic_string<char>                 ");
	ctor<wcharray3>("\n\tstd::wbasic_string<wchar_t>             ");

	typedef std::basic_string<char, std::char_traits<char>, misc::allocator<char> >  charray4;
	typedef std::basic_string<wchar_t, std::char_traits<wchar_t>, misc::allocator<wchar_t> >  wcharray4;

	ctor<charray4> ("\n\tstd::basic_string<char,A>               ");
	ctor<wcharray4>("\n\tstd::wbasic_string<wchar_t,A>           ");
}


void test_generic_array::dtor()
{
	misc::cout << "\n\n\tdtor---------------------------------------------------";

	typedef misc::allocator<float>  fgallocator;
	typedef misc::allocator<char>   challocator;
	typedef misc::allocator<wchar_t> wchallocator;

	typedef misc::generic_array<float, fgallocator> fgarray0;
	typedef misc::generic_array<char, challocator>  charray0;
	typedef misc::generic_array<wchar_t, wchallocator> wcharray0;

	dtor<fgarray0> ("\n\tgeneric_array<float,A>                  ");
	dtor<charray0> ("\n\tgeneric_array<char,A>                   ");
	dtor<wcharray0>("\n\tgeneric_array<wchar_t,A>                ");


	typedef misc::generic_array<float, fgallocator, misc::GENERIC_ARRAY_HAS_POD_TYPE>   fgarray2;
	typedef misc::generic_array<char, challocator, misc::GENERIC_ARRAY_HAS_POD_TYPE>    charray2;
	typedef misc::generic_array<wchar_t, wchallocator, misc::GENERIC_ARRAY_HAS_POD_TYPE> wcharray2;

	dtor<fgarray2> ("\n\tgeneric_array<float,A,POD>              ");
	dtor<charray2> ("\n\tgeneric_array<char,A,POD>               ");
	dtor<wcharray2>("\n\tgeneric_array<wchar_t,A,POD>            ");


	typedef std::basic_string<char, std::char_traits<char>, std::allocator<char> >      charray3;
	typedef std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >  wcharray3;


	dtor<charray3> ("\n\tstd::basic_string<char>                 ");
	dtor<wcharray3>("\n\tstd::wbasic_string<wchar_t>             ");

	typedef std::basic_string<char, std::char_traits<char>, misc::allocator<char> >  charray4;
	typedef std::basic_string<wchar_t, std::char_traits<wchar_t>, misc::allocator<wchar_t> >  wcharray4;

	dtor<charray4> ("\n\tstd::basic_string<char,A>               ");
	dtor<wcharray4>("\n\tstd::wbasic_string<wchar_t,A>           ");
}


void test_generic_array::assignament_op()
{
	{
		using namespace misc::generic_array_ops;
		/* using template type */
		typedef misc::generic_array<char> t_string;

		t_string str1, str2, str3;
		str1 = "Test string: "; // c-string
		str2 = 'x'; // single character
		str3 = str1 + str2; // string

		CPPUNIT_ASSERT(str3 == "Test string: x");
	}

	{ /* using MSDN samples */

		using namespace misc::generic_array_ops;

		// The first member function assigning a
		// character of a certain value to a string
		misc::generic_array<char> str1a("Hello ");
		str1a = '0';
		CPPUNIT_ASSERT(str1a == "0");

		// The second member function assigning the
		// characters of a C-string to a string
		misc::generic_array<char> str1b;
		const char *cstr1b = "Out There";
		str1b = cstr1b;
		CPPUNIT_ASSERT(str1b == "Out There");

		// The third member function assigning the characters
		// from one string to another string in two equivalent
		// ways, comparing the assign and operator =
		misc::generic_array<char> str1c("Hello"), str2c("Wide"), str3c("World");

		CPPUNIT_ASSERT(str1c == "Hello");
		CPPUNIT_ASSERT(str2c == "Wide");

		str1c.assign(str2c);

		CPPUNIT_ASSERT(str1c == "Wide");
		CPPUNIT_ASSERT(str3c == "World");

		str1c = str3c;

		CPPUNIT_ASSERT(str1c == "World");
	}


	misc::cout << "\n\n\tassignament_op-----------------------------------------";

	typedef misc::allocator<float>  fgallocator;
	typedef misc::allocator<char>   challocator;
	typedef misc::allocator<wchar_t> wchallocator;

	typedef misc::generic_array<float, fgallocator> fgarray0;
	typedef misc::generic_array<char, challocator>  charray0;
	typedef misc::generic_array<wchar_t, wchallocator> wcharray0;

	assignament_op<fgarray0> ("\n\tgeneric_array<float,A>                  ");
	assignament_op<charray0> ("\n\tgeneric_array<char,A>                   ");
	assignament_op<wcharray0>("\n\tgeneric_array<wchar_t,A>                ");


	typedef misc::generic_array<float, fgallocator, misc::GENERIC_ARRAY_HAS_POD_TYPE>   fgarray2;
	typedef misc::generic_array<char, challocator, misc::GENERIC_ARRAY_HAS_POD_TYPE>    charray2;
	typedef misc::generic_array<wchar_t, wchallocator, misc::GENERIC_ARRAY_HAS_POD_TYPE> wcharray2;

	assignament_op<fgarray2> ("\n\tgeneric_array<float,A,POD>              ");
	assignament_op<charray2> ("\n\tgeneric_array<char,A,POD>               ");
	assignament_op<wcharray2>("\n\tgeneric_array<wchar_t,A,POD>            ");


	typedef std::basic_string<char, std::char_traits<char>, std::allocator<char> >      charray3;
	typedef std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >  wcharray3;


	assignament_op<charray3> ("\n\tstd::basic_string<char>                 ");
	assignament_op<wcharray3>("\n\tstd::wbasic_string<wchar_t>             ");

	typedef std::basic_string<char, std::char_traits<char>, misc::allocator<char> >  charray4;
	typedef std::basic_string<wchar_t, std::char_traits<wchar_t>, misc::allocator<wchar_t> >  wcharray4;

	assignament_op<charray4> ("\n\tstd::basic_string<char,A>               ");
	assignament_op<wcharray4>("\n\tstd::wbasic_string<wchar_t,A>           ");
}

//Iterators


void test_generic_array::begin()
{
	{
		/* using template type */
		typedef misc::generic_array<char> string;

		string str("Test string");
		string::iterator it;
		size_t i = 0;
		for (it = str.begin(); it < str.end(); it++, ++i)
		{
			CPPUNIT_ASSERT(*it == str[i]);
		}

		string::const_iterator cit;
		i = 0;
		for (cit = str.begin(); cit < str.end(); cit++, ++i)
		{
			CPPUNIT_ASSERT(*cit == str[i]);
		}
	}

	{
		/* using MSDN sample */
		misc::generic_array<char> str1("No way out."), str2;
		misc::generic_array<char>::iterator strp_Iter, str1_Iter, str2_Iter;
		misc::generic_array<char>::const_iterator str1_cIter;

		str1_Iter = str1.begin();

		CPPUNIT_ASSERT(*str1_Iter == 'N');

		CPPUNIT_ASSERT(strcmp(str1.c_str(), "No way out.") == 0);

		// The dereferenced iterator can be used to modify a character
		*str1_Iter = 'G';

		CPPUNIT_ASSERT(*str1_Iter == 'G');
		CPPUNIT_ASSERT(strcmp(str1.c_str(), "Go way out.") == 0);

		// The following line would be an error because iterator is const
		// *str1_cIter = 'g';

		// For an empty string, begin is equivalent to end
		CPPUNIT_ASSERT(str2.begin() == str2.end());

		str1_cIter = str1.begin();
		str1.clear();

		bool bexc = false;
		try
		{
			*str1_cIter;
		}
		catch (const misc::exception& exc)
		{
			exc.what();
			bexc = true;
		}

		CPPUNIT_ASSERT(bexc);
	}


	misc::cout << "\n\n\tbegin--------------------------------------------------";

	typedef misc::allocator<long>   lgallocator;
	typedef misc::allocator<float>  fgallocator;
	typedef misc::allocator<char>   challocator;
	typedef misc::allocator<wchar_t> wchallocator;

	typedef misc::generic_array<long, lgallocator> lgarray0;
	typedef misc::generic_array<float, fgallocator> fgarray0;
	typedef misc::generic_array<char, challocator>  charray0;
	typedef misc::generic_array<wchar_t, wchallocator> wcharray0;


	begin<lgarray0> ("\n\tgeneric_array<long,A>                   ");
	begin<fgarray0> ("\n\tgeneric_array<float,A>                  ");
	begin<charray0> ("\n\tgeneric_array<char,A>                   ");
	begin<wcharray0>("\n\tgeneric_array<wchar_t,A>                ");


	typedef misc::generic_array<long, lgallocator, misc::GENERIC_ARRAY_HAS_POD_TYPE>    lgarray2;
	typedef misc::generic_array<float, fgallocator, misc::GENERIC_ARRAY_HAS_POD_TYPE>   fgarray2;
	typedef misc::generic_array<char, challocator, misc::GENERIC_ARRAY_HAS_POD_TYPE>    charray2;
	typedef misc::generic_array<wchar_t, wchallocator, misc::GENERIC_ARRAY_HAS_POD_TYPE> wcharray2;

	begin<lgarray2> ("\n\tgeneric_array<long,A,POD>               ");
	begin<fgarray2> ("\n\tgeneric_array<float,A,POD>              ");
	begin<charray2> ("\n\tgeneric_array<char,A,POD>               ");
	begin<wcharray2>("\n\tgeneric_array<wchar_t,A,POD>            ");


	typedef std::vector<long, std::allocator<long> > lgarray3;
	typedef std::vector<float, std::allocator<float> > fgarray3;
	typedef std::basic_string<char, std::char_traits<char>, std::allocator<char> >      charray3;
	typedef std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >  wcharray3;


	begin<lgarray3> ("\n\tstd::vector<long>                       ");
	begin<fgarray3> ("\n\tstd::vector<float>                      ");
	begin<charray3> ("\n\tstd::basic_string<char>                 ");
	begin<wcharray3>("\n\tstd::wbasic_string<wchar_t>             ");

	typedef std::vector<long, misc::allocator<long> >            lgarray4;
	typedef std::vector<float, misc::allocator<float> >            fgarray4;
	typedef std::basic_string<char, std::char_traits<char>, misc::allocator<char> >  charray4;
	typedef std::basic_string<wchar_t, std::char_traits<wchar_t>, misc::allocator<wchar_t> >  wcharray4;

	begin<lgarray4> ("\n\tstd::vector<long,A>                     ");
	begin<fgarray4> ("\n\tstd::vector<float,A>                    ");
	begin<charray4> ("\n\tstd::basic_string<char,A>               ");
	begin<wcharray4>("\n\tstd::wbasic_string<wchar_t,A>           ");
}


void test_generic_array::end()
{
	{
		/* using template type */

		typedef misc::generic_array<char> string;

		string str("Test string");
		string::iterator it;
		size_t i = 0;
		for (it = str.begin(); it < str.end(); it++, ++i)
		{
			CPPUNIT_ASSERT(*it == str[i]);
		}

		string::const_iterator cit;
		i = 0;
		for (cit = str.begin(); cit < str.end(); cit++, ++i)
		{
			CPPUNIT_ASSERT(*cit == str[i]);
		}
	}

	{
		/* using MSDN sample */
		misc::generic_array<char> str1("No way out."), str2;
		misc::generic_array<char>::iterator str_Iter, str1_Iter, str2_Iter;
		misc::generic_array<char>::const_iterator str1_cIter;

		str1_Iter = str1.end();
		str1_Iter--;
		str1_Iter--;

		CPPUNIT_ASSERT(*str1_Iter == 't');

		CPPUNIT_ASSERT(strcmp(str1.c_str(), "No way out.") == 0);

		const char* pstr = str1.c_str();

		// end used to test when an iterator has reached the end of its string
		for(str_Iter = str1.begin(); str_Iter != str1.end(); ++str_Iter)
		{
			CPPUNIT_ASSERT(*str_Iter == *pstr++);
		}

		// The dereferenced iterator can be used to modify a character
		*str1_Iter = 'T';
		CPPUNIT_ASSERT(*str1_Iter == 'T');

		CPPUNIT_ASSERT(strcmp(str1.c_str(), "No way ouT.") == 0);

		// The following line would be an error because iterator is const
		// *str1_cIter = 'T';

		// For an empty string, end is equivalent to begin
		CPPUNIT_ASSERT(str2.begin() == str2.end());

		str1_cIter = str1.begin();
		str1.clear();

		bool bexc = false;
		try
		{
			*str1_cIter;
		}
		catch (const misc::exception& exc)
		{
			exc.what();
			bexc = true;
		}

		CPPUNIT_ASSERT(bexc);
	}


	misc::cout << "\n\n\tend----------------------------------------------------";

	typedef misc::allocator<long>   lgallocator;
	typedef misc::allocator<float>  fgallocator;
	typedef misc::allocator<char>   challocator;
	typedef misc::allocator<wchar_t> wchallocator;

	typedef misc::generic_array<long, lgallocator> lgarray0;
	typedef misc::generic_array<float, fgallocator> fgarray0;
	typedef misc::generic_array<char, challocator>  charray0;
	typedef misc::generic_array<wchar_t, wchallocator> wcharray0;


	end<lgarray0> ("\n\tgeneric_array<long,A>                   ");
	end<fgarray0> ("\n\tgeneric_array<float,A>                  ");
	end<charray0> ("\n\tgeneric_array<char,A>                   ");
	end<wcharray0>("\n\tgeneric_array<wchar_t,A>                ");


	typedef misc::generic_array<long, lgallocator, misc::GENERIC_ARRAY_HAS_POD_TYPE>    lgarray2;
	typedef misc::generic_array<float, fgallocator, misc::GENERIC_ARRAY_HAS_POD_TYPE>   fgarray2;
	typedef misc::generic_array<char, challocator, misc::GENERIC_ARRAY_HAS_POD_TYPE>    charray2;
	typedef misc::generic_array<wchar_t, wchallocator, misc::GENERIC_ARRAY_HAS_POD_TYPE> wcharray2;

	end<lgarray2> ("\n\tgeneric_array<long,A,POD>               ");
	end<fgarray2> ("\n\tgeneric_array<float,A,POD>              ");
	end<charray2> ("\n\tgeneric_array<char,A,POD>               ");
	end<wcharray2>("\n\tgeneric_array<wchar_t,A,POD>            ");


	typedef std::vector<long, std::allocator<long> > lgarray3;
	typedef std::vector<float, std::allocator<float> > fgarray3;
	typedef std::basic_string<char, std::char_traits<char>, std::allocator<char> >      charray3;
	typedef std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >  wcharray3;


	end<lgarray3> ("\n\tstd::vector<long>                       ");
	end<fgarray3> ("\n\tstd::vector<float>                      ");
	end<charray3> ("\n\tstd::basic_string<char>                 ");
	end<wcharray3>("\n\tstd::wbasic_string<wchar_t>             ");

	typedef std::vector<long, misc::allocator<long> >            lgarray4;
	typedef std::vector<float, misc::allocator<float> >            fgarray4;
	typedef std::basic_string<char, std::char_traits<char>, misc::allocator<char> >  charray4;
	typedef std::basic_string<wchar_t, std::char_traits<wchar_t>, misc::allocator<wchar_t> >  wcharray4;

	end<lgarray4> ("\n\tstd::vector<long,A>                     ");
	end<fgarray4> ("\n\tstd::vector<float,A>                    ");
	end<charray4> ("\n\tstd::basic_string<char,A>               ");
	end<wcharray4>("\n\tstd::wbasic_string<wchar_t,A>           ");
}


void test_generic_array::rbegin()
{
	{
		/* using template type */
		typedef misc::generic_array<char> string;

		string str("now step live...");
		string::reverse_iterator rit;
		size_t i = str.size() - 1;

//TODO: "test < on reverse_iterator"

		for(rit = str.rbegin(); rit < str.rend(); rit++, --i)
		{
			CPPUNIT_ASSERT(*rit == str[i]);
		}

		string::const_reverse_iterator crit;
		i = str.size() - 1;
		for(crit = str.rbegin(); crit < str.rend(); crit++, --i)
		{
			CPPUNIT_ASSERT(*crit == str[i]);
		}
	}

	{
		/* using MSDN sample */
		misc::generic_array<char> str1("Able was I ere I saw Elba"), str2;
		misc::generic_array<char>::reverse_iterator str_rIter, str1_rIter, str2_rIter;
		misc::generic_array<char>::const_reverse_iterator str1_rcIter;

		str1_rIter = str1.rbegin();

		CPPUNIT_ASSERT(*str1_rIter == 'a');

		const char* ptr = str1.c_str();
		size_t pos = str1.size() - 1;

		for(str_rIter = str1.rbegin(); str_rIter != str1.rend(); str_rIter++)
		{
			CPPUNIT_ASSERT(*str_rIter == *(ptr + pos--));
		}

		// The dereferenced iterator can be used to modify a character
		*str1_rIter = 'A';

		CPPUNIT_ASSERT(*str1_rIter == 'A');
		pos = str1.size() - 1;

		for (str_rIter = str1.rbegin(); str_rIter != str1.rend(); str_rIter++)
		{
			CPPUNIT_ASSERT(*str_rIter == *(ptr + pos--));
		}

		// The following line would be an error because iterator is const
		// *str1_rcIter = 'A';

		// For an empty string, begin is equivalent to end
		CPPUNIT_ASSERT(str2.rbegin() == str2.rend());
	}


	misc::cout << "\n\n\trbegin-------------------------------------------------";

	typedef misc::allocator<long>   lgallocator;
	typedef misc::allocator<float>  fgallocator;
	typedef misc::allocator<char>   challocator;
	typedef misc::allocator<wchar_t> wchallocator;

	typedef misc::generic_array<long, lgallocator> lgarray0;
	typedef misc::generic_array<float, fgallocator> fgarray0;
	typedef misc::generic_array<char, challocator>  charray0;
	typedef misc::generic_array<wchar_t, wchallocator> wcharray0;


	rbegin<lgarray0> ("\n\tgeneric_array<long,A>                   ");
	rbegin<fgarray0> ("\n\tgeneric_array<float,A>                  ");
	begin<charray0>  ("\n\tgeneric_array<char,A>                   ");
	rbegin<wcharray0>("\n\tgeneric_array<wchar_t,A>                ");


	typedef misc::generic_array<long, lgallocator, misc::GENERIC_ARRAY_HAS_POD_TYPE>    lgarray2;
	typedef misc::generic_array<float, fgallocator, misc::GENERIC_ARRAY_HAS_POD_TYPE>   fgarray2;
	typedef misc::generic_array<char, challocator, misc::GENERIC_ARRAY_HAS_POD_TYPE>    charray2;
	typedef misc::generic_array<wchar_t, wchallocator, misc::GENERIC_ARRAY_HAS_POD_TYPE> wcharray2;

	rbegin<lgarray2> ("\n\tgeneric_array<long,A,POD>               ");
	rbegin<fgarray2> ("\n\tgeneric_array<float,A,POD>              ");
	rbegin<charray2> ("\n\tgeneric_array<char,A,POD>               ");
	rbegin<wcharray2>("\n\tgeneric_array<wchar_t,A,POD>            ");


	typedef std::vector<long, std::allocator<long> > lgarray3;
	typedef std::vector<float, std::allocator<float> > fgarray3;
	typedef std::basic_string<char, std::char_traits<char>, std::allocator<char> >      charray3;
	typedef std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >  wcharray3;

	rbegin<lgarray3> ("\n\tstd::vector<long>                       ");
	rbegin<fgarray3> ("\n\tstd::vector<float>                      ");
	rbegin<charray3> ("\n\tstd::basic_string<char>                 ");
	rbegin<wcharray3>("\n\tstd::wbasic_string<wchar_t>             ");

	typedef std::vector<long, misc::allocator<long> >            lgarray4;
	typedef std::vector<float, misc::allocator<float> >            fgarray4;
	typedef std::basic_string<char, std::char_traits<char>, misc::allocator<char> >  charray4;
	typedef std::basic_string<wchar_t, std::char_traits<wchar_t>, misc::allocator<wchar_t> >  wcharray4;

	rbegin<lgarray4> ("\n\tstd::vector<long,A>                     ");
	rbegin<fgarray4> ("\n\tstd::vector<float,A>                    ");
	rbegin<charray4> ("\n\tstd::basic_string<char,A>               ");
	rbegin<wcharray4>("\n\tstd::wbasic_string<wchar_t,A>           ");
}


void test_generic_array::rend()
{
	{
		/* using template type */
		typedef misc::generic_array<char> string;

		string str("now step live...");
		string::reverse_iterator rit;
		size_t i = str.size() - 1;
		for (rit = str.rbegin(); rit < str.rend(); rit++, --i)
		{
			CPPUNIT_ASSERT(*rit == str[i]);
		}

		string::const_reverse_iterator crit;
		i = str.size() - 1;
		for (crit = str.rbegin(); crit < str.rend(); crit++, --i)
		{
			CPPUNIT_ASSERT(*crit == str[i]);
		}
	}

	{
		/* using MSDN sample */
		misc::generic_array<char> str1("Able was I ere I saw Elba"), str2;
		misc::generic_array<char>::reverse_iterator str_rIter, str1_rIter, str2_rIter;
		misc::generic_array<char>::const_reverse_iterator str1_rcIter;

		str1_rIter = str1.rbegin();

		CPPUNIT_ASSERT(*str1_rIter == 'a');

		const char* ptr = str1.c_str();
		size_t pos = str1.size() - 1;

		for (str_rIter = str1.rbegin(); str_rIter != str1.rend(); str_rIter++)
		{
			CPPUNIT_ASSERT(*str_rIter == *(ptr + pos--));
		}

		// The dereferenced iterator can be used to modify a character
		*str1_rIter = 'A';

		CPPUNIT_ASSERT(*str1_rIter == 'A');
		pos = str1.size() - 1;

		for (str_rIter = str1.rbegin(); str_rIter != str1.rend(); str_rIter++)
		{
			CPPUNIT_ASSERT(*str_rIter == *(ptr + pos--));
		}

		// The following line would be an error because iterator is const
		// *str1_rcIter = 'A';

		// For an empty string, begin is equivalent to end
		CPPUNIT_ASSERT(str2.rbegin() == str2.rend());
	}



	misc::cout << "\n\n\trend---------------------------------------------------";

	typedef misc::allocator<long>   lgallocator;
	typedef misc::allocator<float>  fgallocator;
	typedef misc::allocator<char>   challocator;
	typedef misc::allocator<wchar_t> wchallocator;

	typedef misc::generic_array<long, lgallocator> lgarray0;
	typedef misc::generic_array<float, fgallocator> fgarray0;
	typedef misc::generic_array<char, challocator>  charray0;
	typedef misc::generic_array<wchar_t, wchallocator> wcharray0;


	rend<lgarray0> ("\n\tgeneric_array<long,A>                   ");
	rend<fgarray0> ("\n\tgeneric_array<float,A>                  ");
	rend<charray0> ("\n\tgeneric_array<char,A>                   ");
	rend<wcharray0>("\n\tgeneric_array<wchar_t,A>                ");


	typedef misc::generic_array<long, lgallocator, misc::GENERIC_ARRAY_HAS_POD_TYPE>    lgarray2;
	typedef misc::generic_array<float, fgallocator, misc::GENERIC_ARRAY_HAS_POD_TYPE>   fgarray2;
	typedef misc::generic_array<char, challocator, misc::GENERIC_ARRAY_HAS_POD_TYPE>    charray2;
	typedef misc::generic_array<wchar_t, wchallocator, misc::GENERIC_ARRAY_HAS_POD_TYPE> wcharray2;

	rend<lgarray2> ("\n\tgeneric_array<long,A,POD>               ");
	rend<fgarray2> ("\n\tgeneric_array<float,A,POD>              ");
	rend<charray2> ("\n\tgeneric_array<char,A,POD>               ");
	rend<wcharray2>("\n\tgeneric_array<wchar_t,A,POD>            ");


	typedef std::vector<long, std::allocator<long> > lgarray3;
	typedef std::vector<float, std::allocator<float> > fgarray3;
	typedef std::basic_string<char, std::char_traits<char>, std::allocator<char> >      charray3;
	typedef std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >  wcharray3;


	rend<lgarray3> ("\n\tstd::vector<long>                       ");
	rend<fgarray3> ("\n\tstd::vector<float>                      ");
	rend<charray3> ("\n\tstd::basic_string<char>                 ");
	rend<wcharray3>("\n\tstd::wbasic_string<wchar_t>             ");

	typedef std::vector<long, misc::allocator<long> >            lgarray4;
	typedef std::vector<float, misc::allocator<float> >            fgarray4;
	typedef std::basic_string<char, std::char_traits<char>, misc::allocator<char> >  charray4;
	typedef std::basic_string<wchar_t, std::char_traits<wchar_t>, misc::allocator<wchar_t> >  wcharray4;

	rend<lgarray4> ("\n\tstd::vector<long,A>                     ");
	rend<fgarray4> ("\n\tstd::vector<float,A>                    ");
	rend<charray4> ("\n\tstd::basic_string<char,A>               ");
	rend<wcharray4>("\n\tstd::wbasic_string<wchar_t,A>           ");
}

//Capacity


void test_generic_array::size()
{
	{
		/* using template type */
		typedef misc::generic_array<char> string;

		string str("Test string");

		CPPUNIT_ASSERT(str.size() == 11);
	}

	{
		/* using MSDN sample */
		misc::generic_array<char> str1("Hello world");

		// The size and length member functions differ in name only
		misc::generic_array<char>::size_type sizeStr1, lenStr1;
		sizeStr1 = str1.size();
		lenStr1 = str1.length();

		misc::generic_array<char>::size_type capStr1, max_sizeStr1;
		capStr1 = str1.capacity();
		max_sizeStr1 = str1.max_size();

		// Compare size, length, capacity & max_size of a string
		CPPUNIT_ASSERT(sizeStr1 == 11);

		CPPUNIT_ASSERT(lenStr1 == 11);

		CPPUNIT_ASSERT(capStr1 == 11);

		CPPUNIT_ASSERT(max_sizeStr1 == (size_t) - 1 / sizeof (char));

		str1.erase(6, 5);

		sizeStr1 = str1.size();
		lenStr1 = str1.length();
		capStr1 = str1.capacity();
		max_sizeStr1 = str1.max_size();

		// Compare size, length, capacity & max_size of a string
		// after erasing part of the original string
		CPPUNIT_ASSERT(sizeStr1 == 6);
		CPPUNIT_ASSERT(lenStr1 == 6);
		CPPUNIT_ASSERT(capStr1 == 11);
		CPPUNIT_ASSERT(max_sizeStr1 == (size_t) - 1 / sizeof (char));
	}

	misc::cout << "\n\n\tsize---------------------------------------------------";
}


void test_generic_array::length()
{
	{
		/* using template type */
		typedef misc::generic_array<char> string;

		string str("Test string");

		CPPUNIT_ASSERT(str.length() == 11);
	}

	{
		/* using MSDN sample */
		misc::generic_array<char> str1("Hello world");

		// The size and length member functions differ in name only
		misc::generic_array<char>::size_type sizeStr1, lenStr1;
		sizeStr1 = str1.size();
		lenStr1 = str1.length();

		misc::generic_array<char>::size_type capStr1, max_sizeStr1;
		capStr1 = str1.capacity();
		max_sizeStr1 = str1.max_size();

		// Compare size, length, capacity & max_size of a string
		CPPUNIT_ASSERT(sizeStr1 == 11);

		CPPUNIT_ASSERT(lenStr1 == 11);

		CPPUNIT_ASSERT(capStr1 == 11);

		CPPUNIT_ASSERT(max_sizeStr1 == (size_t) - 1 / sizeof (char));

		str1.erase(6, 5);

		sizeStr1 = str1.size();
		lenStr1 = str1.length();
		capStr1 = str1.capacity();
		max_sizeStr1 = str1.max_size();

		// Compare size, length, capacity & max_size of a string
		// after erasing part of the original string
		CPPUNIT_ASSERT(sizeStr1 == 6);
		CPPUNIT_ASSERT(lenStr1 == 6);
		CPPUNIT_ASSERT(capStr1 == 11);
		CPPUNIT_ASSERT(max_sizeStr1 == (size_t) - 1 / sizeof (char));
	}

	misc::cout << "\n\n\tlength-------------------------------------------------";
}


void test_generic_array::max_size()
{
	typedef misc::generic_array<char> string;

	string str("Test string");

	size_t maxsz = static_cast<size_t>(-1) / sizeof(string::value_type);

	CPPUNIT_ASSERT(str.max_size() == maxsz);

	misc::cout << "\n\n\tmax_size-----------------------------------------------";
}

void test_generic_array::resize()
{
	{
		/* using template type */
		typedef misc::generic_array<char> string;

		size_t sz;
		string str("I like to code in C");

		CPPUNIT_ASSERT(strcmp(str.c_str(), "I like to code in C") == 0);

		sz = str.size();

		str.resize(sz + 2, '+');

		CPPUNIT_ASSERT(strcmp(str.c_str(), "I like to code in C++") == 0);

		str.resize(14);

		CPPUNIT_ASSERT(strcmp(str.c_str(), "I like to code") == 0);

		str.resize(0);

		CPPUNIT_ASSERT(strcmp(str.c_str(), "") == 0);
	}

	{
		/* using MSDN sample */
		misc::generic_array<char> str1("Hello world");
		misc::generic_array<char>::size_type sizeStr1;
		sizeStr1 = str1.size();
		misc::generic_array<char>::size_type capStr1;
		capStr1 = str1.capacity();

		CPPUNIT_ASSERT(sizeStr1 == 11);
		CPPUNIT_ASSERT(capStr1 == 11);

		// Use resize to increase size by 2 elements: exclamations
		str1.resize(str1.size() + 2, '!');

		sizeStr1 = str1.size();
		capStr1 = str1.capacity();

		CPPUNIT_ASSERT(sizeStr1 == 13);
		CPPUNIT_ASSERT(capStr1 == 13);

		// Use resize to increase size by 20 elements:
		str1.resize(str1.size() + 20);

		sizeStr1 = str1.size();
		capStr1 = str1.capacity();

		// Compare size & capacity of a string after resizing
		CPPUNIT_ASSERT(sizeStr1 == 33);
		CPPUNIT_ASSERT(capStr1 == 33);

		const char* str2 = str1.c_str();
		size_t str2len = strlen(str2);

		CPPUNIT_ASSERT(str2len == 13);

		// Use resize to downsize by 28 elements:
		str1.resize(str1.size() - 28);

		sizeStr1 = str1.size();
		capStr1 = str1.capacity();

		CPPUNIT_ASSERT(sizeStr1 == 5);
		CPPUNIT_ASSERT(capStr1 == 33);
	}


	misc::cout << "\n\n\tresize-------------------------------------------------";

	typedef misc::allocator<nonpod_v0> npgallocator;
	resize<misc::generic_array<nonpod_v0, npgallocator, misc::GENERIC_ARRAY_HAS_POD_TYPE> >("\n\tgeneric_array<nonpod_v0,POD>            ");
	resize<misc::generic_array<nonpod_v0, npgallocator> >                                  ("\n\tgeneric_array<nonpod_v0>                ");
	resize<std::vector<nonpod_v0, std::allocator<nonpod_v0> > >                            ("\n\tstd::vector<nonpod_v0>                  ");
	resize<std::vector<nonpod_v0, misc::allocator<nonpod_v0> > >                           ("\n\tstd::vector<nonpod_v0,A>                ");
}


void test_generic_array::capacity()
{
	{
		typedef misc::generic_array<char> string;

		string str("Test string");

		CPPUNIT_ASSERT(str.capacity() == 11);

		str.clear();
		CPPUNIT_ASSERT(str.capacity() == 11);

		string str2;

		CPPUNIT_ASSERT(str2.capacity() > 0);
	}

	{
		/* using MSDN sample */
		misc::generic_array<char> str1("Hello world");
		misc::generic_array<char>::size_type sizeStr1;
		sizeStr1 = str1.size();
		misc::generic_array<char>::size_type capStr1;
		capStr1 = str1.capacity();

		CPPUNIT_ASSERT(sizeStr1 == 11);
		CPPUNIT_ASSERT(capStr1 == 11);

		// Use resize to increase size by 2 elements: exclamations
		str1.resize(str1.size() + 2, '!');

		sizeStr1 = str1.size();
		capStr1 = str1.capacity();

		CPPUNIT_ASSERT(sizeStr1 == 13);
		CPPUNIT_ASSERT(capStr1 == 13);

		// Use resize to increase size by 20 elements:
		str1.resize(str1.size() + 20);

		sizeStr1 = str1.size();
		capStr1 = str1.capacity();

		// Compare size & capacity of a string after resizing
		CPPUNIT_ASSERT(sizeStr1 == 33);
		CPPUNIT_ASSERT(capStr1 == 33);

		const char* str2 = str1.c_str();
		size_t str2len = strlen(str2);

		CPPUNIT_ASSERT(str2len == 13);

		// Use resize to downsize by 28 elements:
		str1.resize(str1.size() - 28);

		sizeStr1 = str1.size();
		capStr1 = str1.capacity();

		CPPUNIT_ASSERT(sizeStr1 == 5);
		CPPUNIT_ASSERT(capStr1 == 33);
	}

	misc::cout << "\n\n\tcapacity-----------------------------------------------";
}


void test_generic_array::reserve()
{
	{
		typedef misc::generic_array<char> string;

		string str;

		str.reserve(100);

		CPPUNIT_ASSERT(str.capacity() == 100);
	}

	{
		/* using MSDN sample */
		misc::generic_array<char> str1("Hello world");
		misc::generic_array<char>::size_type sizeStr1;
		sizeStr1 = str1.size();
		misc::generic_array<char>::size_type capStr1;
		capStr1 = str1.capacity();

		CPPUNIT_ASSERT(sizeStr1 == 11);
		CPPUNIT_ASSERT(capStr1 == 11);

		// Use resize to increase size by 2 elements: exclamations
		str1.resize(str1.size() + 2, '!');

		sizeStr1 = str1.size();
		capStr1 = str1.capacity();

		CPPUNIT_ASSERT(sizeStr1 == 13);
		CPPUNIT_ASSERT(capStr1 == 13);

		// Use resize to increase size by 20 elements:
		str1.resize(str1.size() + 20);

		sizeStr1 = str1.size();
		capStr1 = str1.capacity();

		// Compare size & capacity of a string after resizing
		CPPUNIT_ASSERT(sizeStr1 == 33);
		CPPUNIT_ASSERT(capStr1 == 33);

		const char* str2 = str1.c_str();
		size_t str2len = strlen(str2);

		CPPUNIT_ASSERT(str2len == 13);

		// Use resize to downsize by 28 elements:
		str1.resize(str1.size() - 28);

		sizeStr1 = str1.size();
		capStr1 = str1.capacity();

		CPPUNIT_ASSERT(sizeStr1 == 5);
		CPPUNIT_ASSERT(capStr1 == 33);
	}


	misc::cout << "\n\n\treserve------------------------------------------------";

	reserve<misc::generic_array<nonpod_v0, misc::allocator<nonpod_v0>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >("\n\tgeneric_array<nonpod_v0,POD>            ");
	reserve<misc::generic_array<nonpod_v0, misc::allocator<nonpod_v0> > >                                 ("\n\tgeneric_array<nonpod_v0>                ");
	reserve<std::vector<nonpod_v0, std::allocator<nonpod_v0> > >                                          ("\n\tstd::vector<nonpod_v0>                  ");
	reserve<std::vector<nonpod_v0, misc::allocator<nonpod_v0> > >                                         ("\n\tstd::vector<nonpod_v0,A>                ");
}


void test_generic_array::clear()
{
	{
		typedef misc::generic_array<char> string;

		string str("Please type some lines of text. Enter a period to finish:\n");

		size_t cap = str.capacity();

		str.clear();

		CPPUNIT_ASSERT(str.size() == 0);
		/* should remain unchanged */
		CPPUNIT_ASSERT(str.capacity() == cap);
	}

	{
		misc::generic_array<char> str1("Hello world"), str2;
		misc::generic_array<char>::iterator str_Iter;
		CPPUNIT_ASSERT(str1.begin() != str1.end());
		str1.clear();
		CPPUNIT_ASSERT(str1.begin() == str1.end());
	}


	misc::cout << "\n\n\tclear--------------------------------------------------";

	clear<misc::generic_array<nonpod_v0, misc::allocator<nonpod_v0>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >("\n\tgeneric_array<nonpod_v0,POD>            ");
	clear<misc::generic_array<nonpod_v0, misc::allocator<nonpod_v0> > >                                 ("\n\tgeneric_array<nonpod_v0>                ");
	clear<std::vector<nonpod_v0, std::allocator<nonpod_v0> > >                                          ("\n\tstd::vector<nonpod_v0>                  ");
	clear<std::vector<nonpod_v0, misc::allocator<nonpod_v0> > >                                         ("\n\tstd::vector<nonpod_v0,A>                ");
}


void test_generic_array::empty()
{
	{
		/* template type */
		typedef misc::generic_array<char> string;

		string str("Please introduce a text. Enter an empty line to finish:\n");

		CPPUNIT_ASSERT(str.empty() == false);

		str.clear();

		CPPUNIT_ASSERT(str.empty() == true);
	}

	{
		/* MSDN sample */
		misc::generic_array<char> str1("Hello world");

		CPPUNIT_ASSERT(!str1.empty());

		misc::generic_array<char> str2;

		CPPUNIT_ASSERT(str2.empty());
	}

	misc::cout << "\n\n\tempty--------------------------------------------------";
}

//Element access


void test_generic_array::operator_access_element()
{
	{
		/* template type */
		typedef misc::generic_array<char> string;

		char check[] = {'T', 'e', 's', 't', ' ', 's', 't', 'r', 'i', 'n', 'g'};
		string str("Test string");
		size_t i;
		for(i = 0; i < str.length(); i++)
		{
			CPPUNIT_ASSERT(str[i] == check[i]);
		}

		const string cstr("Test string");
		for(i = 0; i < cstr.length(); i++)
		{
			CPPUNIT_ASSERT(cstr[i] == check[i]); //operator[](..) const
		}
	}

	{
		/* MSDN sample */
		// The first member function assigning a
		// character of a certain value to a string
		misc::generic_array<char> str1a("Hello ");
		str1a = '0';

		CPPUNIT_ASSERT(strcmp(str1a.c_str(), "0") == 0);

		// The second member function assigning the
		// characters of a C-string to a string
		misc::generic_array<char> str1b;
		const char *cstr1b = "Out There";
		str1b = cstr1b;

		CPPUNIT_ASSERT(strcmp(str1b.c_str(), "Out There") == 0);

		// The third member function assigning the characters
		// from one string to another string in two equivalent
		// ways, comparing the assign and operator =
		misc::generic_array<char> str1c("Hello"), str2c("Wide"), str3c("World");

		str1c.assign(str2c);

		CPPUNIT_ASSERT(strcmp(str1c.c_str(), "Wide") == 0);

		str1c = str3c;

		CPPUNIT_ASSERT(strcmp(str1c.c_str(), "World") == 0);
	}


	misc::cout << "\n\n\toperator_access_element--------------------------------";

	operator_access_element<misc::generic_array<nonpod_v0, misc::allocator<nonpod_v0>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >("\n\tgeneric_array<nonpod_v0,POD>            ");
	operator_access_element<misc::generic_array<nonpod_v0, misc::allocator<nonpod_v0> > >                                 ("\n\tgeneric_array<nonpod_v0>                ");
	operator_access_element<std::vector<nonpod_v0, std::allocator<nonpod_v0> > >                                          ("\n\tstd::vector<nonpod_v0>                  ");
	operator_access_element<std::vector<nonpod_v0, misc::allocator<nonpod_v0> > >                                         ("\n\tstd::vector<nonpod_v0,A>                ");
}


void test_generic_array::at()
{
	{
		/* template type */
		typedef misc::generic_array<char> string;

		string str("Test string");
		for(size_t i = 0; i < str.length(); i++)
		{
			CPPUNIT_ASSERT(str.at(i) == str[i]);
		}
		//return 0;

		const string cstr("Test string");
		for(size_t i = 0; i < cstr.length(); i++)
		{
			CPPUNIT_ASSERT(cstr.at(i) == cstr[i]); //at() const
		}
	}

	{
		/* MSDN sample */
		misc::generic_array<char> str1("Hello world"), str2("Goodbye world");
		const misc::generic_array<char> cstr1("Hello there"), cstr2("Goodbye now");

		using namespace misc::generic_array_ops;

		CPPUNIT_ASSERT(str1 == "Hello world");
		CPPUNIT_ASSERT(str2 == "Goodbye world");

		// Element access to the non-const strings
		misc::generic_array<char>::reference refStr1 = str1 [6];
		misc::generic_array<char>::reference refStr2 = str2.at(3);

		CPPUNIT_ASSERT(refStr1 == 'w');
		CPPUNIT_ASSERT(refStr2 == 'd');

		// Element access to the const strings
		bool null_not_accesible = false;
		try
		{
			misc::generic_array<char>::const_reference null_elem = cstr1[ cstr1.length() ];
			(void)null_elem;
		}
		catch(const misc::exception&)
		{
			null_not_accesible = true;
		}

		CPPUNIT_ASSERT(null_not_accesible);

		/* access null termination via .c_str() */
		misc::generic_array<char>::const_reference crefStr1 = cstr1.c_str()[ cstr1.length() ];
		misc::generic_array<char>::const_reference crefStr2 = cstr2.at(8);

		CPPUNIT_ASSERT(crefStr1 == '\0');
		CPPUNIT_ASSERT(crefStr2 == 'n');
	}

	misc::cout << "\n\n\tat-----------------------------------------------------";

	at<misc::generic_array<nonpod_v0, misc::allocator<nonpod_v0>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >("\n\tgeneric_array<nonpod_v0,POD>            ");
	at<misc::generic_array<nonpod_v0, misc::allocator<nonpod_v0> > >                                 ("\n\tgeneric_array<nonpod_v0>                ");
	at<std::vector<nonpod_v0, std::allocator<nonpod_v0> > >                                          ("\n\tstd::vector<nonpod_v0>                  ");
	at<std::vector<nonpod_v0, misc::allocator<nonpod_v0> > >                                         ("\n\tstd::vector<nonpod_v0,A>                ");
}

//Modifiers


void test_generic_array::operator_plus_equal()
{
	{
		/* typename sample */
		typedef misc::generic_array<char> string;

		string name("John");
		string family("Smith");
		name += " K. "; // c-string
		name += family; // string
		name += '\n'; // character

		CPPUNIT_ASSERT(strcmp(name.c_str(), "John K. Smith\n") == 0);
	}

	{
		using namespace misc::generic_array_ops;

		/* MSDN sample */
		// The first member function
		// appending a single character to a string
		misc::generic_array<char> str1a("Hello");
		CPPUNIT_ASSERT(str1a == "Hello");

		str1a += '!';

		CPPUNIT_ASSERT(str1a == "Hello!");

		// The second member function
		// appending a C-string to a string
		misc::generic_array<char> str1b("Hello ");
		const char *cstr1b = "Out There";

		str1b += cstr1b;

		CPPUNIT_ASSERT(str1b == "Hello Out There");

		// The third member function
		// appending one string to another in two ways,
		// comparing append and operator [ ]
		misc::generic_array<char> str1d("Hello "), str2d("Wide "), str3d("World");

		CPPUNIT_ASSERT(str2d == "Wide ");

		str1d.append(str2d);

		CPPUNIT_ASSERT(str1d == "Hello Wide ");

		str1d += str3d;

		CPPUNIT_ASSERT(str1d == "Hello Wide World");
	}

	misc::cout << "\n\n\toperator_plus_equal------------------------------------";
	operator_plus_equal<misc::generic_array<char, misc::allocator<char>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >("\n\tgeneric_array<char,POD>                 ");
	operator_plus_equal<misc::generic_array<char, misc::allocator<char> > >                                 ("\n\tgeneric_array<char>                     ");
	operator_plus_equal<std::basic_string<char, std::char_traits<char>, std::allocator<char> > >            ("\n\tstd::basic_string<char>                 ");
	operator_plus_equal<std::basic_string<char, std::char_traits<char>, misc::allocator<char> > >           ("\n\tstd::basic_string<char,A>               ");
}


void test_generic_array::append()
{
	{
		/* template typename */
		typedef misc::generic_array<char> string;

		string str;
		string str2 = "Writing ";
		string str3 = "print 10 and then 5 more";

		// used in the same order as described above:
		str.append(str2); // "Writing "
		str.append(str3, 6, 3); // "10 "
		str.append("dots are cool", 5); // "dots "
		str.append("here: "); // "here: "
		str.append(10, '.'); // ".........."
		str.append(str3.begin() + 8, str3.end()); // " and then 5 more"
		str.append<int>(5, 0x2E); // "....."

		CPPUNIT_ASSERT(
			strcmp(str.c_str(),
				   "Writing 10 dots here: .......... and then 5 more.....") == 0);
	}

	{
		using namespace misc::generic_array_ops;

		/* MSDN sample */
		// The first member function
		// appending a C-string to a string
		misc::generic_array<char> str1a("Hello ");
		const char *cstr1a = "Out There ";

		CPPUNIT_ASSERT(str1a == "Hello ");

		str1a.append(cstr1a);

		CPPUNIT_ASSERT(str1a == "Hello Out There ");

		// The second member function
		// appending part of a C-string to a string
		misc::generic_array<char> str1b("Hello ");
		const char *cstr1b = "Out There ";

		str1b.append(cstr1b, 3);

		CPPUNIT_ASSERT(str1b == "Hello Out");

		// The third member function
		// appending part of one string to another
		misc::generic_array<char> str1c("Hello "), str2c("Wide World ");
		str1c.append(str2c, 5, 5);

		CPPUNIT_ASSERT(str1c == "Hello World");

		// The fourth member function
		// appending one string to another in two ways,
		// comparing append and operator [ ]
		misc::generic_array<char> str1d("Hello "), str2d("Wide "), str3d("World ");

		str1d.append(str2d);

		CPPUNIT_ASSERT(str1d == "Hello Wide ");

		str1d += str3d;

		CPPUNIT_ASSERT(str1d == "Hello Wide World ");

		// The fifth member function
		// appending characters to a string
		misc::generic_array<char> str1e("Hello ");
		str1e.append(4, '!');

		CPPUNIT_ASSERT(str1e == "Hello !!!!");

		// The sixth member function
		// appending a range of one string to another
		misc::generic_array<char> str1f("Hello "), str2f("Wide World ");
		str1f.append(str2f.begin() + 5, str2f.end() - 1);

		CPPUNIT_ASSERT(str1f == "Hello World");
	}


	misc::cout << "\n\n\tappend-------------------------------------------------";
	append<misc::generic_array<char, misc::allocator<char>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >("\n\tgeneric_array<char,POD>                 ");
	append<misc::generic_array<char, misc::allocator<char> > >                                 ("\n\tgeneric_array<char>                     ");
	append<std::basic_string<char, std::char_traits<char>, std::allocator<char> > >            ("\n\tstd::basic_string<char>                 ");
	append<std::basic_string<char, std::char_traits<char>, misc::allocator<char> > >           ("\n\tstd::basic_string<char,A>               ");
}


void test_generic_array::push_back()
{
	{
		using namespace misc::generic_array_ops;

		/* template type */
		typedef misc::generic_array<char> string;
		string str2;
		const char* buff = "test.txt OK.\n";
		const char* beg = buff;
		while(*buff != '\0')
		{
			str2.push_back(*buff++);
		}

		CPPUNIT_ASSERT(str2 == beg);
	}

	{
		using namespace misc::generic_array_ops;

		/* MSDN sample */
		misc::generic_array<char> str1("abc");
		misc::generic_array<char>::iterator str_Iter, str1_Iter;

		str1.push_back('d');
		str1_Iter = str1.end();
		str1_Iter--;

		CPPUNIT_ASSERT(*str1_Iter == 'd');

		CPPUNIT_ASSERT(str1 == "abcd");
	}


	misc::cout << "\n\n\tpush_back----------------------------------------------";
	push_back<misc::generic_array<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >("\n\tgeneric_array<int,POD>                  ");
	push_back<misc::generic_array<int, misc::allocator<int> > >                                 ("\n\tgeneric_array<int>                      ");
	push_back<std::vector<int, std::allocator<int> > >                                          ("\n\tstd::vector<int>                        ");
	push_back<std::vector<int, misc::allocator<int> > >                                         ("\n\tstd::vector<int,A>                      ");
}

void test_generic_array::assign()
{
	{
		/* template type */
		typedef misc::generic_array<char> string;

		string str;
		string base = "The quick brown fox jumps over a lazy dog.";

		// used in the same order as described above:

		str.assign(base);
		CPPUNIT_ASSERT(strcmp(str.c_str(), base.c_str()) == 0);

		str.assign(base, 10, 9);
		CPPUNIT_ASSERT(strcmp(str.c_str(), "brown fox") == 0);

		str.assign("pangrams are cool", 7);
		CPPUNIT_ASSERT(strcmp(str.c_str(), "pangram") == 0);

		str.assign("c-string");
		CPPUNIT_ASSERT(strcmp(str.c_str(), "c-string") == 0);

		str.assign(10, '*');
		CPPUNIT_ASSERT(strcmp(str.c_str(), "**********") == 0);

		str.assign<int>(10, 0x2D);
		CPPUNIT_ASSERT(strcmp(str.c_str(), "----------") == 0);

		//#break: fail
		str.assign(base.begin() + 16, base.end() - 12);
		CPPUNIT_ASSERT(strcmp(str.c_str(), "fox jumps over") == 0);
	}

	{
		typedef misc::generic_array<char> string;


		using namespace misc::generic_array_ops;
		/* MSDN sample */
		// The first member function assigning the
		// characters of a C-string to a string
		string str1a;
		const char *cstr1a = "Out There";

		str1a.assign(cstr1a);

		CPPUNIT_ASSERT(str1a == "Out There");

		// The second member function assigning a specific
		// number of the of characters a C-string to a string
		string str1b;
		const char *cstr1b = "Out There";

		str1b.assign(cstr1b, 3);

		CPPUNIT_ASSERT(str1b == "Out");

		// The third member function assigning a specific number
		// of the characters from one string to another string
		string str1c("Hello "), str2c("Wide World ");

		str1c.assign(str2c, 5, 5);

		CPPUNIT_ASSERT(str1c == "World");

		// The fourth member function assigning the characters
		// from one string to another string in two equivalent
		// ways, comparing the assign and operator =
		string str1d("Hello"), str2d("Wide"), str3d("World");

		str1d.assign(str2d);

		CPPUNIT_ASSERT(str1d == "Wide");

		CPPUNIT_ASSERT(str3d == "World");

		str1d = str3d;

		CPPUNIT_ASSERT(str1d == "World");

		// The fifth member function assigning a specific
		// number of characters of a certain value to a string
		string str1e("Hello ");
		str1e.assign(4, '!');

		CPPUNIT_ASSERT(str1e == "!!!!");

		// The sixth member function assigning the value from
		// the range of one string to another string
		string str1f("Hello "), str2f("Wide World ");

		str1f.assign(str2f.begin() + 5, str2f.end() - 1);

		CPPUNIT_ASSERT(str1f == "World");
	}

	{
		typedef misc::generic_array<char> string;

		using namespace misc::generic_array_ops;
		/* self assignment */
		string s0 = s0;
		string s1 = s0.assign(s0.c_str());
		CPPUNIT_ASSERT(s1 == s0);

		s1 = s0.assign(s0.c_str(), (size_t)-1);
		CPPUNIT_ASSERT(s1 == s0);


		s0 = "1234567890";

		//self assignment
		s1 = s0.assign(s0);

		CPPUNIT_ASSERT(s1 == s0);

		//self assignment
		s1 = s0.assign(s0, 3, (size_t)-1);
		string s2 = "4567890"; // for comparison
		CPPUNIT_ASSERT(s1 == s2);

		//self assignment
		s0 = "1234567890";
		s1 = s0.assign(&s0[3], (size_t)-1);
		s2 =    "4567890";
		CPPUNIT_ASSERT( s1 == s2 );


		//using pointer arithmetic since s0[10] throws
		const char* s0a = s0.c_str() + 10;
		s1 = s0.assign( s0a );
		CPPUNIT_ASSERT( s1 == "" );

		//setting 'n' characters
		s0.assign(10, '\0');
		CPPUNIT_ASSERT( s0 == "" );

		s0.assign(10, '\n');
		CPPUNIT_ASSERT( s0 == "\n\n\n\n\n\n\n\n\n\n" );

		s0.assign(10, '\t');
		CPPUNIT_ASSERT( s0 == "\t\t\t\t\t\t\t\t\t\t" );

		//self assignment using iterators
		s0 = "1234567890";
		string::iterator s0ib = s0.begin();
		string::iterator s0ie = s0.end();
		s1 = s0.assign(s0ib, s0ie);
		CPPUNIT_ASSERT( s1 == "1234567890" );
		CPPUNIT_ASSERT( s0 == s1 );

		s0 = "1234567890";
		string::const_iterator s0cib = s0.begin();
		string::const_iterator s0cie = s0.end();
		s1 = s0.assign(s0cib, s0cie);
		CPPUNIT_ASSERT( s1 == "1234567890" );
		CPPUNIT_ASSERT( s0 == s1 );

		//self assignment using iterators in reverse order
		bool diff_negative_not_throwing_at_the_moment = false;
		try
		{
			s1 = s0.assign(s0ie, s0ib);
		}
		catch(misc::exception&)
		{
			diff_negative_not_throwing_at_the_moment = true;
		}
		CPPUNIT_ASSERT( !diff_negative_not_throwing_at_the_moment );

		diff_negative_not_throwing_at_the_moment = false;
		try
		{
			s1 = s0.assign(s0cie, s0cib);
		}catch(misc::exception&)
		{
			diff_negative_not_throwing_at_the_moment = true;
		}
		CPPUNIT_ASSERT( !diff_negative_not_throwing_at_the_moment );


		//self assignment using reverse_iterator(s)
		s0 = "1234567890";
		string::reverse_iterator s0rib = s0.rbegin();
		string::reverse_iterator s0rie = s0.rend();
		s1 = s0.assign(s0rib, s0rie);
		s2 = "0987654321";
		CPPUNIT_ASSERT( s1 == s2 );

		//similar, with a shorter range
		s0 = "1234567890";
		s0rib = s0.rbegin();
		s0rie = s0.rend();
		s0rie -= 4;
		s1 = s0.assign(s0rib, s0rie);
		s2 = "098765";
		CPPUNIT_ASSERT( s1 == s2 );

		//assign from a different container
		s0 = "1234567890";
		s1 = "abcd";
		s2 = s0.assign(s1.rbegin(), s1.rend());
		string s3 = "dcba";
		CPPUNIT_ASSERT( s2 == s3 );


		//self assignment using const_reverse_iterator(s)
		s0 = "1234567890";
		string::const_reverse_iterator s0crib = s0.rbegin();
		string::const_reverse_iterator s0crie = s0.rend();
		s1 = s0.assign(s0crib, s0crie);
		s2 = "0987654321";
		CPPUNIT_ASSERT( s1 == s2 );

		//similar, with a shorter range
		s0 = "1234567890";
		s0crib = s0.rbegin();
		s0crie = s0.rend();
		s0crie -= 4;
		s1 = s0.assign(s0crib, s0crie);
		s2 = "098765";
		CPPUNIT_ASSERT( s1 == s2 );

		//assign with a different
		s0 = "1234567890";
		s1 = "abcd";
		s2 = s0.assign(s1.rbegin(), s1.rend());
		s3 = "dcba";
		CPPUNIT_ASSERT( s2 == s3 );

	}

	misc::cout << "\n\n\tassign-------------------------------------------------";
	assign<misc::generic_array<char, misc::allocator<char>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >("\n\tgeneric_array<char,POD>                 ");
	assign<misc::generic_array<char, misc::allocator<char> > >                                 ("\n\tgeneric_array<char>                     ");
	assign<std::basic_string<char, std::char_traits<char>, std::allocator<char> > >            ("\n\tstd::vector<char>                       ");
	assign<std::basic_string<char, std::char_traits<char>, misc::allocator<char> > >           ("\n\tstd::vector<char,A>                     ");
}

void test_generic_array::insert()
{
	{
		/* template type */
		typedef misc::generic_array<char> string;

		string str = "to be question";
		string str2 = "the ";
		string str3 = "or not to be";
		string::iterator it;

		// used in the same order as described above:
		str.insert(6, str2); // to be (the )question
		str.insert(6, str3, 3, 4); // to be (not )the question
		str.insert(10, "that is cool", 8); // to be not (that is )the question
		str.insert(10, "to be "); // to be not (to be )that is the question
		str.insert(15, 1, ':'); // to be not to be(:) that is the question
		it = str.insert(str.begin() + 5, ','); // to be(,) not to be: that is the question
		str.insert(str.end(), 3, '.'); // to be, not to be: that is the question(...)
		str.insert(it + 2, str3.begin(), str3.begin() + 3); // (or )

		CPPUNIT_ASSERT(strcmp(str.c_str(), "to be, or not to be: that is the question...") == 0);
	}

	{
		using namespace misc::generic_array_ops;

		/* MSDN sample */
		// The first member function inserting a C-string
		// at a given position
		misc::generic_array<char> str1a("way");
		const char *cstr1a = "a";
		str1a.insert(0, cstr1a);

		CPPUNIT_ASSERT(str1a == "away");

		// The second member function inserting a C-string
		// at a given position for a specified number of elements
		misc::generic_array<char> str2a("Good");
		const char *cstr2a = "Bye Bye Baby";
		str2a.insert(4, cstr2a, 3);

		CPPUNIT_ASSERT(str2a == "GoodBye");

		// The third member function inserting a string
		// at a given position
		misc::generic_array<char> str3a("Bye");
		misc::generic_array<char> str3b("Good");
		str3a.insert(0, str3b);

		CPPUNIT_ASSERT(str3a == "GoodBye");

		// The fourth member function inserting part of
		// a string at a given position
		misc::generic_array<char> str4a("Good ");
		misc::generic_array<char> str4b("Bye Bye Baby");
		str4a.insert(5, str4b, 8, 4);

		CPPUNIT_ASSERT(str4a == "Good Baby");

		// The fifth member function inserts a number of characters
		// at a specified position in the string
		misc::generic_array<char> str5("The number is: .");
		str5.insert(15, 3, '3');

		CPPUNIT_ASSERT(str5 == "The number is: 333.");

		// The sixth member function inserts a character
		// at a specified position in the string
		misc::generic_array<char> str6("ABCDFG");
		misc::generic_array<char>::iterator str6_Iter = (str6.begin() + 4);
		str6.insert(str6_Iter, 'e');

		CPPUNIT_ASSERT(str6 == "ABCDeFG");

		// The seventh member function inserts a range
		// at a specified position in the string
		misc::generic_array<char> str7a("ABCDHIJ");
		misc::generic_array<char> str7b("abcdefgh");
		misc::generic_array<char>::iterator str7a_Iter = (str7a.begin() + 4);
		str7a.insert(str7a_Iter, str7b.begin() + 4, str7b.end() - 1);

		CPPUNIT_ASSERT(str7a == "ABCDefgHIJ");

		// The eigth member function inserts a number of
		// characters at a specified position in the string
		misc::generic_array<char> str8("ABCDHIJ");
		misc::generic_array<char>::iterator str8_Iter = (str8.begin() + 4);
		str8.insert(str8_Iter, 3, 'e');

		CPPUNIT_ASSERT(str8 == "ABCDeeeHIJ");
	}


	misc::cout << "\n\n\tinsert-------------------------------------------------";
	insert<std::basic_string<char, std::char_traits<char>, std::allocator<char> > >            ("\n\tstd::vector<char>                       ");
	insert<std::basic_string<char, std::char_traits<char>, misc::allocator<char> > >           ("\n\tstd::vector<char,A>                     ");
	insert<misc::generic_array<char, misc::allocator<char> > >                                 ("\n\tgeneric_array<char>                     ");
	insert<misc::generic_array<char, std::allocator<char> > >                                  ("\n\tgeneric_array<char,std::A>              ");
	insert<misc::generic_array<char, misc::allocator<char>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >("\n\tgeneric_array<char,POD>                 ");
	insert<misc::generic_array<char, misc::allocator<char>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >("\n\tgeneric_array<char,POD>                 ");
	
	
}

void test_generic_array::erase()
{
	{
		/* template type */
		typedef misc::generic_array<char> string;

		string str("This is an example phrase.");
		string::iterator it;

		// erase used in the same order as described above:
		str.erase(10, 8);
		CPPUNIT_ASSERT(strcmp(str.c_str(), "This is an phrase.") == 0);

		it = str.begin() + 9;
		str.erase(it);
		CPPUNIT_ASSERT(strcmp(str.c_str(), "This is a phrase.") == 0);

		str.erase(str.begin() + 5, str.end() - 7);
		CPPUNIT_ASSERT(strcmp(str.c_str(), "This phrase.") == 0);
	}

	{
		using namespace misc::generic_array_ops;


		/* MSDN sample */
		// The 1st member function using a range demarcated
		// by iterators
		misc::generic_array<char> str1("Hello world");
		misc::generic_array<char>::iterator str1_Iter;

		str1_Iter = str1.erase(str1.begin() + 3, str1.end() - 1);

		CPPUNIT_ASSERT(*str1_Iter == 'd');
		CPPUNIT_ASSERT(str1 == "Held");

		// The 2nd member function erasing a char pointed to
		// by an iterator
		misc::generic_array<char> str2("Hello World");
		misc::generic_array<char>::iterator str2_Iter;

		str2_Iter = str2.erase(str2.begin() + 5);
		CPPUNIT_ASSERT(*str2_Iter == 'W');
		CPPUNIT_ASSERT(str2 == "HelloWorld");

		// The 3rd member function erasing a number of chars
		// after a char
		misc::generic_array<char> str3("Hello computer"), str3m;
		misc::generic_array<char>::iterator str3_Iter;

		str3m = str3.erase(6, 8);

		CPPUNIT_ASSERT(str3m == "Hello ");
	}

	misc::cout << "\n\n\terase-------------------------------------------------";
	erase<misc::generic_array<non_pod_v0, misc::allocator<non_pod_v0> > >                                 ("\n\tgeneric_array<non_pod_v0>               ");
	erase<misc::generic_array<non_pod_v0, std::allocator<non_pod_v0> > >                                  ("\n\tgeneric_array<non_pod_v0,std::A>        ");
	erase<misc::generic_array<non_pod_v0, misc::allocator<non_pod_v0>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >("\n\tgeneric_array<non_pod_v0,POD>           ");
	erase<misc::generic_array<non_pod_v0, misc::allocator<non_pod_v0>,
															misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> > ("\n\tgeneric_array<non_pod_v0,IT_DBG>        ");
	
	
}


void test_generic_array::replace()
{
	{
		/* using template type */
		typedef misc::generic_array<char> string;

		string base = "this is a test string.";
		string str2 = "n example";
		string str3 = "sample phrase";
		string str4 = "useful.";

		// function versions used in the same order as described above:

		string str = base;
		CPPUNIT_ASSERT(strcmp(str.c_str(), "this is a test string.") == 0);

		str.replace(9, 5, str2);
		CPPUNIT_ASSERT(strcmp(str.c_str(), "this is an example string.") == 0);

		str.replace(19, 6, str3, 7, 6);
		CPPUNIT_ASSERT(strcmp(str.c_str(), "this is an example phrase.") == 0);

		str.replace(8, 10, "just all", 6);
		CPPUNIT_ASSERT(strcmp(str.c_str(), "this is just a phrase.") == 0);

		str.replace(8, 6, "a short");
		CPPUNIT_ASSERT(strcmp(str.c_str(), "this is a short phrase.") == 0);

		str.replace(22, 1, 3, '!');
		CPPUNIT_ASSERT(strcmp(str.c_str(), "this is a short phrase!!!") == 0);

		// Using iterators:
		string::iterator it = str.begin();
		str.replace(it, str.end() - 3, str3);
		CPPUNIT_ASSERT(strcmp(str.c_str(), "sample phrase!!!") == 0);

		str.replace(it, it + 6, "replace it", 7);
		CPPUNIT_ASSERT(strcmp(str.c_str(), "replace phrase!!!") == 0);

		it += 8;
		str.replace(it, it + 6, "is cool");
		CPPUNIT_ASSERT(strcmp(str.c_str(), "replace is cool!!!") == 0);

		str.replace(it + 4, str.end() - 4, 4, 'o');
		CPPUNIT_ASSERT(strcmp(str.c_str(), "replace is cooool!!!") == 0);

		it += 3;
		str.replace(it, str.end(), str4.begin(), str4.end());

		CPPUNIT_ASSERT(strcmp(str.c_str(), "replace is useful.") == 0);
	}

	{
		using namespace misc::generic_array_ops;

		/* using MSDN sample */

		// The first two member functions replace
		// part of the operand string with
		// characters from a parameter string or C-string
		misc::generic_array<char> result1a, result1b;
		misc::generic_array<char> s1o("AAAAAAAA");
		misc::generic_array<char> s1p("BBB");
		const char* cs1p = "CCC";

		CPPUNIT_ASSERT(strcmp(s1o.c_str(), "AAAAAAAA") == 0);

		CPPUNIT_ASSERT(strcmp(s1p.c_str(), "BBB") == 0);

		CPPUNIT_ASSERT(strcmp(cs1p, "CCC") == 0);

		result1a = s1o.replace(1, 3, s1p);

		CPPUNIT_ASSERT(strcmp(result1a.c_str(), "ABBBAAAA") == 0);

		result1b = s1o.replace(5, 3, cs1p);

		CPPUNIT_ASSERT(strcmp(result1b.c_str(), "ABBBACCC") == 0);

		// The third & fourth member function replace
		// part of the operand string with characters
		// form part of a parameter string or C-string
		misc::generic_array<char> result2a, result2b;
		misc::generic_array<char> s2o("AAAAAAAA");
		misc::generic_array<char> s2p("BBB");
		const char* cs2p = "CCC";
		CPPUNIT_ASSERT(strcmp(s2o.c_str(), "AAAAAAAA") == 0);

		CPPUNIT_ASSERT(strcmp(s2p.c_str(), "BBB") == 0);

		CPPUNIT_ASSERT(strcmp(cs2p, "CCC") == 0);

		result2a = s2o.replace(1, 3, s2p, 1, 2);

		CPPUNIT_ASSERT(strcmp(result2a.c_str(), "ABBAAAA") == 0);

		result2b = s2o.replace(4, 3, cs2p, 1);

		CPPUNIT_ASSERT(strcmp(result2b.c_str(), "ABBAC") == 0);

		// The fifth member function replaces
		// part of the operand string with characters
		misc::generic_array<char> result3a;
		misc::generic_array<char> s3o("AAAAAAAA");
		char ch3p = 'C';

		CPPUNIT_ASSERT(strcmp(s3o.c_str(), "AAAAAAAA") == 0);

		CPPUNIT_ASSERT(ch3p == 'C');

		result3a = s3o.replace(1, 3, 4, ch3p);

		CPPUNIT_ASSERT(strcmp(result3a.c_str(), "ACCCCAAAA") == 0);

		// The sixth & seventh member functions replace
		// part of the operand string, delineated with iterators,
		// with a parameter string or C-string
		misc::generic_array<char> s4o("AAAAAAAA");
		misc::generic_array<char> s4p("BBB");
		const char* cs4p = "CCC";

		CPPUNIT_ASSERT(strcmp(s4o.c_str(), "AAAAAAAA") == 0);
		CPPUNIT_ASSERT(strcmp(s4p.c_str(), "BBB") == 0);
		CPPUNIT_ASSERT(strcmp(cs4p, "CCC") == 0);

		misc::generic_array<char>::iterator IterF0, IterL0;
		IterF0 = s4o.begin();
		IterL0 = s4o.begin() + 3;
		misc::generic_array<char> result4a, result4b;
		result4a = s4o.replace(IterF0, IterL0, s4p);

		CPPUNIT_ASSERT(strcmp(result4a.c_str(), "BBBAAAAA") == 0);

		result4b = s4o.replace(IterF0, IterL0, cs4p);

		CPPUNIT_ASSERT(strcmp(result4b.c_str(), "CCCAAAAA") == 0);

		// The 8th member function replaces
		// part of the operand string delineated with iterators
		// with a number of characters from a parameter C-string
		misc::generic_array<char> s5o("AAAAAAAF");
		const char* cs5p = "CCCBB";

		CPPUNIT_ASSERT(strcmp(s5o.c_str(), "AAAAAAAF") == 0);
		CPPUNIT_ASSERT(s5o == "AAAAAAAF");
		CPPUNIT_ASSERT(strcmp(cs5p, "CCCBB") == 0);

		misc::generic_array<char>::iterator IterF1, IterL1;
		IterF1 = s5o.begin();
		IterL1 = s5o.begin() + 4;
		misc::generic_array<char> result5a;
		result5a = s5o.replace(IterF1, IterL1, cs5p, 4);

		CPPUNIT_ASSERT(strcmp(result5a.c_str(), "CCCBAAAF") == 0);
		CPPUNIT_ASSERT(result5a == "CCCBAAAF");

		// The 9th member function replaces
		// part of the operand string delineated with iterators
		// with specified characters
		misc::generic_array<char> s6o("AAAAAAAG");
		char ch6p = 'q';

		misc::generic_array<char>::iterator IterF2, IterL2;
		IterF2 = s6o.begin();
		IterL2 = s6o.begin() + 3;
		misc::generic_array<char> result6a;
		result6a = s6o.replace(IterF2, IterL2, 4, ch6p);

		CPPUNIT_ASSERT(strcmp(result6a.c_str(), "qqqqAAAAG") == 0);

		// The 10th member function replaces
		// part of the operand string delineated with iterators
		// with part of a parameter string delineated with iterators
		misc::generic_array<char> s7o("OOOOOOO");
		misc::generic_array<char> s7p("PPPP");

		CPPUNIT_ASSERT(strcmp(s7o.c_str(), "OOOOOOO") == 0);
		CPPUNIT_ASSERT(strcmp(s7p.c_str(), "PPPP") == 0);

		misc::generic_array<char>::iterator IterF3, IterL3, IterF4, IterL4;
		IterF3 = s7o.begin() + 1;
		IterL3 = s7o.begin() + 3;
		IterF4 = s7p.begin();
		IterL4 = s7p.begin() + 2;
		misc::generic_array<char> result7a;
		result7a = s7o.replace(IterF3, IterL3, IterF4, IterL4);

		CPPUNIT_ASSERT(strcmp(result7a.c_str(), "OPPOOOO") == 0);
	}


	misc::cout << "\n\n\treplace------------------------------------------------";
	replace<std::basic_string<char, std::char_traits<char>, std::allocator<char> > >            ("\n\tstd::basic_string<char>                 ");
	replace<std::basic_string<char, std::char_traits<char>, misc::allocator<char> > >           ("\n\tstd::basic_string<char,A>               ");
	replace<misc::generic_array<char, misc::allocator<char> > >                                 ("\n\tgeneric_array<char>                     ");
	replace<misc::generic_array<char, std::allocator<char> > >                                  ("\n\tgeneric_array<char,std::A>              ");
	replace<misc::generic_array<char, misc::allocator<char>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >("\n\tgeneric_array<char,POD>                 ");
	replace<misc::generic_array<char, misc::allocator<char>,
												misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >   ("\n\tgeneric_array<char,IT_DBG>              ");	
}


void test_generic_array::swap()
{
	{
		/* template type sample */
		typedef misc::generic_array<char> string;

		string buyer("money");
		string seller("goods");

		seller.swap(buyer);

		CPPUNIT_ASSERT(strcmp(seller.c_str(), "money") == 0);

		CPPUNIT_ASSERT(strcmp(buyer.c_str(), "goods") == 0);
	}

	{
		misc::generic_array<char> s1;
		misc::generic_array<char> s2("");
		s1.swap(s2);
		misc::generic_array<char> s3;
		s3 = s1;
		CPPUNIT_ASSERT(s1.empty());
		CPPUNIT_ASSERT(s2.empty());
		CPPUNIT_ASSERT(s3.empty());
	}


	misc::cout << "\n\n\tswap---------------------------------------------------";
	swap<std::vector<non_pod_v0, std::allocator<non_pod_v0> > >                                          ("\n\tstd::vector<non_pod_v0>                 ");
	swap<std::vector<non_pod_v0, misc::allocator<non_pod_v0> > >                                         ("\n\tstd::vector<non_pod_v0,A>               ");
	swap<misc::generic_array<non_pod_v0, misc::allocator<non_pod_v0> > >                                 ("\n\tgeneric_array<non_pod_v0>               ");
	swap<misc::generic_array<non_pod_v0, std::allocator<non_pod_v0> > >                                  ("\n\tgeneric_array<non_pod_v0,std::A>        ");
	swap<misc::generic_array<non_pod_v0, misc::allocator<non_pod_v0>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >("\n\tgeneric_array<non_pod_v0,POD>           ");
	swap<misc::generic_array<non_pod_v0, misc::allocator<non_pod_v0>,
															misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >("\n\tgeneric_array<non_pod_v0,IT_DBG>        ");	
}


//String operations

void test_generic_array::c_str()
{
	{
		/* template type */
		typedef misc::generic_array<char> string;

		const char* table[] = {"Please", "split", "this", "phrase", "into", "tokens"};

		char * cstr, *p;

		string str("Please split this phrase into tokens");

		cstr = new char [str.size() + 1];
		strcpy(cstr, str.c_str());

		// cstr now contains a c-string copy of str
		int i = 0;

		p = strtok(cstr, " ");
		while(p != NULL)
		{
			CPPUNIT_ASSERT(strcmp(p, table[i++]) == 0);
			p = strtok(NULL, " ");
		}

		delete[] cstr;
	}

	{
		/* MSDN sample */
		misc::generic_array<char> str1("Hello world");

		// Converting a string to an array7 of characters
		const char *ptr1 = 0;
		ptr1 = str1.data();

		CPPUNIT_ASSERT(strlen(ptr1) == 11);

		// Converting a string to a C-style string
		const char *c_str1 = str1.c_str();

		CPPUNIT_ASSERT(strlen(c_str1) == 11);
	}
	misc::cout << "\n\n\tc_str--------------------------------------------------";
}


void test_generic_array::data()
{
	{
		/* template type */
		typedef misc::generic_array<char> string;

		int length;

		string str = "Test string";
		const char* cstr = "Test string";

		CPPUNIT_ASSERT(str.length() == strlen(cstr));

		length = str.length();

		CPPUNIT_ASSERT(memcmp(cstr, str.data(), length) == 0);
	}

	{
		/* MSDN sample */
		misc::generic_array<char> str1("Hello world");

		// Converting a string to an array7 of characters
		const char *ptr1 = 0;
		ptr1 = str1.data();

		CPPUNIT_ASSERT(strcmp(ptr1, "Hello world") == 0);

		// Converting a string to a C-style string
		const char *c_str1 = str1.c_str();

		/* same address for returned char array7 */
		CPPUNIT_ASSERT(c_str1 == ptr1);

		CPPUNIT_ASSERT(strcmp(c_str1, "Hello world") == 0);
	}

	misc::cout << "\n\n\tdata---------------------------------------------------";
}


void test_generic_array::get_allocator()
{
	//not implemented
	misc::cout << "\n\n\tget_allocator------------------------------------------";
}


void test_generic_array::copy()
{
	typedef misc::generic_array<char> string;

	size_t length;
	char buffer[20];
	string str("Test string...");
	length = str.copy(buffer, 6, 5);
	buffer[length] = '\0';

	CPPUNIT_ASSERT(strcmp(buffer, "string") == 0);


	misc::cout << "\n\n\tcopy---------------------------------------------------";
	copy<std::basic_string<char, std::char_traits<char>, std::allocator<char> > >            ("\n\tstd::basic_string<char>                 ");
	copy<std::basic_string<char, std::char_traits<char>, misc::allocator<char> > >           ("\n\tstd::basic_string<char,A>               ");
	copy<misc::generic_array<char, misc::allocator<char> > >                                 ("\n\tgeneric_array<char>                     ");
	copy<misc::generic_array<char, std::allocator<char> > >                                  ("\n\tgeneric_array<char,std::A>              ");
	copy<misc::generic_array<char, misc::allocator<char>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >("\n\tgeneric_array<char,POD>                 ");
	copy<misc::generic_array<char, misc::allocator<char>,
												misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >("\n\tgeneric_array<char,IT_DBG>              ");
}


void test_generic_array::find()
{
	{
		/* template type */
		typedef misc::generic_array<char> string;

		string str("There are two needles in this haystack with needles.");
		string str2("needle");
		size_t found;

		found = str.find(str2);
		CPPUNIT_ASSERT(found != string::npos && found == 14);

		found = str.find("needles are small", found + 1, 6);
		CPPUNIT_ASSERT(found != string::npos && found == 44);

		found = str.find("haystack");
		CPPUNIT_ASSERT(found != string::npos && found == 30);

		found = str.find('.');
		CPPUNIT_ASSERT(found != string::npos && found == 51);

		// let's replace the first needle:
		str.replace(str.find(str2), str2.length(), "preposition");

		CPPUNIT_ASSERT(strcmp(str.c_str(), "There are two prepositions in this haystack with needles.") == 0);
	}

	{
		typedef misc::generic_array<char> string;

		//off correction not allowed, no throw
		string s0("1234567890");
		size_t pos0 = s0.find('5', 0);
		CPPUNIT_ASSERT(pos0 == 4);

		pos0 = s0.find('5', (size_t) - 1);
		CPPUNIT_ASSERT(pos0 == string::npos);

		pos0 = s0.find("89", 5);
		CPPUNIT_ASSERT(pos0 == 7);
		pos0 = s0.find("89", 9);
		CPPUNIT_ASSERT(pos0 == string::npos);
		bool throw1 = false;
		try{
			pos0 = s0.find("89", (size_t) - 1);
		}catch(const misc::exception&){ throw1 = true; };
		CPPUNIT_ASSERT( throw1 );

		//count not corrected, throws
		string s1("1234567890");
		size_t pos1 = s1.find("89", 5, 0); //MS returns pos 5 (pretty non-sense)!!
		CPPUNIT_ASSERT( pos1 == string::npos );

		pos1 = s1.find("89", 5, (size_t) - 1);
		CPPUNIT_ASSERT( pos1 == string::npos );

		size_t pos3 = s1.find("89", 7, 2);
		CPPUNIT_ASSERT(pos3 == 7);
	}

	misc::cout << "\n\n\tfind---------------------------------------------------";
	find<std::basic_string<unsigned char, std::char_traits<unsigned char>, std::allocator<unsigned char> > >   ("\n\tstd::basic_string<char>                 ");
	find<std::basic_string<unsigned char, std::char_traits<unsigned char>, misc::allocator<unsigned char> > >  ("\n\tstd::basic_string<char,A>               ");
	find<misc::generic_array<unsigned char, misc::allocator<unsigned char> > >                                 ("\n\tgeneric_array<char>                     ");
	find<misc::generic_array<unsigned char, std::allocator<unsigned char> > >                                  ("\n\tgeneric_array<char,std::A>              ");
	find<misc::generic_array<unsigned char, misc::allocator<unsigned char>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >("\n\tgeneric_array<char,POD>                 ");
	find<misc::generic_array<unsigned char, misc::allocator<unsigned char>,
																misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >  ("\n\tgeneric_array<char,IT_DBG>              ");
}


void test_generic_array::rfind()
{
	{
		/* template type */
		typedef misc::generic_array<char> string;

		string str("The sixth sick sheik's sixth sheep's sick.");
		string key("sixth");
		size_t found;

		found = str.rfind(key);

		CPPUNIT_ASSERT(found == 23);

		str.replace(found, key.length(), "seventh");

		CPPUNIT_ASSERT(strcmp(str.c_str(), "The sixth sick sheik's seventh sheep's sick.") == 0);
	}

	{
		typedef misc::generic_array<char> string;

		string s0("1234567890");
		size_t pos0 = s0.rfind('8');
		CPPUNIT_ASSERT(pos0 == 7);
		pos0 = s0.rfind('8', 7);
		CPPUNIT_ASSERT(pos0 == 7);
		pos0 = s0.rfind('8', 6);
		CPPUNIT_ASSERT(pos0 == string::npos);

		//off correction allowed, no throw
		pos0 = s0.rfind("89", (size_t) - 1);
		CPPUNIT_ASSERT(pos0 == 7);

		pos0 = s0.rfind('8', 5);
		CPPUNIT_ASSERT(pos0 == string::npos);

		pos0 = s0.rfind("89", 5);
		CPPUNIT_ASSERT(pos0 == string::npos);

		pos0 = s0.rfind("89", (size_t) - 1, 0);
		CPPUNIT_ASSERT(pos0 == string::npos);

		pos0 = s0.rfind("89", (size_t) - 1, (size_t) - 1);
		CPPUNIT_ASSERT(pos0 == string::npos);

		string s3("89");
		size_t pos3 = s0.rfind(s3, 0);
		CPPUNIT_ASSERT(pos3 == string::npos);

		pos3 = s0.rfind(s3, (size_t) - 1);
		CPPUNIT_ASSERT(pos3 == 7);
	}

	misc::cout << "\n\n\trfind--------------------------------------------------";
	rfind<std::basic_string<unsigned char, std::char_traits<unsigned char>, std::allocator<unsigned char> > >   ("\n\tstd::basic_string<char>                 ");
	rfind<std::basic_string<unsigned char, std::char_traits<unsigned char>, misc::allocator<unsigned char> > >  ("\n\tstd::basic_string<char,A>               ");
	rfind<misc::generic_array<unsigned char, misc::allocator<unsigned char> > >                                 ("\n\tgeneric_array<char>                     ");
	rfind<misc::generic_array<unsigned char, std::allocator<unsigned char> > >                                  ("\n\tgeneric_array<char,std::A>              ");
	rfind<misc::generic_array<unsigned char, misc::allocator<unsigned char>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >("\n\tgeneric_array<char,POD>                 ");
	rfind<misc::generic_array<unsigned char, misc::allocator<unsigned char>,
																misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >   ("\n\tgeneric_array<char,IT_DBG>              ");	
}


void test_generic_array::find_first_of()
{
	{
		/* template type */
		typedef misc::generic_array<char> string;

		string str("Replace the vowels in this sentence by asterisks.");
		size_t found;

		found = str.find_first_of("aeiou");
		while (found != string::npos) {
			str[found] = '*';
			found = str.find_first_of("aeiou", found + 1);
		}

		CPPUNIT_ASSERT(strcmp(str.c_str(), "R*pl*c* th* v*w*ls *n th*s s*nt*nc* by *st*r*sks.") == 0);
	}

	{
		typedef misc::generic_array<char> string;

		//off correction not allowed, no throws
		string s0("1234567890");
		size_t pos0 = s0.find_first_of('8');
		CPPUNIT_ASSERT(pos0 == 7);

		pos0 = s0.find_first_of('8', 8);
		CPPUNIT_ASSERT(pos0 == string::npos);

		pos0 = s0.find_first_of('8', (size_t) - 1);
		CPPUNIT_ASSERT(pos0 == string::npos);

		pos0 = s0.find_first_of("89");
		CPPUNIT_ASSERT(pos0 == 7);

		pos0 = s0.find_first_of("89", 7);
		CPPUNIT_ASSERT(pos0 == 7);

		pos0 = s0.find_first_of("89", 8);
		CPPUNIT_ASSERT(pos0 == 8);

		pos0 = s0.find_first_of("89", 9);
		CPPUNIT_ASSERT(pos0 == string::npos);

		bool throw1 = false;
		try
		{
			pos0 = s0.find_first_of("89", (size_t) - 1);
		}
		catch(const misc::exception&)
		{
			throw1 = true;
		}

		CPPUNIT_ASSERT( throw1 );

		//count throws
		pos0 = s0.find_first_of("89", 9, 0);
		CPPUNIT_ASSERT(pos0 == string::npos);

		pos0 = s0.find_first_of("89", 9, 3);
		CPPUNIT_ASSERT( pos0 == string::npos );

		pos0 = s0.find_first_of("89", 9, (size_t) - 1);
		CPPUNIT_ASSERT( pos0 == string::npos );
	}


	misc::cout << "\n\n\tfind_first_of------------------------------------------";
	find_first_of<std::basic_string<unsigned char, std::char_traits<unsigned char>, std::allocator<unsigned char> > >   ("\n\tstd::basic_string<char>                 ");
	find_first_of<std::basic_string<unsigned char, std::char_traits<unsigned char>, misc::allocator<unsigned char> > >  ("\n\tstd::basic_string<char,A>               ");
	find_first_of<misc::generic_array<unsigned char, misc::allocator<unsigned char> > >                                 ("\n\tgeneric_array<char>                     ");
	find_first_of<misc::generic_array<unsigned char, std::allocator<unsigned char> > >                                  ("\n\tgeneric_array<char,std::A>              ");
	find_first_of<misc::generic_array<unsigned char, misc::allocator<unsigned char>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >("\n\tgeneric_array<char,POD>                 ");
	find_first_of<misc::generic_array<unsigned char, misc::allocator<unsigned char>, 
																		misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >   ("\n\tgeneric_array<char,IT_DBG>              ");
}


void test_generic_array::find_last_of()
{
	{
		/* template type */
		typedef misc::generic_array<char> string;

		string str1("/usr/bin/man");
		string str2("c:\\windows\\winhelp.exe");

		size_t found;
		found = str1.find_last_of("/\\");
		string str3 = str1.substr(0, found);

		CPPUNIT_ASSERT(strcmp(str3.c_str(), "/usr/bin") == 0); //folder

		string str4 = str1.substr(found + 1);

		CPPUNIT_ASSERT(strcmp(str4.c_str(), "man") == 0); //file

		found = str2.find_last_of("/\\");

		string str5 = str2.substr(0, found);

		CPPUNIT_ASSERT(strcmp(str5.c_str(), "c:\\windows") == 0);

		string str6 = str2.substr(found + 1);

		CPPUNIT_ASSERT(strcmp(str6.c_str(), "winhelp.exe") == 0);
	}

	{
		typedef misc::generic_array<char> string;

		//off correction allowed, no throw
		string s0("1234567890");
		size_t pos0 = s0.find_last_of('8');
		CPPUNIT_ASSERT(pos0 == 7);

		pos0 = s0.find_last_of('8', 9);
		CPPUNIT_ASSERT(pos0 == 7);

		pos0 = s0.find_last_of('8', 7);
		CPPUNIT_ASSERT(pos0 == 7);

		pos0 = s0.find_last_of('8', 6);
		CPPUNIT_ASSERT(pos0 == string::npos);

		pos0 = s0.find_last_of('8', (size_t) - 1);
		CPPUNIT_ASSERT(pos0 == 7);

		//count throws
		pos0 = s0.find_last_of("89");
		CPPUNIT_ASSERT(pos0 == 8);

		pos0 = s0.find_last_of("89", 8);
		CPPUNIT_ASSERT(pos0 == 8);

		pos0 = s0.find_last_of("89", 7);
		CPPUNIT_ASSERT(pos0 == 7);

		pos0 = s0.find_last_of("89", 6);
		CPPUNIT_ASSERT(pos0 == string::npos);

		pos0 = s0.find_last_of("89", (size_t) - 1);
		CPPUNIT_ASSERT(pos0 == 8);

		pos0 = s0.find_last_of("89", 9, 0);
		CPPUNIT_ASSERT(pos0 == string::npos);

		pos0 = s0.find_last_of("89", 9, 2);
		CPPUNIT_ASSERT(pos0 == 8);

		pos0 = s0.find_last_of("89", 9, 3);
		CPPUNIT_ASSERT(pos0 == 8);

		pos0 = s0.find_last_of("89", 9, (size_t) - 1);
		CPPUNIT_ASSERT(pos0 == 8);

		string s1("89");
		pos0 = s0.find_last_of(s1);
		CPPUNIT_ASSERT(pos0 == 8);

		pos0 = s0.find_last_of(s1, 8);
		CPPUNIT_ASSERT(pos0 == 8);

		pos0 = s0.find_last_of(s1, 7);
		CPPUNIT_ASSERT(pos0 == 7);

		pos0 = s0.find_last_of(s1, 6);
		CPPUNIT_ASSERT(pos0 == string::npos);
	}


	misc::cout << "\n\n\tfind_last_of------------------------------------------";
	find_last_of<std::basic_string<unsigned char, std::char_traits<unsigned char>, std::allocator<unsigned char> > >   ("\n\tstd::basic_string<char>                 ");
	find_last_of<std::basic_string<unsigned char, std::char_traits<unsigned char>, misc::allocator<unsigned char> > >  ("\n\tstd::basic_string<char,A>               ");
	find_last_of<misc::generic_array<unsigned char, misc::allocator<unsigned char> > >                                 ("\n\tgeneric_array<char>                     ");
	find_last_of<misc::generic_array<unsigned char, std::allocator<unsigned char> > >                                  ("\n\tgeneric_array<char,std::A>              ");
	find_last_of<misc::generic_array<unsigned char, misc::allocator<unsigned char>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >("\n\tgeneric_array<char,POD>                 ");
	find_last_of<misc::generic_array<unsigned char, misc::allocator<unsigned char>,
																		misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >  ("\n\tgeneric_array<char,IT_DBG>              ");	
}


void test_generic_array::find_first_not_of()
{
	{
		/* template type */
		typedef misc::generic_array<char> string;

		string str("look for non-alphabetic characters...");
		size_t found;

		found = str.find_first_not_of("abcdefghijklmnopqrstuvwxyz ");

		CPPUNIT_ASSERT(found == 12);
		CPPUNIT_ASSERT(str[found] == '-');
	}

	{
		typedef misc::generic_array<char> string;

		//off correction not allowed, no throw
		string s0("8888888088");
		size_t pos0 = s0.find_first_not_of('8');
		CPPUNIT_ASSERT(pos0 == 7);

		pos0 = s0.find_first_not_of('8', 6);
		CPPUNIT_ASSERT(pos0 == 7);

		pos0 = s0.find_first_not_of('8', 7);
		CPPUNIT_ASSERT(pos0 == 7);

		pos0 = s0.find_first_not_of('8', 8);
		CPPUNIT_ASSERT(pos0 == string::npos);

		bool throw1 = false;
		try
		{
			pos0 = s0.find_first_not_of('8', (size_t) - 1);
		}
		catch(const misc::exception&)
		{
			throw1 = true;
		}

		CPPUNIT_ASSERT( throw1 );

		s0 = "1234567890";
		pos0 = s0.find_first_not_of("098764321");
		CPPUNIT_ASSERT(pos0 == 4);

		pos0 = s0.find_first_not_of("098764321", 4);
		CPPUNIT_ASSERT(pos0 == 4);

		pos0 = s0.find_first_not_of("098764321", 5);
		CPPUNIT_ASSERT(pos0 == string::npos);


		throw1 = false;
		try
		{
			pos0 = s0.find_first_not_of("098764321", (size_t) - 1);
		}
		catch(const misc::exception&)
		{
			throw1 = true;
		}
		CPPUNIT_ASSERT( throw1 );

		pos0 = s0.find_first_not_of("098764321", 0, 0);
		CPPUNIT_ASSERT(pos0 == string::npos);

		pos0 = s0.find_first_not_of("098764321", 0, 9);
		CPPUNIT_ASSERT(pos0 == 4);

		pos0 = s0.find_first_not_of("098764321", 0, (size_t) - 1);
		CPPUNIT_ASSERT( pos0 == 4 );

		string s1("098764321");
		pos0 = s0.find_first_not_of(s1);
		CPPUNIT_ASSERT(pos0 == 4);

		pos0 = s0.find_first_not_of(s1, 4);
		CPPUNIT_ASSERT(pos0 == 4);

		pos0 = s0.find_first_not_of(s1, 5);
		CPPUNIT_ASSERT(pos0 == string::npos);

		pos0 = s0.find_first_not_of(s1, 6);
		CPPUNIT_ASSERT(pos0 == string::npos);

		throw1 = false;
		try
		{
			pos0 = s0.find_first_not_of(s1, (size_t) - 1);
		}
		catch(const misc::exception&)
		{
			throw1 = true;
		}
		CPPUNIT_ASSERT( throw1 );
	}

	misc::cout << "\n\n\tfind_first_not_of------------------------------------------";
	find_first_not_of<std::basic_string<unsigned char, std::char_traits<unsigned char>, std::allocator<unsigned char> > >   ("\n\tstd::basic_string<char>                 ");
	find_first_not_of<std::basic_string<unsigned char, std::char_traits<unsigned char>, misc::allocator<unsigned char> > >  ("\n\tstd::basic_string<char,A>               ");
	find_first_not_of<misc::generic_array<unsigned char, misc::allocator<unsigned char> > >                                 ("\n\tgeneric_array<char>                     ");
	find_first_not_of<misc::generic_array<unsigned char, std::allocator<unsigned char> > >                                  ("\n\tgeneric_array<char,std::A>              ");
	find_first_not_of<misc::generic_array<unsigned char, misc::allocator<unsigned char>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >("\n\tgeneric_array<char,POD>                 ");
	find_first_not_of<misc::generic_array<unsigned char, misc::allocator<unsigned char>,
																			misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >   ("\n\tgeneric_array<char,IT_DBG>              ");	
}


void test_generic_array::find_last_not_of()
{
	{
		/* template type */
		typedef misc::generic_array<char> string;

		string str("erase trailing white-spaces   \n");
		string whitespaces(" \t\f\v\n\r");
		size_t found;

		found = str.find_last_not_of(whitespaces);

		if(found != string::npos)
		{
			str.erase(found + 1);
		}
		else
		{
			str.clear();
		}

		CPPUNIT_ASSERT(strcmp(str.c_str(), "erase trailing white-spaces") == 0);
	}

	{
		typedef misc::generic_array<char> string;

		//off correction allowed, no throw
		string s0("8888808088");
		size_t pos0 = s0.find_last_not_of('8');
		CPPUNIT_ASSERT(pos0 == 7);

		pos0 = s0.find_last_not_of('8', 8);
		CPPUNIT_ASSERT(pos0 == 7);

		pos0 = s0.find_last_not_of('8', 7);
		CPPUNIT_ASSERT(pos0 == 7);

		pos0 = s0.find_last_not_of('8', 6);
		CPPUNIT_ASSERT(pos0 == 5);

		pos0 = s0.find_last_not_of('8', 4);
		CPPUNIT_ASSERT(pos0 == string::npos);

		pos0 = s0.find_last_not_of('8', (size_t) - 1);
		CPPUNIT_ASSERT(pos0 == 7);

		s0 = "1234567590";
		pos0 = s0.find_last_not_of("098764321");
		CPPUNIT_ASSERT(pos0 == 7);

		pos0 = s0.find_last_not_of("098764321", 3);
		CPPUNIT_ASSERT(pos0 == string::npos);

		pos0 = s0.find_last_not_of("098764321", 4);
		CPPUNIT_ASSERT(pos0 == 4);

		pos0 = s0.find_last_not_of("098764321", 7);
		CPPUNIT_ASSERT(pos0 == 7);

		pos0 = s0.find_last_not_of("098764321", (size_t) - 1);
		CPPUNIT_ASSERT(pos0 == 7);

		pos0 = s0.find_last_not_of("098764321", (size_t) - 1, 0);
		CPPUNIT_ASSERT(pos0 == string::npos);

		pos0 = s0.find_last_not_of("098764321", (size_t) - 1, 9);
		CPPUNIT_ASSERT(pos0 == 7);

		pos0 = s0.find_last_not_of("098764321", (size_t) - 1, (size_t) - 1);
		CPPUNIT_ASSERT(pos0 == 7);

		string s1("098764321");
		pos0 = s0.find_last_not_of(s1);
		CPPUNIT_ASSERT(pos0 == 7);

		pos0 = s0.find_last_not_of(s1, 4);
		CPPUNIT_ASSERT(pos0 == 4);

		pos0 = s0.find_last_not_of(s1, 7);
		CPPUNIT_ASSERT(pos0 == 7);

		pos0 = s0.find_last_not_of(s1, 0);
		CPPUNIT_ASSERT(pos0 == string::npos);

		pos0 = s0.find_last_not_of(s1, (size_t) - 1);
		CPPUNIT_ASSERT(pos0 == 7);
	}

	misc::cout << "\n\n\tfind_last_not_of------------------------------------------";
	find_last_not_of<std::basic_string<unsigned char, std::char_traits<unsigned char>, std::allocator<unsigned char> > >   ("\n\tstd::basic_string<char>                 ");
	find_last_not_of<std::basic_string<unsigned char, std::char_traits<unsigned char>, misc::allocator<unsigned char> > >  ("\n\tstd::basic_string<char,A>               ");
	find_last_not_of<misc::generic_array<unsigned char, misc::allocator<unsigned char> > >                                 ("\n\tgeneric_array<char>                     ");
	find_last_not_of<misc::generic_array<unsigned char, std::allocator<unsigned char> > >                                  ("\n\tgeneric_array<char,std::A>              ");
	find_last_not_of<misc::generic_array<unsigned char, misc::allocator<unsigned char>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >("\n\tgeneric_array<char,POD>                 ");
	find_last_not_of<misc::generic_array<unsigned char, misc::allocator<unsigned char>,
																			misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >  ("\n\tgeneric_array<char,ITD_DBG>             ");
}


void test_generic_array::substr()
{
	typedef misc::generic_array<char> string;

	string str = "We think in generalities, but we live in details.";
	// quoting Alfred N. Whitehead
	string str2, str3;
	size_t pos;

	str2 = str.substr(12, 12); // "generalities"
	pos = str.find("live"); // position of "live" in str
	str3 = str.substr(pos); // get from "live" to the end

	CPPUNIT_ASSERT(strcmp(str3.c_str(), "live in details.") == 0);


	misc::cout << "\n\n\tsubstr------------------------------------------------";
	substr<std::basic_string<unsigned char, std::char_traits<unsigned char>, std::allocator<unsigned char> > >   ("\n\tstd::basic_string<char>                 ");
	substr<std::basic_string<unsigned char, std::char_traits<unsigned char>, misc::allocator<unsigned char> > >  ("\n\tstd::basic_string<char,A>               ");
	substr<misc::generic_array<unsigned char, misc::allocator<unsigned char> > >                                 ("\n\tgeneric_array<char>                     ");
	substr<misc::generic_array<unsigned char, std::allocator<unsigned char> > >                                  ("\n\tgeneric_array<char,std::A>              ");
	substr<misc::generic_array<unsigned char, misc::allocator<unsigned char>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >("\n\tgeneric_array<char,POD>                 ");
	substr<misc::generic_array<unsigned char, misc::allocator<unsigned char>, 
																	misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >("\n\tgeneric_array<char,IT_DBG>              ");
}


void test_generic_array::compare()
{
	typedef misc::generic_array<char> string;

	string str1("green apple");
	string str2("red apple");

	CPPUNIT_ASSERT(str1.compare(str2) != 0);

	CPPUNIT_ASSERT(str1.compare(6, 5, "apple") == 0);

	CPPUNIT_ASSERT(str2.compare(str2.size() - 5, 5, "apple") == 0);

	CPPUNIT_ASSERT(str1.compare(6, 5, str2, 4, 5) == 0);


	misc::cout << "\n\n\tcompare------------------------------------------------";
	compare<std::basic_string<unsigned char, std::char_traits<unsigned char>, std::allocator<unsigned char> > >   ("\n\tstd::basic_string<char>                 ");
	compare<std::basic_string<unsigned char, std::char_traits<unsigned char>, misc::allocator<unsigned char> > >  ("\n\tstd::basic_string<char,A>               ");	
	compare<misc::generic_array<unsigned char, misc::allocator<unsigned char> > >                                 ("\n\tgeneric_array<char>                     ");
	compare<misc::generic_array<unsigned char, std::allocator<unsigned char> > >                                  ("\n\tgeneric_array<char, std::A>             ");
	compare<misc::generic_array<unsigned char, misc::allocator<unsigned char>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >("\n\tgeneric_array<char,POD>                 ");
	compare<misc::generic_array<unsigned char, misc::allocator<unsigned char>,
																	misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> > ("\n\tgeneric_array<char,IT_DBG>              ");
}


//////////////////////////////////////////////////////////////////////////

template<typename Container>
void test_generic_array::ctor(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::allocator_type Calloc;


	// initialization data
	Cval chtab[255]; /*NULL terminated*/ chtab[254]=0;
	for(size_t i = 0; i < 254; ++i)
	{
		chtab[i] = Cval(i+1); // we iterate also with float,double,etc
	}

	// measure only the time for constructors
	misc::vector<Container*> store;

	//  TEST
	{
		time_printer tp(msg, m_print_time);


		for(size_t i=0; i < m_container_size; ++i)
		{
			//generic_array(const Allocator& alloc = Allocator())
			Container* array0 = new Container(Calloc());
			store.push_back(array0);

			/* create non-empty container
			   generic_array(const value_type* ptr, size_type count,
			   const Allocator& alloc = Allocator())
			*/
			Container* array2 = new Container(chtab, 255, Calloc());
			//obs: 2nd params std::string::npos -> exception: "string too long"
			store.push_back(array2);

			//generic_array(const generic_array<value_type>& x)
			const Container& array3 = *array2;
			const Container* array4 = new Container(array3);//copy-ctor
			store.push_back(const_cast<Container*>(array4));

			/*
			  generic_array(const generic_array& str, size_type off, size_type count = npos,
			  const Allocator& alloc = Allocator())
			*/
			Container* array5 = new Container(*array4, 2, Container::npos, Calloc());
			// null terminated otherwise will fault
			if(*(array5->rbegin()) != 0)
				array5->push_back(0);
			store.push_back(array5);


			/*
			  generic_array(const value_type* ptr, size_type count,
			  const Allocator& alloc = Allocator())
			*/
			Container* array6 = new Container(array5->c_str(), array5->size(), Calloc());
			// null terminated otherwise will fault
			if(*(array6->rbegin()) != 0)
				array6->push_back(0);
			store.push_back(array6);


			//generic_array(const value_type* ptr, const Allocator& alloc = Allocator())
			Container* array7 = new Container(array6->c_str(), Calloc());
			store.push_back(array7);


			//generic_array(size_type n, value_type c, const Allocator& alloc = Allocator())
			Container* array8 = new Container(m_container_size, static_cast<Cval>(1.e-3f), Calloc());
			store.push_back(array8);


			/*
			  template<class InputIterator>
			  inline generic_array(InputIterator begin, InputIterator end,
			  const Allocator& alloc = Allocator())
			*/
			Container* array9 = new Container(array4->begin(), array4->end(), Calloc());
			store.push_back(array9);

		}
	}


	// calling ~generic_array()
	for(size_t i=0; i < store.size(); ++i)
	{
		delete store[i];
	}
}


template<typename Container>
void test_generic_array::dtor(const char* msg)
{
	// preserving the code from ctor<Container>(...)
	// and measuring the destructor
	typedef typename Container::value_type Cval;
	typedef typename Container::allocator_type Calloc;


	// initialization data
	Cval chtab[255]; /*NULL terminated*/ chtab[254]=0;
	for(size_t i = 0; i < 254; ++i)
	{
		chtab[i] = Cval(i+1); // we iterate also with float,double,etc
	}


	misc::vector<Container*> store;

	//  Create containers, will take the time of ~generic_array()
	for(size_t i=0; i < m_container_size; ++i)
	{
		//generic_array(const Allocator& alloc = Allocator())
		Container* array0 = new Container(Calloc());
		store.push_back(array0);

		/* create non-empty container
		   generic_array(const value_type* ptr, size_type count,
		   const Allocator& alloc = Allocator())
		*/
		Container* array2 = new Container(chtab, 255, Calloc());
		//obs: 2nd params std::string::npos -> exception: "string too long"
		store.push_back(array2);

		//generic_array(const generic_array<value_type>& x)
		const Container& array3 = *array2;
		const Container* array4 = new Container(array3);//copy-ctor
		store.push_back(const_cast<Container*>(array4));

		/*
		  generic_array(const generic_array& str, size_type off, size_type count = npos,
		  const Allocator& alloc = Allocator())
		*/
		Container* array5 = new Container(*array4, 2, Container::npos, Calloc());
		// null terminated otherwise will fault
		if(*(array5->rbegin()) != 0)
			array5->push_back(0);
		store.push_back(array5);


		/*
		  generic_array(const value_type* ptr, size_type count,
		  const Allocator& alloc = Allocator())
		*/
		Container* array6 = new Container(array5->c_str(), array5->size(), Calloc());
		// null terminated otherwise will fault
		if(*(array6->rbegin()) != 0)
			array6->push_back(0);
		store.push_back(array6);


		//generic_array(const value_type* ptr, const Allocator& alloc = Allocator())
		Container* array7 = new Container(array6->c_str(), Calloc());
		store.push_back(array7);


		//generic_array(size_type n, value_type c, const Allocator& alloc = Allocator())
		Container* array8 = new Container(m_container_size, static_cast<Cval>(1.e-3f), Calloc());
		store.push_back(array8);


		/*
		  template<class InputIterator>
		  inline generic_array(InputIterator begin, InputIterator end,
		  const Allocator& alloc = Allocator())
		*/
		Container* array9 = new Container(array4->begin(), array4->end(), Calloc());
		store.push_back(array9);

	}

	//  TEST
	{
		time_printer tp(msg, m_print_time);

		// calling ~generic_array()
		for(size_t i=0; i < store.size(); ++i)
		{
			delete store[i];
		}
	}
}

template<typename Container>
void test_generic_array::assignament_op(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::allocator_type Calloc;


	// Initialize test data
	Cval chtab[255]; /* NULL terminated */ chtab[254]=0;
	for(size_t i=0; i < 254; ++i)
	{
		chtab[i] = Cval(i+1);
	}

	misc::vector<Container*> store;
	// string(size_type n, value_type c, const Allocator& alloc = Allocator())
	Container* array0 = new Container(m_container_size, 'A', Calloc());
	store.push_back(array0);



	//  TEST
	{
		time_printer tp(msg, m_print_time);

		for(size_t i=0; i < m_container_size; ++i)
		{
			Container* array1 = new Container(Calloc());
			store.push_back(array1);

			//inline generic_array& operator=(const generic_array<value_type>& str)
			*array1 = *array0;

			//inline generic_array<value_type>& operator=(const value_type* ptr)
			Container* array2 = new Container();
			store.push_back(array2);
			*array2 = chtab;

			//inline generic_array<value_type>& operator=(value_type ch)
			*array2 = Cval('c');

			//inline generic_array& operator=(const generic_array<value_type>& str)
			Container* array4 = new Container(500, math::min_value(Cval(0)));
			store.push_back(array4);

			Container* array5 = new Container();
			store.push_back(array5);
			*array5 = *array4;
		}  // for
	}

	for(size_t j=0; j < store.size(); ++j)
	{
		delete store[j];
	}
}


template<typename Container>
void test_generic_array::begin(const char* msg)
{
	typedef typename Container::iterator It;

	typedef misc::list<It> chitlist;
	chitlist itlist0;
	Container array0;
	array0.resize(m_container_size);

	//  TEST
	{
		time_printer tp(msg, m_print_time);

		for(size_t i=0; i<m_container_size; ++i)
		{
			itlist0.push_back(array0.begin());
		}
	}
}


template<typename Container>
void test_generic_array::end(const char* msg)
{
	typedef typename Container::iterator It;

	typedef misc::list<It> chitlist;
	chitlist itlist0;
	Container array0;
	array0.resize(m_container_size);

	//  TEST
	{
		time_printer tp(msg, m_print_time);

		for(size_t i=0; i<m_container_size; ++i)
		{
			itlist0.push_back(array0.end());
		}
	}
}

template<typename Container>
void test_generic_array::rbegin(const char* msg)
{
	typedef typename Container::reverse_iterator RIt;

	typedef misc::list<RIt> chitlist;
	chitlist itlist0;
	Container array0;
	array0.resize(m_container_size);

	//  TEST
	{
		time_printer tp(msg, m_print_time);

		for(size_t i=0; i<m_container_size; ++i)
		{
			itlist0.push_back(array0.rbegin());
		}
	}
}


template<typename Container>
void test_generic_array::rend(const char* msg)
{
	typedef typename Container::reverse_iterator RIt;

	typedef misc::list<RIt> chitlist;
	chitlist itlist0;
	Container array0;
	array0.resize(m_container_size);

	//  TEST
	{
		time_printer tp(msg, m_print_time);

		for(size_t i=0; i<m_container_size; ++i)
		{
			itlist0.push_back(array0.rend());
		}
	}
}


template<typename Container>
void  test_generic_array::resize(const char* msg)
{
	{
		time_printer tp(msg, m_print_time);

		for(size_t i=0; i < m_container_size; ++i)
		{
			size_t objsz = i%2 == 0 ? m_container_size : 0;
			Container array0(objsz, nonpod_v0(-100));
			array0.resize(i%2 == 0 ? 0 : m_container_size);
		}
	}
}


template<typename Container>
void test_generic_array::reserve(const char* msg)
{
  	//  TEST
	{
		time_printer tp(msg, m_print_time);

		for(size_t i=0; i < m_container_size; ++i)
		{
			Container array0(0, -2); // tricky one
			array0.reserve(m_container_size);
		}
	}
}


template<typename Container>
void test_generic_array::clear(const char* msg)
{
	//  TEST
	{
		time_printer tp(msg, m_print_time);

		for(size_t i=0; i < m_container_size; ++i)
		{
			Container array0(m_container_size, -2);
			array0.clear();
		}
	}
}

template<typename Container>
void test_generic_array::operator_access_element(const char* msg)
{
	//  TEST
	{
		time_printer tp(msg, m_print_time);

		for(size_t i=0; i < m_container_size; ++i)
		{
			Container array0(m_container_size, -2);
			nonpod_v0& obj = array0[0]; // validate address
			for(size_t i=0; i < m_container_size; ++i)
			{
				obj = array0[i];
			}
		}
	}
}


template<typename Container>
void test_generic_array::at(const char* msg)
{
	//  TEST
	{
		time_printer tp(msg, m_print_time);

		for(size_t i=0; i < m_container_size; ++i)
		{
			Container array0(m_container_size, -2);
			nonpod_v0& obj = array0[0]; // validate address
			for(size_t i=0; i < m_container_size/10; ++i)
			{
				obj = array0.at(i);
			}
		}
	}
}

template<typename Container>
void test_generic_array::operator_plus_equal(const char* msg)
{
	typedef typename Container::value_type Cval;

	//  TEST
	{
		time_printer tp(msg, m_print_time);

		//both 3 operators are STD::STRING related:
		//(1) inline container& operator+=(const container& str)
		//(2) inline container& operator+=(const value_type* ptr)
		//(3) inline container& operator+=(value_type ch)


		//(1)
		Container array0;
		Container array_plus0(2, 'c');
		for(size_t i = 0; i < m_container_size; ++i)
		{
			array0 += array_plus0;
		}
		//(2)
		Container array2;
		const Cval* array_plus2 = "12345abcdeABCDE";
		for(size_t i=0; i < m_container_size; ++i)
		{
			array2 += array_plus2;
		}
		//(3)
		Container array3;
		Cval array_plus3('1');
		for(size_t i=0; i < m_container_size; ++i)
		{
			array3 += array_plus3;
		}
	}
}

template<typename Container>
void test_generic_array::append(const char* msg)
{
	typedef typename Container::value_type Cval;

	Cval chtab[255]; /* NULL terminated */ chtab[254]=0;
	for(int c=0; c < 254; ++c)
	{
		chtab[c] = Cval(c+1);
	}


	//  TEST
	{
		/*
		  append is STD::STRING ONLY specific
		  container& append(const container& str);
		  container& append(const container& str, size_type p2, size_type n2);
		  container& append(const value_type* ptr, size_type n2);
		  container& append(const value_type* ptr);
		  container& append(size_type n, value_type value);
		  template<typename InputIterator>
		  container& append(InputIterator first, InputIterator last);
		*/
		time_printer tp(msg, m_print_time);


		Container array0(chtab);
		Container array1;

		for(size_t i=0; i < m_container_size; ++i)
		{
			array1.append(array0);
			array1.append(array0, array0.size()/2, (size_t)-1);
			array1.append(array0.c_str(), array0.size());
			array1.append(array0.data());
			array1.append(100, 'c');
			array1.append(chtab+0, chtab+200);
		}
	}
}


template<typename Container>
void test_generic_array::push_back(const char* msg)
{
	typedef typename Container::value_type Cval;

	//  TEST
	{
		time_printer tp(msg, m_print_time);

		Container array;
		for(size_t i=0; i < m_container_size; ++i)
		{
			array.push_back( Cval(i) );
		}
	}
}


template<typename Container>
void test_generic_array::assign(const char* msg)
{
	Container charr0(m_container_size, 'x');

	//  TEST
	{
		/*
		// string's specific
		container& assign(const container& str);
		container& assign(const container& str, size_type p2, size_type n2);
		container& assign(const value_type* ptr, size_type n2);
		container& assign(const value_type* ptr);
		// vector's specific
		container& assign(size_type count, const value_type& val);
		template <typename InputIterator>
		inline container& assign(InputIterator first, InputIterator last);
		*/

		time_printer tp(msg, m_print_time);


		for(size_t i = 0; i < m_container_size; ++i)
		{
			Container charr2;
			charr2.assign(charr0);
			charr2.assign(charr0, charr0.size()/2, charr0.size()/2);
			charr2.assign(charr0.c_str(), charr0.size()/2);
			charr2.assign(charr0.data());
		}

		
		// time of: container& assign(size_type count, const value_type& val);
		// time of: container& assign(InputIterator first, InputIterator last);
		for(size_t i=0; i < m_container_size; ++i)
		{
			Container nparr0;
			Container nparr2;
			nparr0.assign(m_container_size, 'x');
			nparr2.assign(nparr0.begin(), nparr0.end());
		}
	}
}


template<typename Container>
void test_generic_array::insert(const char* msg)
{
	// initialization data
	Container charr0(m_container_size, 'x');

	//  TEST
	{
		/*
		// -- string --
		container& insert(size_type p1, const container& str)
		container& insert(size_type p1, const container& str, size_type p2, size_type n2)

		container& insert(size_type p1, const value_type* ptr, size_type n2)
		container& insert(size_type p1, const value_type* ptr)
		container& insert(size_type p1, size_type n2, value_type ch)

		// -- vector + string --
		iterator insert(iterator position, const value_type& x)
		void insert(iterator position, size_type n, const value_type& x)
		<typename InputIterator>
		inline void insert(iterator position, InputIterator first, InputIterator last)
		// -- vector + string --
		*/

		time_printer tp(msg, m_print_time);


		for(size_t i=0; i < m_container_size; ++i)
		{
			Container charr2(20, 'y');
			charr2.insert(1, charr0);
			charr2.insert(1, charr0, 0, charr0.size());
			charr2.insert(1, charr0.c_str(), charr0.size());
			charr2.insert(1, charr0.c_str());
			charr2.insert(1, charr0.size(), charr0.data()[0]);
			charr2.insert(++charr2.begin(), charr0.data()[0]);
			charr2.insert(++charr2.begin(), charr0.size(), charr0.data()[0]);
			charr2.insert(++charr2.begin(), charr0.begin(), charr0.end());
		}

		//non_pod_v0
		for(size_t i=0; i < m_container_size; ++i)
		{
			Container varr0(10, 'z');
			varr0.insert(++varr0.begin(), 'z');
			varr0.insert(++varr0.begin(), 5, 'z');
			varr0.insert(++varr0.begin(), varr0.begin()+2, varr0.end());
		}
	}
}


template<typename Container>
void test_generic_array::erase(const char* msg)
{

	//   TEST
	{
		/*
		// -- string --
		container& erase(size_type p1 = 0, size_type n1 = npos)
		// -- vector & string --
		iterator erase(iterator position)
		iterator erase(iterator first, iterator last)
		*/

		time_printer tp(msg, m_print_time);


		// initialization data
		non_pod_v0 np;
		np.val=-100;
		np.fval=-1e3;
		np.ucval = 100;
		np.f = non_pod_f_v0;

		for(size_t i=0; i < m_container_size; ++i)
		{
			Container charr0(10, np);
			Container charr2(10, np);
			Container charr3(10, np);
			charr0.erase(1, 1);
			charr2.erase(charr2.begin());
			charr3.erase(charr3.begin(), ++charr3.begin());
		}

		for(size_t i=0; i < m_container_size; ++i)
		{
			Container varr0(10, np);
			Container varr2(10, np);
			varr0.erase(varr0.begin()+1);
			varr2.erase(varr2.begin(), ++varr2.begin());
		}
	}
}

template<typename Container>
void test_generic_array::replace(const char* msg)
{
	typedef typename Container::iterator It;

	const size_t SIZE = 100;
	//  TEST
	{
		time_printer tp(msg, m_print_time);

		/*
		// string specifics
		container& replace(size_type p1, size_type n1, const container& str)
		container& replace(size_type p1, size_type n1, const container& str, size_type p2, size_type n2)
		container& replace(size_type p1, size_type n1, const value_type* ptr, size_type n2)
		container& replace(size_type p1, size_type n1, const value_type* ptr)
		container& replace(size_type p1, size_type n1, size_type n2, value_type ch)
		container& replace(iterator first, iterator last, const container& str)
		container& replace(iterator first, iterator last, const value_type* ptr, size_type n2)
		container& replace(iterator first, iterator last, const value_type* ptr)
		container& replace(iterator first, iterator last, size_type n2, value_type ch)
		template<typename InputIterator>
		inline container& replace(iterator first, iterator last, InputIterator first2, InputIterator last2)
		*/

		for(size_t i=0; i < m_container_size; ++i)
		{
			Container charr0(SIZE, 'x');
			Container charr2(SIZE, 'y');
			Container charr3(SIZE, 'z');
			Container charr4(SIZE, 'a');
			Container charr5(SIZE, 'b');

			charr0.replace(SIZE/2, 1, charr2);
			charr3.replace(SIZE/2, 1, charr0, 0, charr0.size());
			charr4.replace(SIZE/2, 1, charr3.data(), charr3.size());
			charr5.replace(SIZE/2, 1, charr4.c_str());
			charr5.replace(charr5.size() - SIZE/2, 1, SIZE, 'd');

			It beg = charr5.begin();
			for(size_t j = 0; j < charr5.size()/2; ++j)
				++beg;
			It end = beg; ++end;
			charr5.replace(beg, end, charr4);

			// search the middle
			beg = charr5.begin();
			for(size_t j = 0; j < charr5.size()/2; ++j)
				++beg;
			end = beg; ++end;
			charr5.replace(beg, end, charr4.c_str(), charr4.size());

			// search the middle
			beg = charr5.begin();
			for(size_t j = 0; j < charr5.size()/2; ++j)
				++beg;
			end = beg; ++end;
			charr5.replace(beg, end, charr4.c_str());

			// search the middle
			beg = charr5.begin();
			for(size_t j = 0; j < charr5.size()/2; ++j)
				++beg;
			end = beg; ++end;
			charr5.replace(beg, end, SIZE, 'y');

			// search the middle
			beg = charr5.begin();
			for(size_t j = 0; j < charr5.size()/2; ++j)
				++beg;
			end = beg; ++end;
			charr5.replace(beg, end, charr4.c_str(), charr4.c_str()+charr4.size()-1);
		}
	}
}


template<typename Container>
void test_generic_array::swap(const char* msg)
{
	non_pod_v0 np1, np2;
	np1.fval = -1e-2f;
	np1.ucval= 'c';
	np1.val = 100;
	np1.f = non_pod_f_v0;
	np2 = np1;


	Container nparr0(m_container_size, np1);
	Container nparr2(m_container_size, np2);

	//  TEST
	{
		time_printer tp(msg, m_print_time);

		for(size_t i=0; i < m_container_size; ++i)
		{
			nparr0.swap(nparr2);
		}
	}
}


template<typename Container>
void test_generic_array::copy(const char* msg)
{
	typedef typename Container::value_type Cval;

	Container charr0(m_container_size, 'x');
	Cval charr2[m_container_size];

	//  TEST
	{
		// string specific
		// copies this into ptr, from p1, n1 elements;
		// size_type copy(value_type* ptr, size_type n1, size_type p1 = 0) const

		time_printer tp(msg, m_print_time);

		for(size_t i=0; i < m_container_size; ++i)
		{
			charr0.copy(charr2, charr0.size(), 0);
		}
	}
}


template<typename Container>
void test_generic_array::find(const char* msg)
{
	const size_t STRSIZE = 1000;
	const size_t CYCLE = 300;
	unsigned char chtab[STRSIZE];

	// Generate random numbers in the half-closed interval
	// [range_min, range_max). In other words,
	// range_min <= random number < range_max
	int range_min = 33;
	int range_max = 127;
	for ( int i = 0; i < (int)STRSIZE; i++ )
	{
		double u = (double) ::rand() / ((double)RAND_MAX + 1.) * (range_max - range_min) + range_min;
		chtab[i] = (unsigned char) u;
	}
	chtab[STRSIZE-1] = 0; // null terminated

	Container charr0;
	for(size_t s=0; s < CYCLE; ++s)
	{
		charr0.append(chtab);
	} // for

	Container charr1(chtab);


	//  TEST
	{
		/*
		  std::basic_string specifics
		  size_t find (const string& str, size_t pos = 0) const;
		  size_t find (const char* s, size_t pos = 0) const;
		  size_t find (const char* s, size_t pos, size_t n) const;
		  size_t find (char c, size_t pos = 0) const;
		*/

		time_printer tp(msg, m_print_time);

		for(size_t i=0; i < CYCLE; ++i)
		{
			size_t pos1 = charr0.find(charr1);
			while(pos1 != Container::npos)
			{
				pos1 = charr0.find(charr1.c_str(), pos1+1);
				if(pos1 == Container::npos) break;
				pos1 = charr0.find(charr1.c_str(), pos1+1, STRSIZE-1);
				if(pos1 == Container::npos) break;
				pos1 = charr0.find(charr1[0], pos1+1);
			}
		}
	}
}


template<typename Container>
void test_generic_array::rfind(const char* msg)
{
	/*
	  size_t rfind (const string& str, size_t pos = npos) const;
	  size_t rfind (const char* s, size_t pos = npos) const;
	  size_t rfind (const char* s, size_t pos, size_t n) const;
	  size_t rfind (char c, size_t pos = npos) const;
	*/

	const size_t STRSIZE = 1000;
	const size_t CYCLE = 300;
	unsigned char chtab[STRSIZE];

	// Generate random numbers in the half-closed interval
	// [range_min, range_max). In other words,
	// range_min <= random number < range_max
	int range_min = 33;
	int range_max = 127;
	for ( int i = 0; i < (int)STRSIZE; i++ )
	{
		double tmp = (double)rand() / ((double)RAND_MAX + 1.) * (range_max - range_min) + range_min;
		chtab[i] = (unsigned char) tmp;
	}
	chtab[STRSIZE-1] = 0; // null terminated

	Container charr0;
	for(size_t s=0; s < CYCLE; ++s)
	{
		charr0.append(chtab);
	} // for

	Container charr1(chtab);


	//  TEST
	{
		time_printer tp(msg, m_print_time);

		for(size_t i=0; i < CYCLE; ++i)
		{
			size_t pos1 = charr0.rfind(charr1);
			while(pos1 != 0)
			{
				pos1 = charr0.rfind(charr1.c_str(), pos1-1);
				if(pos1 == 0) break;
				pos1 = charr0.rfind(charr1.c_str(), pos1-1, STRSIZE-1);
				if(pos1 == 0) break;
				pos1 = charr0.rfind(charr1[0], pos1-1);
			}
		}
	}
}


template<typename Container>
void test_generic_array::find_first_of(const char* msg)
{
	/*
	  size_t find_first_of (const string& str, size_t pos = 0) const;
	  size_t find_first_of (const char* s, size_t pos = 0) const;
	  size_t find_first_of (const char* s, size_t pos, size_t n) const;
	  size_t find_first_of (char c, size_t pos = 0) const;
	*/

	const size_t STRSIZE = 500;
	const size_t CYCLE = 800;
	unsigned char chtab[STRSIZE];

	// Generate random numbers in the half-closed interval
	// [range_min, range_max). In other words,
	// range_min <= random number < range_max
	int range_min = 33;
	int range_max = 127;
	for ( int i = 0; i < (int)STRSIZE; i++ )
	{
		double tmp = (double) ::rand() / ((double)RAND_MAX + 1.) * (range_max - range_min) + range_min;
		chtab[i] = (unsigned char) tmp;
	}
	chtab[STRSIZE-1] = 0; // null terminated

	Container charr0;
	for(size_t s=0; s < CYCLE; ++s)
	{
		charr0.append(chtab);
	} // for

	Container charr1(chtab);


	//  TEST
	{
		time_printer tp(msg, m_print_time);


		for(size_t i=0; i < CYCLE; ++i)
		{
			size_t pos1 = charr0.find_first_of(charr1);
			while(pos1 != Container::npos)
			{
				pos1 = charr0.find_first_of(charr1.c_str(), pos1+1);
				if(pos1 == Container::npos) break;
				pos1 = charr0.find_first_of(charr1.c_str(), pos1+1, STRSIZE-1);
				if(pos1 == Container::npos) break;
				pos1 = charr0.find_first_of(charr1[0], pos1+1);
			}
		} // for
	}
}


template<typename Container>
void test_generic_array::find_last_of(const char* msg)
{
	/*
	  size_t find_last_of (const string& str, size_t pos = npos) const;
	  size_t find_last_of (const char* s, size_t pos = npos) const;
	  size_t find_last_of (const char* s, size_t pos, size_t n) const;
	  size_t find_last_of (char c, size_t pos = npos) const;
	*/
	const size_t STRSIZE = 300;
	const size_t CYCLE = 50;
	unsigned char chtab[STRSIZE];

	// Generate random numbers in the half-closed interval
	// [range_min, range_max). In other words,
	// range_min <= random number < range_max
	int range_min = 33;
	int range_max = 127;
	for ( int i = 0; i < (int)STRSIZE; i++ )
	{
		double tmp = (double) ::rand() / ((double)RAND_MAX + 1.) * (range_max - range_min) + range_min;
		chtab[i] = (unsigned char) tmp;
	}
	chtab[STRSIZE-1] = 0; // null terminated

	Container charr0;
	for(size_t s=0; s < CYCLE; ++s)
	{
		charr0.append(chtab);
	} // for

	Container charr1(chtab);

	//  TEST
	{
		time_printer tp(msg, m_print_time);

		for(size_t i=0; i < CYCLE; ++i)
		{
			size_t pos1 = charr0.find_last_of(charr1);
			while(pos1 != 0)
			{
				pos1 = charr0.find_last_of(charr1.c_str(), pos1-1);
				if(pos1 == 0) break;
				pos1 = charr0.find_last_of(charr1.c_str(), pos1-1, STRSIZE-1);
				if(pos1 == 0) break;
				pos1 = charr0.find_last_of(charr1[0], pos1-1);
			}
		}
	}
}


template<typename Container>
void test_generic_array::find_first_not_of(const char* msg)
{

	/*
	  size_t find_first_not_of (const string& str, size_t pos = 0) const;
	  size_t find_first_not_of (const char* s, size_t pos = 0) const;
	  size_t find_first_not_of (const char* s, size_t pos, size_t n) const;
	  size_t find_first_not_of (char c, size_t pos = 0) const;
	*/


	const size_t STRSIZE = 200;
	const size_t CYCLE = 200;
	unsigned char chtab[STRSIZE];

	// Generate random numbers in the half-closed interval
	// [range_min, range_max). In other words,
	// range_min <= random number < range_max
	int range_min = 33;
	int range_max = 127;
	for ( int i = 0; i < (int)STRSIZE; i++ )
	{
		double tmp = (double) ::rand() / ((double)RAND_MAX + 1.) * (range_max - range_min) + range_min;
		chtab[i] = (unsigned char) tmp;
	}
	chtab[STRSIZE-1] = 0; // null terminated
	unsigned char chtab2[]={" \t\f\v\n\r"};
	Container charr0;
	for(size_t s=0; s < CYCLE; ++s)
	{
		charr0.append(chtab);
	} // for

	Container charr1(chtab2);

	//  TEST
	{
		time_printer tp(msg, m_print_time);


		for(size_t i=0; i < CYCLE; ++i)
		{
			size_t pos1 = charr0.find_first_not_of(charr1);
			while(pos1 != Container::npos)
			{
				pos1 = charr0.find_first_not_of(charr1.c_str(), pos1+1);
				if(pos1 == Container::npos) break;
				pos1 = charr0.find_first_not_of(charr1.c_str(), pos1+1, STRSIZE-1);
				if(pos1 == Container::npos) break;
				pos1 = charr0.find_first_not_of(charr1[0], pos1+1);
			}
		}
	}
}

template<typename Container>
void test_generic_array::find_last_not_of(const char* msg)
{
	/*
	  size_t find_last_not_of (const string& str, size_t pos = npos) const;
	  size_t find_last_not_of (const char* s, size_t pos = npos) const;
	  size_t find_last_not_of (const char* s, size_t pos, size_t n) const;
	  size_t find_last_not_of (char c, size_t pos = npos) const;
	*/


	const size_t STRSIZE = 50;
	const size_t CYCLE = 100;
	unsigned char chtab[STRSIZE];

	// Generate random numbers in the half-closed interval
	// [range_min, range_max). In other words,
	// range_min <= random number < range_max
	int range_min = 33;
	int range_max = 127;
	for ( int i = 0; i < (int)STRSIZE; i++ )
	{
		double tmp = (double) ::rand() / ((double)RAND_MAX + 1.) * (range_max - range_min) + range_min;
		chtab[i] = (unsigned char) tmp;
	}
	chtab[STRSIZE-1] = 0; // null terminated
	unsigned char chtab2[]={" \t\f\v\n\r"};

	Container charr0;
	for(size_t s=0; s < CYCLE; ++s)
	{
		charr0.append(chtab);
	} // for

	Container charr1(chtab2);

	//  TEST
	{
		time_printer tp(msg, m_print_time);

		for(size_t i=0; i < CYCLE; ++i)
		{
			size_t pos1 = charr0.find_last_not_of(charr1);
			while(pos1 != 0)
			{
				pos1 = charr0.find_last_not_of(charr1.c_str(), pos1-1);
				if(pos1 == 0) break;
				pos1 = charr0.find_last_not_of(charr1.c_str(), pos1-1, STRSIZE-1);
				if(pos1 == 0) break;
				pos1 = charr0.find_last_not_of(charr1[0], pos1-1);
			}
		}
	}
}


template<typename Container>
void test_generic_array::substr(const char* msg)
{
	/*
	  string substr (size_t pos = 0, size_t len = npos) const;
	*/
	const size_t STRSIZE = 500;
	const size_t CYCLE = 500;
	unsigned char chtab[STRSIZE];

	// Generate random numbers in the half-closed interval
	// [range_min, range_max). In other words,
	// range_min <= random number < range_max
	int range_min = 33;
	int range_max = 127;
	for ( int i = 0; i < (int)STRSIZE; i++ )
	{
		double tmp = (double) ::rand() / ((double)RAND_MAX + 1.) * (range_max - range_min) + range_min;
		chtab[i] = (unsigned char) tmp;
	}
	chtab[STRSIZE-1] = 0; // null terminated

	Container charr0;
	for(size_t i = 0; i < CYCLE; ++i)
	{
		charr0.append(chtab);
	} // for


	//  TEST
	{
		time_printer tp(msg, m_print_time);

		for(size_t i = 0; i < CYCLE; ++i)
		{
			size_t pos1 = i * STRSIZE;
			charr0.substr(pos1, STRSIZE);
		}
	}
}


template<typename Container>
void test_generic_array::compare(const char* msg)
{
	/*
	  int compare (const string& str) const;
	  int compare (size_t pos, size_t len, const string& str) const;
	  int compare (size_t pos, size_t len, const string& str, size_t subpos, size_t sublen) const;
	  int compare (const char* s) const;
	  int compare (size_t pos, size_t len, const char* s) const;
	  int compare (size_t pos, size_t len, const char* s, size_t n) const;
	*/


	const size_t STRSIZE = 500;
	const size_t CYCLE = 2500;
	unsigned char chtab[STRSIZE];

	// Generate random numbers in the half-closed interval
	// [range_min, range_max). In other words,
	// range_min <= random number < range_max
	int range_min = 33;
	int range_max = 127;
	for ( int i = 0; i < (int)STRSIZE; i++ )
	{
		double tmp = (double) ::rand() / ((double)RAND_MAX + 1.) * (range_max - range_min) + range_min;
		chtab[i] = (unsigned char) tmp;
	}
	chtab[STRSIZE-1] = 0; /* NULL terminated */

	Container charr0(chtab), charr1(chtab);
	size_t pos1 = 0;
	size_t len1 = charr1.size();
	size_t subpos1 = 0;
	size_t sublen1 = charr1.size();
	size_t len2 = charr1.size();

	//  TEST
	{
		time_printer tp(msg, m_print_time);

		for(size_t i=0; i < CYCLE; ++i)
		{
			int eq1 = charr0.compare(charr1);                               (void)eq1;
			int eq2 = charr0.compare(pos1, len1, charr1);                   (void)eq2;
			int eq3 = charr0.compare(pos1, len1, charr1, subpos1, sublen1); (void)eq3;
			int eq4 = charr0.compare(charr1.c_str());                       (void)eq4;
			int eq5 = charr0.compare(pos1, len1, charr1.c_str());           (void)eq5;
			int eq6 = charr0.compare(pos1, len1, charr1.c_str(), len2);     (void)eq6;
		} // for
	}
}

//////////////////////////////////////////////////////////////////////////

/*
Copyright (C) 2012 Mihai Vasilian
*/

//this
#include "test_generic_string.hpp"


//c/c++
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <string>
#include <iomanip>

//CppUnit
#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TestResult.h>


//libraries
#include "exception.hpp"
#include "autoptr.hpp"
#include "string.hpp"
#include "stdio.hpp"
#include "generic_string.hpp"
#include "stream.hpp"
#include "misctest_util.hpp"


/*
  TODO: implement test for slt::basic_string<class type, or struct type>
  TODO: self assignment, different version (overlapping regions, etc) 
  TODO: const_iterator(iterator), const_reverse_iterator(reverse_iterator)
  TODO: test all exceptions conditions
  TODO: str.size() is 10; str[3] = '\0' -> what does it mean ?
  TODO: should I return str[str.size()] as '\0' ?  what if some change it to smth else ?
  TODO: generic_string cannot hold POD types; a new podvector is required for this; strlen(ptr) on POD ?
 */



//###########################BEGIN TEST CLASS ####################################

void test_generic_string::setUp() 
{
}

void test_generic_string::tearDown() 
{
}

//##########################BEGIN TEST SUITE######################################
//test begin
//Member functions

void test_generic_string::ctor() 
{
	stl::cout << "\n\n\t*******************************************************";
	stl::cout <<   "\n\t* TESTING HEADER: generic_string.hpp                  *";
	stl::cout <<   "\n\t*******************************************************";

	stl::cout << "\n\n\tctor---------------------------------------------------";
	ctor<slt::basic_string<char> >                                             ("\n\tgeneric_string            ");
	ctor<std::basic_string<char> >                                                ("\n\tstd::basic_string         ");
//	compile error for _alloc1 == _alloc2
//  ctor<std::basic_string<char, std::char_traits<char>, misc::allocator<char> > >("\n\tstd::basic_string<char,A> ");
	ctor<std::basic_string<char, std::char_traits<char>, std::allocator<char> > >("\n\tstd::basic_string<char,A> ");

}

void test_generic_string::assignament_op() 
{
	stl::cout << "\n\n\tassignament_op-----------------------------------------";
	assignament_op<slt::basic_string<char> >                                             ("\n\tgeneric_string            ");
	assignament_op<std::basic_string<char> >                                                ("\n\tstd::basic_string         ");
	assignament_op<std::basic_string<char, std::char_traits<char>, misc::allocator<char> > >("\n\tstd::basic_string<char,A> ");
}

//Iterators

void test_generic_string::begin() 
{
	stl::cout << "\n\n\tbegin--------------------------------------------------";
	begin<slt::basic_string<char> >                                             ("\n\tgeneric_string            ");
	begin<std::basic_string<char> >                                                ("\n\tstd::basic_string         ");
	begin<std::basic_string<char, std::char_traits<char>, misc::allocator<char> > >("\n\tstd::basic_string<char,A> ");
}

void test_generic_string::end() 
{
	stl::cout << "\n\n\tend----------------------------------------------------";
	end<slt::basic_string<char> >                                             ("\n\tgeneric_string            ");
	end<std::basic_string<char> >                                                ("\n\tstd::basic_string         ");
	end<std::basic_string<char, std::char_traits<char>, misc::allocator<char> > >("\n\tstd::basic_string<char,A> ");
}

void test_generic_string::rbegin() 
{
	stl::cout << "\n\n\trbegin-------------------------------------------------";
	rbegin<slt::basic_string<char> >                                             ("\n\tgeneric_string            ");
	rbegin<std::basic_string<char> >                                                ("\n\tstd::basic_string         ");
	rbegin<std::basic_string<char, std::char_traits<char>, misc::allocator<char> > >("\n\tstd::basic_string<char,A> ");
}

void test_generic_string::rend() 
{
	stl::cout << "\n\n\trend---------------------------------------------------";
	rend<slt::basic_string<char> >                                             ("\n\tgeneric_string            ");
	rend<std::basic_string<char> >                                                ("\n\tstd::basic_string         ");
	rend<std::basic_string<char, std::char_traits<char>, misc::allocator<char> > >("\n\tstd::basic_string<char,A> ");
}

//Capacity

void test_generic_string::size() 
{
	stl::cout << "\n\n\tsize---------------------------------------------------";
	size<slt::basic_string<char> >                                             ("\n\tgeneric_string            ");
	size<std::basic_string<char> >                                                ("\n\tstd::basic_string         ");
	size<std::basic_string<char, std::char_traits<char>, misc::allocator<char> > >("\n\tstd::basic_string<char,A> ");
}

void test_generic_string::length() 
{
	stl::cout << "\n\n\tlength-------------------------------------------------";
	length<slt::basic_string<char> >                                             ("\n\tgeneric_string            ");
	length<std::basic_string<char> >                                                ("\n\tstd::basic_string         ");
	length<std::basic_string<char, std::char_traits<char>, misc::allocator<char> > >("\n\tstd::basic_string<char,A> ");
}

void test_generic_string::max_size() 
{
	stl::cout << "\n\n\tmax_size-----------------------------------------------";
	max_size<slt::basic_string<char> >("\n\tgeneric_string");
	// std::basic_string returns a different maximum size;
//	max_size<std::basic_string<char> >("\n\tstd::basic_string");
//	max_size<std::basic_string<char, std::char_traits<char>, misc::allocator<char> > >("\n\tstd::basic_string<char,A>");
}

void test_generic_string::resize() 
{
	stl::cout << "\n\n\tresize-------------------------------------------------";
	resize<slt::basic_string<char> >                                             ("\n\tgeneric_string            ");
	resize<std::basic_string<char> >                                                ("\n\tstd::basic_string         ");
	resize<std::basic_string<char, std::char_traits<char>, misc::allocator<char> > >("\n\tstd::basic_string<char,A> ");
}

void test_generic_string::capacity() 
{
	stl::cout << "\n\n\tcapacity-----------------------------------------------";
	capacity<slt::basic_string<char> >("\n\tgeneric_string");
	// std::basic_string resizes with a different factor
//	capacity<std::basic_string<char> >("\n\tstd::basic_string");
//	capacity<std::basic_string<char, std::char_traits<char>, misc::allocator<char> > >("\n\tstd::basic_string<char,A>");
}

void test_generic_string::reserve() 
{
	stl::cout << "\n\n\treserve------------------------------------------------";
	reserve<slt::basic_string<char> >("\n\tgeneric_string");
	// see above: wrong capacity
//	reserve<std::basic_string<char> >("\n\tstd::basic_string");
//	reserve<std::basic_string<char, std::char_traits<char>, misc::allocator<char> > >("\n\tstd::basic_string<char,A>");
}

void test_generic_string::clear() 
{
	stl::cout << "\n\n\tclear--------------------------------------------------";
	clear<slt::basic_string<char> >                                             ("\n\tgeneric_string            ");
	clear<std::basic_string<char> >                                                ("\n\tstd::basic_string         ");
	clear<std::basic_string<char, std::char_traits<char>, misc::allocator<char> > >("\n\tstd::basic_string<char,A> ");
}

void test_generic_string::empty() 
{
	stl::cout << "\n\n\tempty--------------------------------------------------";
	empty<slt::basic_string<char> >                                             ("\n\tgeneric_string            ");
	empty<std::basic_string<char> >                                                ("\n\tstd::basic_string         ");
	empty<std::basic_string<char, std::char_traits<char>, misc::allocator<char> > >("\n\tstd::basic_string<char,A> ");
}

//Element access

void test_generic_string::operator_access_element() 
{
	stl::cout << "\n\n\toperator_access_element--------------------------------";
	operator_access_element<slt::basic_string<char> >                                             ("\n\tgeneric_string            ");
	operator_access_element<std::basic_string<char> >                                                ("\n\tstd::basic_string         ");
	operator_access_element<std::basic_string<char, std::char_traits<char>, misc::allocator<char> > >("\n\tstd::basic_string<char,A> ");
}

void test_generic_string::at() 
{
	stl::cout << "\n\n\tat-----------------------------------------------------";
	at<slt::basic_string<char> >                                             ("\n\tgeneric_string            ");
	at<std::basic_string<char> >                                                ("\n\tstd::basic_string         ");
	at<std::basic_string<char, std::char_traits<char>, misc::allocator<char> > >("\n\tstd::basic_string<char,A> ");
}

//Modifiers

void test_generic_string::operator_plus_equal() 
{
	stl::cout << "\n\n\toperator_plus_equal------------------------------------";
	operator_plus_equal<slt::basic_string<char> >                                             ("\n\tgeneric_string            ");
	operator_plus_equal<std::basic_string<char> >                                                ("\n\tstd::basic_string         ");
	operator_plus_equal<std::basic_string<char, std::char_traits<char>, misc::allocator<char> > >("\n\tstd::basic_string<char,A> ");
}

void test_generic_string::append() 
{
	stl::cout << "\n\n\tappend-------------------------------------------------";
	append<slt::basic_string<char> >                                             ("\n\tgeneric_string            ");
	append<std::basic_string<char> >                                                ("\n\tstd::basic_string         ");
	append<std::basic_string<char, std::char_traits<char>, misc::allocator<char> > >("\n\tstd::basic_string<char,A> ");
}

void test_generic_string::push_back() 
{
	stl::cout << "\n\n\tpush_back----------------------------------------------";
	push_back<slt::basic_string<char> >                                             ("\n\tgeneric_string            ");
	push_back<std::basic_string<char> >                                                ("\n\tstd::basic_string         ");
	push_back<std::basic_string<char, std::char_traits<char>, misc::allocator<char> > >("\n\tstd::basic_string<char,A> ");
}

void test_generic_string::assign() 
{
	stl::cout << "\n\n\tassign-------------------------------------------------";
	
	assign<slt::basic_string<char> >                                             ("\n\tgeneric_string            ");

	/* some methods are safe with slt::basic_string and trigger undefined behaviour with std::string */
//	assign<std::basic_string<char> >                                                ("\n\tstd::basic_string         ");
//	assign<std::basic_string<char, std::char_traits<char>, misc::allocator<char> > >("\n\tstd::basic_string<char,A> ");
}

void test_generic_string::insert() 
{
	stl::cout << "\n\n\tinsert-------------------------------------------------";
	insert<slt::basic_string<char> >                                             ("\n\tgeneric_string            ");
	insert<std::basic_string<char> >                                                ("\n\tstd::basic_string         ");
	insert<std::basic_string<char, std::char_traits<char>, misc::allocator<char> > >("\n\tstd::basic_string<char,A> ");
}

void test_generic_string::erase() 
{
	stl::cout << "\n\n\terase--------------------------------------------------";
	erase<slt::basic_string<char> >                                             ("\n\tgeneric_string            ");
	erase<std::basic_string<char> >                                                ("\n\tstd::basic_string         ");
	erase<std::basic_string<char, std::char_traits<char>, misc::allocator<char> > >("\n\tstd::basic_string<char,A> ");
}

void test_generic_string::replace() 
{
	stl::cout << "\n\n\treplace------------------------------------------------";
	replace<slt::basic_string<char> >                                             ("\n\tgeneric_string            ");
	replace<std::basic_string<char> >                                                ("\n\tstd::basic_string         ");
	replace<std::basic_string<char, std::char_traits<char>, misc::allocator<char> > >("\n\tstd::basic_string<char,A> ");
}

void test_generic_string::swap()
{
	stl::cout << "\n\n\tswap---------------------------------------------------";
	swap<slt::basic_string<char> >                                             ("\n\tgeneric_string            ");
	swap<std::basic_string<char> >                                                ("\n\tstd::basic_string         ");
	swap<std::basic_string<char, std::char_traits<char>, misc::allocator<char> > >("\n\tstd::basic_string<char,A> ");
}

//String operations

void test_generic_string::c_str()
{
	stl::cout << "\n\n\tc_str--------------------------------------------------";
	c_str<slt::basic_string<char> >                                             ("\n\tgeneric_string            ");
	c_str<std::basic_string<char> >                                                ("\n\tstd::basic_string         ");
	c_str<std::basic_string<char, std::char_traits<char>, misc::allocator<char> > >("\n\tstd::basic_string<char,A> ");
}

void test_generic_string::data()
{
	stl::cout << "\n\n\tdata---------------------------------------------------";
	data<slt::basic_string<char> >                                             ("\n\tgeneric_string            ");
	data<std::basic_string<char> >                                                ("\n\tstd::basic_string         ");
	data<std::basic_string<char, std::char_traits<char>, misc::allocator<char> > >("\n\tstd::basic_string<char,A> ");
}

void test_generic_string::get_allocator() 
{
	stl::cout << "\n\n\tget_allocator------------------------------------------";
	get_allocator<slt::basic_string<char> >                                             ("\n\tgeneric_string            ");
	get_allocator<std::basic_string<char> >                                                ("\n\tstd::basic_string         ");
	get_allocator<std::basic_string<char, std::char_traits<char>, misc::allocator<char> > >("\n\tstd::basic_string<char,A> ");
}

void test_generic_string::copy()
{
	stl::cout << "\n\n\tcopy---------------------------------------------------";
	copy<slt::basic_string<char> >                                             ("\n\tgeneric_string            ");
	copy<std::basic_string<char> >                                                ("\n\tstd::basic_string         ");
	copy<std::basic_string<char, std::char_traits<char>, misc::allocator<char> > >("\n\tstd::basic_string<char,A> ");
}

void test_generic_string::find()
{
	stl::cout << "\n\n\tfind---------------------------------------------------";
	find<slt::basic_string<char> >                                             ("\n\tgeneric_string            ");
	// basic_string.find(*ptr, -1) returns -1 versus stl::exception.
//	find<std::basic_string<char> >                                                ("\n\tstd::basic_string         ");
//	find<std::basic_string<char, std::char_traits<char>, misc::allocator<char> > >("\n\tstd::basic_string<char,A> ");
}

void test_generic_string::rfind()
{
	stl::cout << "\n\n\trfind--------------------------------------------------";
	rfind<slt::basic_string<char> >                                             ("\n\tgeneric_string            ");
	// pos0 = s0.rfind("89", (size_t) - 1, 0);
	// basic_string returns 10 versus npos
//	rfind<std::basic_string<char> >                                                ("\n\tstd::basic_string         ");
//	rfind<std::basic_string<char, std::char_traits<char>, misc::allocator<char> > >("\n\tstd::basic_string<char,A> ");
}

void test_generic_string::find_first_of()
{
	stl::cout << "\n\n\tfind_first_of------------------------------------------";

	find_first_of<slt::basic_string<char> >                                             ("\n\tgeneric_string            ");
	// pos0 = s0.find_first_of("89", (size_t) - 1);
	// basic_string returns -1 versus exception
//	find_first_of<std::basic_string<char> >                                                ("\n\tstd::basic_string         ");
//	find_first_of<std::basic_string<char, std::char_traits<char>, misc::allocator<char> > >("\n\tstd::basic_string<char,A> ");
}

void test_generic_string::find_last_of()
{
	stl::cout << "\n\n\tfind_last_of-------------------------------------------";
	find_last_of<slt::basic_string<char> >                                             ("\n\tgeneric_string            ");
	// s0 = string("1234567890");
	// pos0 = s0.find_last_of("89", 9, (size_t) - 1);
	// std::basic_string returns 9 versus npos. Position 9 would be end() but its a low number still.
	// I stick with npos.
//	find_last_of<std::basic_string<char> >                                                ("\n\tstd::basic_string         ");
//	find_last_of<std::basic_string<char, std::char_traits<char>, misc::allocator<char> > >("\n\tstd::basic_string<char,A> ");
}

void test_generic_string::find_first_not_of()
{
	stl::cout << "\n\n\tfind_first_not_of--------------------------------------";
	find_first_not_of<slt::basic_string<char> >                                             ("\n\tgeneric_string            ");
	// std::basic_string doesn't throw exception
//	find_first_not_of<std::basic_string<char> >                                                ("\n\tstd::basic_string         ");
//	find_first_not_of<std::basic_string<char, std::char_traits<char>, misc::allocator<char> > >("\n\tstd::basic_string<char,A> ");
}

void test_generic_string::find_last_not_of()
{
	stl::cout << "\n\n\tfind_last_not_of---------------------------------------";
	find_last_not_of<slt::basic_string<char> >                                             ("\n\tgeneric_string            ");
	// see find_last_of
	// the same thing here, std::basic_string returns 9 , the offset of end() iterator
	// but that's a low number. I prefer npos (-1).
//	find_last_not_of<std::basic_string<char> >                                                ("\n\tstd::basic_string         ");
//	find_last_not_of<std::basic_string<char, std::char_traits<char>, misc::allocator<char> > >("\n\tstd::basic_string<char,A> ");
}

void test_generic_string::substr()
{
	stl::cout << "\n\n\tsubstr-------------------------------------------------";
	substr<slt::basic_string<char> >                                             ("\n\tgeneric_string            ");
	substr<std::basic_string<char> >                                                ("\n\tstd::basic_string         ");
	substr<std::basic_string<char, std::char_traits<char>, misc::allocator<char> > >("\n\tstd::basic_string<char,A> ");
}

void test_generic_string::compare()
{
	stl::cout << "\n\n\tcompare------------------------------------------------";
	compare<slt::basic_string<char> >                                             ("\n\tgeneric_string            ");
	compare<std::basic_string<char> >                                                ("\n\tstd::basic_string         ");
	compare<std::basic_string<char, std::char_traits<char>, misc::allocator<char> > >("\n\tstd::basic_string<char,A> ");
}

//test end
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//template version of test function
//Member functions

template<typename Container>
void test_generic_string::ctor(const char* msg) 
{
	time_printer tp(msg, m_print_time);

	{/* using template type Container */
		typedef Container string;

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
		typedef Container string;

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

	{
		/* self assignment */
		typedef Container string;
		string s;
		s = s;
	}
}

template<typename Container>
void test_generic_string::assignament_op(const char* msg) 
{
	time_printer tp(msg, m_print_time);

	{
		/* using template type */
		typedef Container string;

		string str1, str2, str3;
		str1 = "Test string: "; // c-string
		str2 = 'x'; // single character
		str3 = str1 + str2; // string

		CPPUNIT_ASSERT(strcmp(str3.c_str(), "Test string: x") == 0);
	}

	{ /* using MSDN samples */

		// The first member function assigning a
		// character of a certain value to a string
		slt::basic_string<char> str1a("Hello ");
		str1a = '0';
		CPPUNIT_ASSERT(strcmp(str1a.c_str(), "0") == 0);

		// The second member function assigning the
		// characters of a C-string to a string
		slt::basic_string<char> str1b;
		const char *cstr1b = "Out There";
		str1b = cstr1b;
		CPPUNIT_ASSERT(strcmp(str1b.c_str(), "Out There") == 0);

		// The third member function assigning the characters
		// from one string to another string in two equivalent
		// ways, comparing the assign and operator =
		slt::basic_string<char> str1c("Hello"), str2c("Wide"), str3c("World");

		CPPUNIT_ASSERT(strcmp(str1c.c_str(), "Hello") == 0);
		CPPUNIT_ASSERT(strcmp(str2c.c_str(), "Wide") == 0);

		str1c.assign(str2c);

		CPPUNIT_ASSERT(strcmp(str1c.c_str(), "Wide") == 0);
		CPPUNIT_ASSERT(strcmp(str3c.c_str(), "World") == 0);

		str1c = str3c;

		CPPUNIT_ASSERT(strcmp(str1c.c_str(), "World") == 0);
	}
}

//Iterators

template<typename Container>
void test_generic_string::begin(const char* msg)
{
	time_printer tp(msg, m_print_time);

	{
		/* using template type */
		typedef Container string;

		string str("Test string");
		typename string::iterator it;
		size_t i = 0;
		for (it = str.begin(); it < str.end(); it++, ++i) {
			CPPUNIT_ASSERT(*it == str[i]);
		}

		typename string::const_iterator cit;
		i = 0;
		for (cit = str.begin(); cit < str.end(); cit++, ++i) {
			CPPUNIT_ASSERT(*cit == str[i]);
		}
	}

	{
		/* using MSDN sample */
		slt::basic_string<char> str1("No way out."), str2;
		slt::basic_string<char>::iterator strp_Iter, str1_Iter, str2_Iter;
		slt::basic_string<char>::const_iterator str1_cIter;

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
		catch (const stl::exception& exc)
		{
			exc.what();			
			bexc = true;
		}

		CPPUNIT_ASSERT(bexc);
	}
}

template<typename Container>
void test_generic_string::end(const char* msg)
{
	time_printer tp(msg, m_print_time);

	{
		/* using template type */

		typedef Container string;

		string str("Test string");
		typename string::iterator it;
		size_t i = 0;
		for (it = str.begin(); it < str.end(); it++, ++i)
		{
			CPPUNIT_ASSERT(*it == str[i]);
		}

		typename string::const_iterator cit;
		i = 0;
		for (cit = str.begin(); cit < str.end(); cit++, ++i)
		{
			CPPUNIT_ASSERT(*cit == str[i]);
		}
	}

	{
		/* using MSDN sample */
		slt::basic_string<char> str1("No way out."), str2;
		slt::basic_string<char>::iterator str_Iter, str1_Iter, str2_Iter;
		slt::basic_string<char>::const_iterator str1_cIter;

		str1_Iter = str1.end();
		str1_Iter--;
		str1_Iter--;

		CPPUNIT_ASSERT(*str1_Iter == 't');

		CPPUNIT_ASSERT(strcmp(str1.c_str(), "No way out.") == 0);

		const char* pstr = str1.c_str();

		// end used to test when an iterator has reached the end of its string
		for (str_Iter = str1.begin(); str_Iter != str1.end(); ++str_Iter) {
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
		catch (const stl::exception& exc)
		{
			exc.what();
			bexc = true;
		}

		CPPUNIT_ASSERT(bexc);
	}
}

template<typename Container>
void test_generic_string::rbegin(const char* msg)
{
	time_printer tp(msg, m_print_time);

	{
		/* using template type */
		typedef Container string;

		string str("now step live...");
		typename string::reverse_iterator rit;
		size_t i = str.size() - 1;
		for (rit = str.rbegin(); rit < str.rend(); rit++, --i) {
			CPPUNIT_ASSERT(*rit == str[i]);
		}

		typename string::const_reverse_iterator crit;
		i = str.size() - 1;
		for (crit = str.rbegin(); crit < str.rend(); crit++, --i) {
			CPPUNIT_ASSERT(*crit == str[i]);
		}
	}

	{
		/* using MSDN sample */
		slt::basic_string<char> str1("Able was I ere I saw Elba"), str2;
		slt::basic_string<char>::reverse_iterator str_rIter, str1_rIter, str2_rIter;
		slt::basic_string<char>::const_reverse_iterator str1_rcIter;

		str1_rIter = str1.rbegin();

		CPPUNIT_ASSERT(*str1_rIter == 'a');

		const char* ptr = str1.c_str();
		size_t pos = str1.size() - 1;

		for (str_rIter = str1.rbegin(); str_rIter != str1.rend(); str_rIter++) {
			CPPUNIT_ASSERT(*str_rIter == *(ptr + pos--));
		}

		// The dereferenced iterator can be used to modify a character
		*str1_rIter = 'A';

		CPPUNIT_ASSERT(*str1_rIter == 'A');
		pos = str1.size() - 1;

		for (str_rIter = str1.rbegin(); str_rIter != str1.rend(); str_rIter++) {
			CPPUNIT_ASSERT(*str_rIter == *(ptr + pos--));
		}

		// The following line would be an error because iterator is const
		// *str1_rcIter = 'A';

		// For an empty string, begin is equivalent to end
		CPPUNIT_ASSERT(str2.rbegin() == str2.rend());
	}
}

template<typename Container>
void test_generic_string::rend(const char* msg)
{
	time_printer tp(msg, m_print_time);

	{
		/* using template type */
		typedef Container string;

		string str("now step live...");
		typename string::reverse_iterator rit;
		size_t i = str.size() - 1;
		for (rit = str.rbegin(); rit < str.rend(); rit++, --i) {
			CPPUNIT_ASSERT(*rit == str[i]);
		}

		typename string::const_reverse_iterator crit;
		i = str.size() - 1;
		for (crit = str.rbegin(); crit < str.rend(); crit++, --i) {
			CPPUNIT_ASSERT(*crit == str[i]);
		}
	}

	{
		/* using MSDN sample */
		slt::basic_string<char> str1("Able was I ere I saw Elba"), str2;
		slt::basic_string<char>::reverse_iterator str_rIter, str1_rIter, str2_rIter;
		slt::basic_string<char>::const_reverse_iterator str1_rcIter;

		str1_rIter = str1.rbegin();

		CPPUNIT_ASSERT(*str1_rIter == 'a');

		const char* ptr = str1.c_str();
		size_t pos = str1.size() - 1;

		for (str_rIter = str1.rbegin(); str_rIter != str1.rend(); str_rIter++) {
			CPPUNIT_ASSERT(*str_rIter == *(ptr + pos--));
		}

		// The dereferenced iterator can be used to modify a character
		*str1_rIter = 'A';

		CPPUNIT_ASSERT(*str1_rIter == 'A');
		pos = str1.size() - 1;

		for (str_rIter = str1.rbegin(); str_rIter != str1.rend(); str_rIter++) {
			CPPUNIT_ASSERT(*str_rIter == *(ptr + pos--));
		}

		// The following line would be an error because iterator is const
		// *str1_rcIter = 'A';

		// For an empty string, begin is equivalent to end
		CPPUNIT_ASSERT(str2.rbegin() == str2.rend());
	}
}

//Capacity

template<typename Container>
void test_generic_string::size(const char* msg)
{
	time_printer tp(msg, m_print_time);

	{
		/* using template type */
		typedef Container string;

		string str("Test string");

		CPPUNIT_ASSERT(str.size() == 11);
	}

	{
		/* using MSDN sample */
		slt::basic_string<char> str1("Hello world");

		// The size and length member functions differ in name only
		slt::basic_string<char>::size_type sizeStr1, lenStr1;
		sizeStr1 = str1.size();
		lenStr1 = str1.length();

		slt::basic_string<char>::size_type capStr1, max_sizeStr1;
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
}

template<typename Container>
void test_generic_string::length(const char* msg)
{
	time_printer tp(msg, m_print_time);

	{
		/* using template type */
		typedef Container string;

		string str("Test string");

		CPPUNIT_ASSERT(str.length() == 11);
	}

	{
		/* using MSDN sample */
		slt::basic_string<char> str1("Hello world");

		// The size and length member functions differ in name only
		slt::basic_string<char>::size_type sizeStr1, lenStr1;
		sizeStr1 = str1.size();
		lenStr1 = str1.length();

		slt::basic_string<char>::size_type capStr1, max_sizeStr1;
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
}

template<typename Container>
void test_generic_string::max_size(const char* msg)
{
	time_printer tp(msg, m_print_time);

	typedef Container string;

	string str("Test string");

	size_t maxsz =
			static_cast<size_t> (-1) / sizeof (typename Container::value_type);

	CPPUNIT_ASSERT(str.max_size() == maxsz);
}

template<typename Container>
void test_generic_string::resize(const char* msg)
{
	time_printer tp(msg, m_print_time);

	{
		/* using template type */
		typedef Container string;

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
		slt::basic_string<char> str1("Hello world");
		slt::basic_string<char>::size_type sizeStr1;
		sizeStr1 = str1.size();
		slt::basic_string<char>::size_type capStr1;
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
}

template<typename Container>
void test_generic_string::capacity(const char* msg)
{
	time_printer tp(msg, m_print_time);

	{
		typedef Container string;

		string str("Test string");

		CPPUNIT_ASSERT(str.capacity() == 11);

		str.clear();
		CPPUNIT_ASSERT(str.capacity() == 11);

		string str2;

		CPPUNIT_ASSERT(str2.capacity() > 0);
	}

	{
		/* using MSDN sample */
		slt::basic_string<char> str1("Hello world");
		slt::basic_string<char>::size_type sizeStr1;
		sizeStr1 = str1.size();
		slt::basic_string<char>::size_type capStr1;
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
}

template<typename Container>
void test_generic_string::reserve(const char* msg)
{
	time_printer tp(msg, m_print_time);

	{
		typedef Container string;

		string str;

		str.reserve(100);

		CPPUNIT_ASSERT(str.capacity() == 100);
	}

	{
		/* using MSDN sample */
		slt::basic_string<char> str1("Hello world");
		slt::basic_string<char>::size_type sizeStr1;
		sizeStr1 = str1.size();
		slt::basic_string<char>::size_type capStr1;
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
}

template<typename Container>
void test_generic_string::clear(const char* msg)
{
	time_printer tp(msg, m_print_time);

	{
		typedef Container string;

		string str("Please type some lines of text. Enter a period to finish:\n");

		size_t cap = str.capacity();

		str.clear();

		CPPUNIT_ASSERT(str.size() == 0);
		/* should remain unchanged */
		CPPUNIT_ASSERT(str.capacity() == cap);
	}

	{
		slt::basic_string<char> str1("Hello world"), str2;
		slt::basic_string<char>::iterator str_Iter;
		CPPUNIT_ASSERT(str1.begin() != str1.end());
		str1.clear();
		CPPUNIT_ASSERT(str1.begin() == str1.end());
	}
}

template<typename Container>
void test_generic_string::empty(const char* msg)
{
	time_printer tp(msg, m_print_time);

	{
		/* template type */
		typedef Container string;

		string str("Please introduce a text. Enter an empty line to finish:\n");

		CPPUNIT_ASSERT(str.empty() == false);

		str.clear();

		CPPUNIT_ASSERT(str.empty() == true);
	}

	{
		/* MSDN sample */
		slt::basic_string<char> str1("Hello world");

		CPPUNIT_ASSERT(!str1.empty());

		slt::basic_string<char> str2;

		CPPUNIT_ASSERT(str2.empty());
	}
}

//Element access

template<typename Container>
void test_generic_string::operator_access_element(const char* msg)
{
	time_printer tp(msg, m_print_time);

	{
		/* template type */
		typedef Container string;

		char check[] = {'T', 'e', 's', 't', ' ', 's', 't', 'r', 'i', 'n', 'g'};
		string str("Test string");
		size_t i;
		for (i = 0; i < str.length(); i++) {
			CPPUNIT_ASSERT(str[i] == check[i]);
		}

		const string cstr("Test string");
		for (i = 0; i < cstr.length(); i++) {
			CPPUNIT_ASSERT(cstr[i] == check[i]); //operator[](..) const
		}
	}

	{
		/* MSDN sample */
		// The first member function assigning a
		// character of a certain value to a string
		slt::basic_string<char> str1a("Hello ");
		str1a = '0';

		CPPUNIT_ASSERT(str1a == "0");

		// The second member function assigning the
		// characters of a C-string to a string
		slt::basic_string<char> str1b;
		const char *cstr1b = "Out There";
		str1b = cstr1b;

		CPPUNIT_ASSERT(str1b == "Out There");

		// The third member function assigning the characters
		// from one string to another string in two equivalent
		// ways, comparing the assign and operator =
		slt::basic_string<char> str1c("Hello"), str2c("Wide"), str3c("World");

		str1c.assign(str2c);

		CPPUNIT_ASSERT(str1c == "Wide");

		str1c = str3c;

		CPPUNIT_ASSERT(str1c == "World");
	}
}

template<typename Container>
void test_generic_string::at(const char* msg)
{
	time_printer tp(msg, m_print_time);

	{
		/* template type */
		typedef Container string;

		string str("Test string");
		for (size_t i = 0; i < str.length(); i++) {
			CPPUNIT_ASSERT(str.at(i) == str[i]);
		}
		//return 0;

		const string cstr("Test string");
		for (size_t i = 0; i < cstr.length(); i++) {
			CPPUNIT_ASSERT(cstr.at(i) == cstr[i]); //at() const
		}
	}

	{
		/* MSDN sample */
		slt::basic_string<char> str1("Hello world"), str2("Goodbye world");
		const slt::basic_string<char> cstr1("Hello there"), cstr2("Goodbye now");

		CPPUNIT_ASSERT(str1 == "Hello world");
		CPPUNIT_ASSERT(str2 == "Goodbye world");

		// Element access to the non-const strings
		slt::basic_string<char>::reference refStr1 = str1 [6];
		slt::basic_string<char>::reference refStr2 = str2.at(3);

		CPPUNIT_ASSERT(refStr1 == 'w');
		CPPUNIT_ASSERT(refStr2 == 'd');

		// Element access to the const strings
		bool null_not_accesible = false;
		try 
		{
			slt::basic_string<char>::const_reference null_elem = cstr1[ cstr1.length() ];
			(void)null_elem;
		}
		catch (const stl::exception&)
		{
			null_not_accesible = true;
		}

		CPPUNIT_ASSERT(null_not_accesible);

		/* access null termination via .c_str() */
		slt::basic_string<char>::const_reference crefStr1 = cstr1.c_str()[ cstr1.length() ];
		slt::basic_string<char>::const_reference crefStr2 = cstr2.at(8);

		CPPUNIT_ASSERT(crefStr1 == '\0');
		CPPUNIT_ASSERT(crefStr2 == 'n');
	}
}

//Modifiers

template<typename Container>
void test_generic_string::operator_plus_equal(const char* msg)
{
	time_printer tp(msg, m_print_time);

	{
		/* typename sample */
		typedef Container string;

		string name("John");
		string family("Smith");
		name += " K. "; // c-string
		name += family; // string
		name += '\n'; // character

		CPPUNIT_ASSERT(strcmp(name.c_str(), "John K. Smith\n") == 0);
	}

	{
		/* MSDN sample */
		// The first member function
		// appending a single character to a string
		slt::basic_string<char> str1a("Hello");
		CPPUNIT_ASSERT(str1a == "Hello");

		str1a += '!';

		CPPUNIT_ASSERT(str1a == "Hello!");

		// The second member function
		// appending a C-string to a string
		slt::basic_string<char> str1b("Hello ");
		const char *cstr1b = "Out There";

		str1b += cstr1b;

		CPPUNIT_ASSERT(str1b == "Hello Out There");

		// The third member function
		// appending one string to another in two ways,
		// comparing append and operator [ ]
		slt::basic_string<char> str1d("Hello "), str2d("Wide "), str3d("World");

		CPPUNIT_ASSERT(str2d == "Wide ");

		str1d.append(str2d);

		CPPUNIT_ASSERT(str1d == "Hello Wide ");

		str1d += str3d;

		CPPUNIT_ASSERT(str1d == "Hello Wide World");
	}
}

template<typename Container>
void test_generic_string::append(const char* msg)
{
	time_printer tp(msg, m_print_time);

	{
		/* template typename */
		typedef Container string;

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
		str.append(5, 0x2E); // "....."

		CPPUNIT_ASSERT(
				strcmp(str.c_str(),
				"Writing 10 dots here: .......... and then 5 more.....") == 0);
	}

	{
		/* MSDN sample */
		// The first member function
		// appending a C-string to a string
		slt::basic_string<char> str1a("Hello ");
		const char *cstr1a = "Out There ";

		CPPUNIT_ASSERT(str1a == "Hello ");

		str1a.append(cstr1a);

		CPPUNIT_ASSERT(str1a == "Hello Out There ");

		// The second member function
		// appending part of a C-string to a string
		slt::basic_string<char> str1b("Hello ");
		const char *cstr1b = "Out There ";

		str1b.append(cstr1b, 3);

		CPPUNIT_ASSERT(str1b == "Hello Out");

		// The third member function
		// appending part of one string to another
		slt::basic_string<char> str1c("Hello "), str2c("Wide World ");
		str1c.append(str2c, 5, 5);

		CPPUNIT_ASSERT(str1c == "Hello World");

		// The fourth member function
		// appending one string to another in two ways,
		// comparing append and operator [ ]
		slt::basic_string<char> str1d("Hello "), str2d("Wide "), str3d("World ");

		str1d.append(str2d);

		CPPUNIT_ASSERT(str1d == "Hello Wide ");

		str1d += str3d;

		CPPUNIT_ASSERT(str1d == "Hello Wide World ");

		// The fifth member function
		// appending characters to a string
		slt::basic_string<char> str1e("Hello ");
		str1e.append(4, '!');

		CPPUNIT_ASSERT(str1e == "Hello !!!!");

		// The sixth member function
		// appending a range of one string to another
		slt::basic_string<char> str1f("Hello "), str2f("Wide World ");
		str1f.append(str2f.begin() + 5, str2f.end() - 1);

		CPPUNIT_ASSERT(str1f == "Hello World");
	}
}

template<typename Container>
void test_generic_string::push_back(const char* msg)
{
	time_printer tp(msg, m_print_time);

	{
		/* template type */
		typedef Container string;
		string str2;
		const char* buff = "test.txt OK.\n";
		const char* beg = buff;
		while (*buff != '\0') {
			str2.push_back(*buff++);
		}

		CPPUNIT_ASSERT(str2 == beg);
	}

	{
		/* MSDN sample */
		slt::basic_string<char> str1("abc");
		slt::basic_string<char>::iterator str_Iter, str1_Iter;

		str1.push_back('d');
		str1_Iter = str1.end();
		str1_Iter--;

		CPPUNIT_ASSERT(*str1_Iter == 'd');

		CPPUNIT_ASSERT(str1 == "abcd");
	}
}

template<typename Container>
void test_generic_string::assign(const char* msg)
{
	time_printer tp(msg, m_print_time);

	{
		/* template type */
		typedef Container string;

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
		typedef Container string;


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
		typedef Container string;

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
		CPPUNIT_ASSERT( s0 != "" ); // s0 has a bigger size

		s0.assign(10, '\n');
		CPPUNIT_ASSERT( s0 == "\n\n\n\n\n\n\n\n\n\n" );

		s0.assign(10, '\t');
		CPPUNIT_ASSERT( s0 == "\t\t\t\t\t\t\t\t\t\t" );

		//self assignment using iterators
		s0 = "1234567890";
		typename string::iterator s0ib = s0.begin();
		typename string::iterator s0ie = s0.end();
		s1 = s0.assign(s0ib, s0ie);
		CPPUNIT_ASSERT( s1 == "1234567890" );
		CPPUNIT_ASSERT( s0 == s1 );

		s0 = "1234567890";
		typename string::const_iterator s0cib = s0.begin();
		typename string::const_iterator s0cie = s0.end();
		s1 = s0.assign(s0cib, s0cie);
		CPPUNIT_ASSERT( s1 == "1234567890" );
		CPPUNIT_ASSERT( s0 == s1 );

		//self assignment using iterators in reverse order
		bool diff_negative_not_throwing_at_the_moment = false;
		try
		{
			s1 = s0.assign(s0ie, s0ib);
		}
		catch(stl::exception&)
		{
			diff_negative_not_throwing_at_the_moment = true; 
		}
		CPPUNIT_ASSERT( !diff_negative_not_throwing_at_the_moment );

		diff_negative_not_throwing_at_the_moment = false;
		try
		{
			s1 = s0.assign(s0cie, s0cib);
		}catch(stl::exception&)
		{ 
			diff_negative_not_throwing_at_the_moment = true; 
		}
		CPPUNIT_ASSERT( !diff_negative_not_throwing_at_the_moment );


		//self assignment using reverse_iterator(s)
		s0 = "1234567890";
		typename string::reverse_iterator s0rib = s0.rbegin();
		typename string::reverse_iterator s0rie = s0.rend();
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
		typename string::const_reverse_iterator s0crib = s0.rbegin();
		typename string::const_reverse_iterator s0crie = s0.rend();
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
}

template<typename Container>
void test_generic_string::insert(const char* msg)
{
	time_printer tp(msg, m_print_time);

	{
		/* template type */
		typedef Container string;

		string str = "to be question";
		string str2 = "the ";
		string str3 = "or not to be";
		typename string::iterator it;

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
		/* MSDN sample */
		// The first member function inserting a C-string
		// at a given position
		slt::basic_string<char> str1a("way");
		const char *cstr1a = "a";
		str1a.insert(0, cstr1a);

		CPPUNIT_ASSERT(str1a == "away");

		// The second member function inserting a C-string
		// at a given position for a specified number of elements
		slt::basic_string<char> str2a("Good");
		const char *cstr2a = "Bye Bye Baby";
		str2a.insert(4, cstr2a, 3);

		CPPUNIT_ASSERT(str2a == "GoodBye");

		// The third member function inserting a string
		// at a given position
		slt::basic_string<char> str3a("Bye");
		slt::basic_string<char> str3b("Good");
		str3a.insert(0, str3b);

		CPPUNIT_ASSERT(str3a == "GoodBye");

		// The fourth member function inserting part of
		// a string at a given position
		slt::basic_string<char> str4a("Good ");
		slt::basic_string<char> str4b("Bye Bye Baby");
		str4a.insert(5, str4b, 8, 4);

		CPPUNIT_ASSERT(str4a == "Good Baby");

		// The fifth member function inserts a number of characters
		// at a specified position in the string
		slt::basic_string<char> str5("The number is: .");
		str5.insert(15, 3, '3');

		CPPUNIT_ASSERT(str5 == "The number is: 333.");

		// The sixth member function inserts a character
		// at a specified position in the string
		slt::basic_string<char> str6("ABCDFG");
		slt::basic_string<char>::iterator str6_Iter = (str6.begin() + 4);
		str6.insert(str6_Iter, 'e');

		CPPUNIT_ASSERT(str6 == "ABCDeFG");

		// The seventh member function inserts a range
		// at a specified position in the string
		slt::basic_string<char> str7a("ABCDHIJ");
		slt::basic_string<char> str7b("abcdefgh");
		slt::basic_string<char>::iterator str7a_Iter = (str7a.begin() + 4);
		str7a.insert(str7a_Iter, str7b.begin() + 4, str7b.end() - 1);

		CPPUNIT_ASSERT(str7a == "ABCDefgHIJ");

		// The eigth member function inserts a number of
		// characters at a specified position in the string
		slt::basic_string<char> str8("ABCDHIJ");
		slt::basic_string<char>::iterator str8_Iter = (str8.begin() + 4);
		str8.insert(str8_Iter, 3, 'e');

		CPPUNIT_ASSERT(str8 == "ABCDeeeHIJ");
	}
}

template<typename Container>
void test_generic_string::erase(const char* msg)
{
	time_printer tp(msg, m_print_time);

	{
		/* template type */
		typedef Container string;

		string str("This is an example phrase.");
		typename string::iterator it;

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
		/* MSDN sample */
		// The 1st member function using a range demarcated
		// by iterators
		slt::basic_string<char> str1("Hello world");
		slt::basic_string<char>::iterator str1_Iter;

		str1_Iter = str1.erase(str1.begin() + 3, str1.end() - 1);

		CPPUNIT_ASSERT(*str1_Iter == 'd');
		CPPUNIT_ASSERT(str1 == "Held");

		// The 2nd member function erasing a char pointed to
		// by an iterator
		slt::basic_string<char> str2("Hello World");
		slt::basic_string<char>::iterator str2_Iter;

		str2_Iter = str2.erase(str2.begin() + 5);
		CPPUNIT_ASSERT(*str2_Iter == 'W');
		CPPUNIT_ASSERT(str2 == "HelloWorld");

		// The 3rd member function erasing a number of chars
		// after a char
		slt::basic_string<char> str3("Hello computer"), str3m;
		slt::basic_string<char>::iterator str3_Iter;

		str3m = str3.erase(6, 8);

		CPPUNIT_ASSERT(str3m == "Hello ");
	}
}

template<typename Container>
void test_generic_string::replace(const char* msg)
{
	time_printer tp(msg, m_print_time);

	{
		/* using template type */
		typedef Container string;

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
		typename string::iterator it = str.begin();
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
		/* using MSDN sample */

		// The first two member functions replace
		// part of the operand string with
		// characters from a parameter string or C-string
		slt::basic_string<char> result1a, result1b;
		slt::basic_string<char> s1o("AAAAAAAA");
		slt::basic_string<char> s1p("BBB");
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
		slt::basic_string<char> result2a, result2b;
		slt::basic_string<char> s2o("AAAAAAAA");
		slt::basic_string<char> s2p("BBB");
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
		slt::basic_string<char> result3a;
		slt::basic_string<char> s3o("AAAAAAAA");
		char ch3p = 'C';

		CPPUNIT_ASSERT(strcmp(s3o.c_str(), "AAAAAAAA") == 0);

		CPPUNIT_ASSERT(ch3p == 'C');

		result3a = s3o.replace(1, 3, 4, ch3p);

		CPPUNIT_ASSERT(strcmp(result3a.c_str(), "ACCCCAAAA") == 0);

		// The sixth & seventh member functions replace
		// part of the operand string, delineated with iterators,
		// with a parameter string or C-string
		slt::basic_string<char> s4o("AAAAAAAA");
		slt::basic_string<char> s4p("BBB");
		const char* cs4p = "CCC";

		CPPUNIT_ASSERT(strcmp(s4o.c_str(), "AAAAAAAA") == 0);
		CPPUNIT_ASSERT(strcmp(s4p.c_str(), "BBB") == 0);
		CPPUNIT_ASSERT(strcmp(cs4p, "CCC") == 0);

		slt::basic_string<char>::iterator IterF0, IterL0;
		IterF0 = s4o.begin();
		IterL0 = s4o.begin() + 3;
		slt::basic_string<char> result4a, result4b;
		result4a = s4o.replace(IterF0, IterL0, s4p);

		CPPUNIT_ASSERT(strcmp(result4a.c_str(), "BBBAAAAA") == 0);

		result4b = s4o.replace(IterF0, IterL0, cs4p);

		CPPUNIT_ASSERT(strcmp(result4b.c_str(), "CCCAAAAA") == 0);

		// The 8th member function replaces
		// part of the operand string delineated with iterators
		// with a number of characters from a parameter C-string
		slt::basic_string<char> s5o("AAAAAAAF");
		const char* cs5p = "CCCBB";

		CPPUNIT_ASSERT(strcmp(s5o.c_str(), "AAAAAAAF") == 0);
		CPPUNIT_ASSERT(s5o == "AAAAAAAF");
		CPPUNIT_ASSERT(strcmp(cs5p, "CCCBB") == 0);

		slt::basic_string<char>::iterator IterF1, IterL1;
		IterF1 = s5o.begin();
		IterL1 = s5o.begin() + 4;
		slt::basic_string<char> result5a;
		result5a = s5o.replace(IterF1, IterL1, cs5p, 4);

		CPPUNIT_ASSERT(strcmp(result5a.c_str(), "CCCBAAAF") == 0);
		CPPUNIT_ASSERT(result5a == "CCCBAAAF");

		// The 9th member function replaces
		// part of the operand string delineated with iterators
		// with specified characters
		slt::basic_string<char> s6o("AAAAAAAG");
		char ch6p = 'q';

		slt::basic_string<char>::iterator IterF2, IterL2;
		IterF2 = s6o.begin();
		IterL2 = s6o.begin() + 3;
		slt::basic_string<char> result6a;
		result6a = s6o.replace(IterF2, IterL2, 4, ch6p);

		CPPUNIT_ASSERT(strcmp(result6a.c_str(), "qqqqAAAAG") == 0);

		// The 10th member function replaces
		// part of the operand string delineated with iterators
		// with part of a parameter string delineated with iterators
		slt::basic_string<char> s7o("OOOOOOO");
		slt::basic_string<char> s7p("PPPP");

		CPPUNIT_ASSERT(strcmp(s7o.c_str(), "OOOOOOO") == 0);
		CPPUNIT_ASSERT(strcmp(s7p.c_str(), "PPPP") == 0);

		slt::basic_string<char>::iterator IterF3, IterL3, IterF4, IterL4;
		IterF3 = s7o.begin() + 1;
		IterL3 = s7o.begin() + 3;
		IterF4 = s7p.begin();
		IterL4 = s7p.begin() + 2;
		slt::basic_string<char> result7a;
		result7a = s7o.replace(IterF3, IterL3, IterF4, IterL4);

		CPPUNIT_ASSERT(strcmp(result7a.c_str(), "OPPOOOO") == 0);
	}
}

template<typename Container>
void test_generic_string::swap(const char* msg)
{
	time_printer tp(msg, m_print_time);

	{
		/* template type sample */
		typedef Container string;

		string buyer("money");
		string seller("goods");

		seller.swap(buyer);

		CPPUNIT_ASSERT(strcmp(seller.c_str(), "money") == 0);

		CPPUNIT_ASSERT(strcmp(buyer.c_str(), "goods") == 0);
	}

	{
		slt::basic_string<char> s1("");
		slt::basic_string<char> s2("");
		s1.swap(s2);
		slt::basic_string<char> s3;
		s3 = s1;
		CPPUNIT_ASSERT(s1.empty());
		CPPUNIT_ASSERT(s2.empty());
		CPPUNIT_ASSERT(s3.empty());
	}
}

//String operations

template<typename Container>
void test_generic_string::c_str(const char* msg)
{
	time_printer tp(msg, m_print_time);

	{
		/* template type */
		typedef Container string;

		const char* table[] = {"Please", "split", "this", "phrase", "into", "tokens"};

		char * cstr, *p;

		string str("Please split this phrase into tokens");

		cstr = new char [str.size() + 1];
		strcpy(cstr, str.c_str());

		// cstr now contains a c-string copy of str
		int i = 0;

		p = strtok(cstr, " ");
		while (p != NULL) {
			CPPUNIT_ASSERT(strcmp(p, table[i++]) == 0);
			p = strtok(NULL, " ");
		}

		delete[] cstr;
	}

	{
		/* MSDN sample */
		slt::basic_string<char> str1("Hello world");

		// Converting a string to an array of characters
		const char *ptr1 = 0;
		ptr1 = str1.data();

		CPPUNIT_ASSERT(strlen(ptr1) == 11);

		// Converting a string to a C-style string
		const char *c_str1 = str1.c_str();

		CPPUNIT_ASSERT(strlen(c_str1) == 11);
	}
}

template<typename Container>
void test_generic_string::data(const char* msg)
{
	time_printer tp(msg, m_print_time);

	{
		/* template type */
		typedef Container string;

		int length;

		string str = "Test string";
		const char* cstr = "Test string";

		CPPUNIT_ASSERT(str.length() == strlen(cstr));

		length = str.length();

		CPPUNIT_ASSERT(memcmp(cstr, str.data(), length) == 0);
	}

	{
		/* MSDN sample */
		slt::basic_string<char> str1("Hello world");

		// Converting a string to an array of characters
		const char *ptr1 = 0;
		ptr1 = str1.data();

		CPPUNIT_ASSERT(strcmp(ptr1, "Hello world") == 0);

		// Converting a string to a C-style string
		const char *c_str1 = str1.c_str();

		/* same address for returned char array */
		CPPUNIT_ASSERT(c_str1 == ptr1);

		CPPUNIT_ASSERT(strcmp(c_str1, "Hello world") == 0);
	}
}

template<typename Container>
void test_generic_string::get_allocator(const char* msg)
{
	time_printer tp(msg, m_print_time);
	//not implemented
}

template<typename Container>
void test_generic_string::copy(const char* msg)
{
	time_printer tp(msg, m_print_time);

	typedef Container string;

	size_t length;
	char buffer[20];
	string str("Test string...");
	length = str.copy(buffer, 6, 5);
	buffer[length] = '\0';

	CPPUNIT_ASSERT(strcmp(buffer, "string") == 0);
}

template<typename Container>
void test_generic_string::find(const char* msg)
{
	time_printer tp(msg, m_print_time);

	{
		/* template type */
		typedef Container string;

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
		typedef Container string;

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
		}catch(const stl::exception&){ throw1 = true; };
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
}

template<typename Container>
void test_generic_string::rfind(const char* msg)
{
	time_printer tp(msg, m_print_time);

	{
		/* template type */
		typedef Container string;

		string str("The sixth sick sheik's sixth sheep's sick.");
		string key("sixth");
		size_t found;

		found = str.rfind(key);

		CPPUNIT_ASSERT(found == 23);

		str.replace(found, key.length(), "seventh");

		CPPUNIT_ASSERT(strcmp(str.c_str(), "The sixth sick sheik's seventh sheep's sick.") == 0);
	}

	{
		typedef Container string;

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
}

template<typename Container>
void test_generic_string::find_first_of(const char* msg)
{
	time_printer tp(msg, m_print_time);

	{
		/* template type */
		typedef Container string;

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
		typedef Container string;

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
		try{
		pos0 = s0.find_first_of("89", (size_t) - 1);
		} catch(const stl::exception&){ throw1 = true; }
		CPPUNIT_ASSERT( throw1 );

		//count throws
		pos0 = s0.find_first_of("89", 9, 0);
		CPPUNIT_ASSERT(pos0 == string::npos);

		pos0 = s0.find_first_of("89", 9, 3);
		CPPUNIT_ASSERT( pos0 == string::npos );

		pos0 = s0.find_first_of("89", 9, (size_t) - 1);
		CPPUNIT_ASSERT( pos0 == string::npos );
	}
}

template<typename Container>
void test_generic_string::find_last_of(const char* msg)
{
	time_printer tp(msg, m_print_time);

	{
		/* template type */
		typedef Container string;

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
		typedef Container string;

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

		pos0 = s0.find_last_of("89", 9, (size_t)-1);
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
}

template<typename Container>
void test_generic_string::find_first_not_of(const char* msg)
{
	time_printer tp(msg, m_print_time);

	{
		/* template type */
		typedef Container string;

		string str("look for non-alphabetic characters...");
		size_t found;

		found = str.find_first_not_of("abcdefghijklmnopqrstuvwxyz ");

		CPPUNIT_ASSERT(found == 12);
		CPPUNIT_ASSERT(str[found] == '-');
	}

	{
		typedef Container string;

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
		try{
			pos0 = s0.find_first_not_of('8', (size_t) - 1);
		}
		catch(const stl::exception&){ throw1 = true; }

		CPPUNIT_ASSERT( throw1 );

		s0 = "1234567890";
		pos0 = s0.find_first_not_of("098764321");
		CPPUNIT_ASSERT(pos0 == 4);

		pos0 = s0.find_first_not_of("098764321", 4);
		CPPUNIT_ASSERT(pos0 == 4);

		pos0 = s0.find_first_not_of("098764321", 5);
		CPPUNIT_ASSERT(pos0 == string::npos);


		throw1 = false;
		try{
			pos0 = s0.find_first_not_of("098764321", (size_t) - 1);
		}
		catch(const stl::exception&){ throw1 = true; }
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
		try{
			pos0 = s0.find_first_not_of(s1, (size_t) - 1);
		}
		catch(const stl::exception&){ throw1 = true; }
		CPPUNIT_ASSERT( throw1 );
	}
}

template<typename Container>
void test_generic_string::find_last_not_of(const char* msg)
{
	time_printer tp(msg, m_print_time);

	{
		/* template type */
		typedef Container string;

		string str("erase trailing white-spaces   \n");
		string whitespaces(" \t\f\v\n\r");
		size_t found;

		found = str.find_last_not_of(whitespaces);
		if (found != string::npos) {
			str.erase(found + 1);
		} else {
			str.clear();
		}

		CPPUNIT_ASSERT(strcmp(str.c_str(), "erase trailing white-spaces") == 0);
	}

	{
		typedef Container string;

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
}

template<typename Container>
void test_generic_string::substr(const char* msg)
{
	time_printer tp(msg, m_print_time);

	typedef Container string;

	string str = "We think in generalities, but we live in details.";
	// quoting Alfred N. Whitehead
	string str2, str3;
	size_t pos;

	str2 = str.substr(12, 12); // "generalities"
	pos = str.find("live"); // position of "live" in str
	str3 = str.substr(pos); // get from "live" to the end

	CPPUNIT_ASSERT(strcmp(str3.c_str(), "live in details.") == 0);
}

template<typename Container>
void test_generic_string::compare(const char* msg)
{
	time_printer tp(msg, m_print_time);

	typedef Container string;

	string str1("green apple");
	string str2("red apple");

	CPPUNIT_ASSERT(str1.compare(str2) != 0);

	CPPUNIT_ASSERT(str1.compare(6, 5, "apple") == 0);

	CPPUNIT_ASSERT(str2.compare(str2.size() - 5, 5, "apple") == 0);

	CPPUNIT_ASSERT(str1.compare(6, 5, str2, 4, 5) == 0);
}

//end of template version of test function
//////////////////////////////////////////////////////////////////////////

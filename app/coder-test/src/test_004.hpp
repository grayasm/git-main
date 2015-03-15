/*
	Copyright (C) 2011 Mihai Vasilian

	This program is free software; you can redistribute it and/or modify it under the terms of the GNU General
	Public License as published by the Free Software Foundation; either version 2 of the License, or (at your
	option) any later version.

	This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the 
	implied warranty of	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
	for more details.

	You should have received a copy of the GNU General Public License along with this program. 
	If not, see http://www.gnu.org/licenses/.

	contact: grayasm@gmail.com
*/




#ifndef __test_4_hpp__
#define __test_4_hpp__

#include "test_gen.hpp"



class test4 : public test_gen
{
public:
	static void run(const char* test);

private:
	enum TokenAttribute
	{
		A_UNKNOWN=0,
		A_IDENTIFIER,
		A_PLUS,
		A_MINUS,
		A_NEGATION,
		A_UNARY_PLUS,
		A_MULTIPLICATION,
		A_DIVIZION,
		A_REMAINDER,
		A_XOR,
		A_POWER,
		A_TEXT,
		A_WS,
		A_TERMINATOR
	};


	test4():test_gen(){};
	//virtual
	char* GetText();
	void SetGrammar(ebnf::DefaultGrammar::Ptr& grammar);
	void SetSyntax(lex::Base::Syntax& ref);
	void SetReports(lex::Base::Reports& reps);

	//non-virtual
	void AddAsProduction(lex::Base::Syntax& prod, const char* p[], const int a[], int lim);
};


#endif//__test_4_hpp__
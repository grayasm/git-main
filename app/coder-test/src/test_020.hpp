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




#ifndef __test_20_hpp__
#define __test_20_hpp__

#include "test_gen.hpp"



class test20 : public test_gen
{
public:
	static void run(const char* test);

private:

	enum TokenAttribute
	{
		TA_UNKNOWN=0,
		TA_DECIMAL,
		TA_HEXADECIMAL,
		TA_OCTAL,
		TA_TERMINAL,

		TA_WS,
		TA_HEX_PREFIX,
		TA_UNSIGNED_SUFFIX,
		TA_LONG_SUFFIX,
		TA_LONG_LONG_SUFFIX,
		TA_END
	};


	test20():test_gen(){};
	//virtual
	char* GetText();
	void SetGrammar(ebnf::DefaultGrammar::Ptr& grammar);
	void SetSyntax(lex::Base::Syntax& ref);
	void SetReports(lex::Base::Reports& reps);


	//non-virtual
	void AddAsProduction(lex::Base::Syntax& prod, const char* p[], const int a[], int lim);
};


#endif//__test_20_hpp__
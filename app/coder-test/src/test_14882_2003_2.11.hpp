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



#ifndef __test_14882_2003_2_11_hpp__
#define __test_14882_2003_2_11_hpp__



#include "test_gen.hpp"



class test_14882_2003_2_11 : public test_gen
{
public:
	static void run(const char* test);

private:

	enum TokenAttribute
	{
		TA_UNKNOWN=0,
		TA_ASM,
		TA_AUTO,
		TA_BOOL,
		TA_BREAK,
		TA_CASE,
		TA_CATCH,
		TA_CHAR,
		TA_CLASS,
		TA_CONST,
		TA_CONST_CAST,
		TA_CONTINUE,
		TA_DEFAULT,
		TA_DELETE,
		TA_DO,
		TA_DOUBLE,
		TA_DYNAMIC_CAST,
		TA_ELSE,
		TA_ENUM,
		TA_EXPLICIT,
		TA_EXPORT,
		TA_EXTERN,
		TA_FALSE,
		TA_FLOAT,
		TA_FOR,
		TA_FRIEND,
		TA_GOTO,
		TA_IF,
		TA_INLINE,
		TA_INT,
		TA_LONG,
		TA_MUTABLE,
		TA_NAMESPACE,
		TA_NEW,
		TA_OPERATOR,
		TA_PRIVATE,
		TA_PROTECTED,
		TA_PUBLIC,
		TA_REGISTER,
		TA_REINTERPRET_CAST,
		TA_RETURN,
		TA_SHORT,
		TA_SIGNED,
		TA_SIZEOF,
		TA_STATIC,
		TA_STATIC_CAST,
		TA_STRUCT,
		TA_SWITCH,
		TA_TEMPLATE,
		TA_THIS,
		TA_THROW,
		TA_TRUE,
		TA_TRY,
		TA_TYPEDEF,
		TA_TYPEID,
		TA_TYPENAME,
		TA_UNION,
		TA_UNSIGNED,
		TA_USING,
		TA_VIRTUAL,
		TA_VOID,
		TA_VOLATILE,
		TA_WCHAR_T,
		TA_WHILE,
		TA_TERMINAL,
		TA_END
	};


	test_14882_2003_2_11():test_gen(){};
	//virtual
	char* GetText();
	void SetGrammar(ebnf::DefaultGrammar::Ptr& grammar);
	void SetSyntax(lex::Base::Syntax& ref);
	void SetReports(lex::Base::Reports& reps);


	//non-virtual
	void AddAsProduction(lex::Base::Syntax& prod, const char* p[], const int a[], int lim);
};




#endif//__test_14882_2003_2_11_hpp__




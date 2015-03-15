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



#include "test_005.hpp"




void test5::run(const char* test)
{
	test5 obj;
	obj.test_gen::run(test);
};


char* test5::GetText()
{
	//must preserve correct position in Lexer::CheckTree
	/*
		Stream AND &&
		stream: "1autoe"
		m["syntax"] = 
			(m["0_9"] && m["auto"] && m["0_9"]) ||
			(m["0_9"] && m["auto"] && m["a_z"]) ;

		2-nd rule begin to parse in wrong position 5 instead of 1.
	*/


	char* text=
		"1autoe";

	return text;
};


void test5::SetGrammar(ebnf::DefaultGrammar::Ptr& grammar)
{
	grammar->SetTerm("endl");
	ebnf::Grammar::Map& m = grammar->GetMap();

	//grammar
	m["auto"] = new lex::Quote("auto");

	m["start"] = 
		(
				LEX(m["0_9"], A_DIGIT, "dot a digit: 0-9", 1) 
			&&	LEX(m["auto"], A_AUTO, "expected word: auto", 1) 
			&&	LEX(m["0_9"], A_DIGIT, "dot a digit: 0-9", 1)) 
		||
		(
				LEX(m["0_9"], A_DIGIT, "dot a digit: 0-9", 1) 
			&&	LEX(m["auto"], A_AUTO, "expected word: auto", 1) 
			&&	LEX(m["a_z"], A_LETTER, "not a letter: a-z")) ;
};


void test5::SetSyntax(lex::Base::Syntax& ref)
{
	const char* p1[]={"1","auto","e"};
	const int a1[]={A_DIGIT, A_AUTO, A_LETTER};
	AddAsProduction(ref, p1, a1, 3);
};



void test5::SetReports(lex::Base::Reports& /*rep*/)
{

};


void test5::AddAsProduction(lex::Base::Syntax& ref, const char* p[], const int a[], int lim)
{	
	lex::Base::Production prod;
	//int lim = sizeof(p)/sizeof(p[0]);
	for(int i=0; i<lim; ++i)
	{
		lex::Token token;
		token.SetToken(p[i]);
		token.SetAttr(a[i]);

		prod.push_back(token);
	};
	ref.push_back(prod);
};




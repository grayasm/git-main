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



#include "test_007.hpp"




void test7::run(const char* test)
{
	test7 obj;
	obj.test_gen::run(test);
};


char* test7::GetText()
{	
	/*
		Has
		text: 'a_'
		m["syntax"] = (m["a"] & 0 * m["_"]) + m["a"];
		syntax reference: "a"

		When left side of + needs to re-validate the stream resized to 1 position, it consumes
		first token 'a' and then reaches the end of stream (which in reality is '_'). 
		That's why I put back the (pseudo) eof, and it must be removed at the top level of Lexer.
	*/

	char* text=
		"a_";

	return text;
};


void test7::SetGrammar(ebnf::DefaultGrammar::Ptr& grammar)
{
	grammar->SetTerm("endl");
	ebnf::Grammar::Map& m = grammar->GetMap();

	//grammar
	m["a"] = new lex::Integer('a');	
	m["start"] = LEX((m["a"] & 0 * m["_"]) + m["a"], TA_LETTER, "expected letter 'a'", 1);
};


void test7::SetSyntax(lex::Base::Syntax& ref)
{
	const char* p1[]={"a"};
	const int a1[]={TA_LETTER};
	AddAsProduction(ref, p1, a1, 1);
};




void test7::SetReports(lex::Base::Reports& reps)
{
	//{fp= 2 ln=0 col= 2} expected letter 'a' {1} 
	lex::Report rep;
	rep.report(lex::Error("expected letter 'a'", 1), 2, 0, 2);
	reps.push_back(rep);
};



void test7::AddAsProduction(lex::Base::Syntax& ref, const char* p[], const int a[], int lim)
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




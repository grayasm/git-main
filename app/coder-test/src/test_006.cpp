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



#include "test_006.hpp"




void test6::run(const char* test)
{
	test6 obj;
	obj.test_gen::run(test);
};


char* test6::GetText()
{	
	//token AND &
	//the reason behind this 0x4 is that we should not return false unless nothing is to be done.
	//stream: "vocala"
	//m["vocale"] = m["vocala"] & 0 * m["vocala"];   the right of & now will return true for in.eof() and c=0x4


	char* text=
		"vocala";

	return text;
};


void test6::SetGrammar(ebnf::DefaultGrammar::Ptr& grammar)
{
	grammar->SetTerm("endl");
	ebnf::Grammar::Map& m = grammar->GetMap();

	//grammar
	m["vocala"] = LEX(new lex::Quote("vocala"), TA_VOCALA, "expected word: vocala", 1);
	m["vocale"] = m["vocala"] & 0 * m["vocala"]; 
	m["start"] = LEX(m["vocale"], TA_TEXT);
};


void test6::SetSyntax(lex::Base::Syntax& ref)
{
	const char* p1[]={"vocala"};
	const int a1[]={TA_TEXT};
	AddAsProduction(ref, p1, a1, 1);
};


void test6::SetReports(lex::Base::Reports& /*rep*/)
{

};


void test6::AddAsProduction(lex::Base::Syntax& ref, const char* p[], const int a[], int lim)
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




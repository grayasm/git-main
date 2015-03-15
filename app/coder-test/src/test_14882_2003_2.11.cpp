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


#include "test_14882_2003_2.11.hpp"



void test_14882_2003_2_11::run(const char* test)
{
	test_14882_2003_2_11 obj;
	obj.test_gen::run(test);
};


char* test_14882_2003_2_11::GetText()
{	
	char* text=
		"__asm{};\n"
		"auto volatile unsigned long long lval = 10L;\n"		
		;

	return text;
};


void test_14882_2003_2_11::SetGrammar(ebnf::DefaultGrammar::Ptr& grammar)
{
	grammar->SetTerm("endl");
	ebnf::Grammar::Map& m = grammar->GetMap();


	//grammar
	
	m["start"] = m["integer-literal"] && LEX(m[";"], TA_TERMINAL);
};


void test_14882_2003_2_11::SetSyntax(lex::Base::Syntax& ref)
{	

	//decimal
	const char* p1[]={"0",";"};
	const int a1[]={TA_TERMINAL, TA_TERMINAL};

	//decimal
	AddAsProduction(ref, p1, a1, sizeof(p1)/sizeof(p1[0]));
	


};



void test_14882_2003_2_11::SetReports(lex::Base::Reports& /*rep*/)
{

};




void test_14882_2003_2_11::AddAsProduction(lex::Base::Syntax& ref, const char* p[], const int a[], int lim)
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







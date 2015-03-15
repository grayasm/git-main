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



#include "test_024.hpp"



void test24::run(const char* test)
{
	test24 obj;
	obj.test_gen::run(test);
};


char* test24::GetText()
{		
	char* text=		
		""
		;

	return text;
};


void test24::SetGrammar(ebnf::DefaultGrammar::Ptr& grammar)
{
	grammar->SetTerm(";");
	ebnf::Grammar::Map& m = grammar->GetMap();
	//grammar
	m["start"] = m[";"];
};


void test24::SetSyntax(lex::Base::Syntax& /*ref*/)
{	
	//[simple-escape-sequence]
	//const char* p1[]={"012345",";"};
	//const int a1[]={TA_NUMBER, TA_TERMINAL};

	////string literal
	//AddAsProduction(ref, p1, a1, sizeof(p1)/sizeof(p1[0]));
};




void test24::SetReports(lex::Base::Reports& /*reps*/)
{
	
};



void test24::AddAsProduction(lex::Base::Syntax& ref, const char* p[], const int a[], int lim)
{	
	lex::Base::Production prod;	
	for(int i=0; i<lim; ++i)
	{
		lex::Token token;
		token.SetToken(p[i]);
		token.SetAttr(a[i]);


		prod.push_back(token);
	};
	ref.push_back(prod);
};




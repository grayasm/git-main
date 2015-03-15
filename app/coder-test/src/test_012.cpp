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



#include "test_012.hpp"




void test12::run(const char* test)
{
	test12 obj;
	obj.test_gen::run(test);
};


char* test12::GetText()
{	
	//IsNotEq
	//class_  != class = true
	//_class != class = true
	//switch != switch = false

	char* text=
		"class_	Circle\n"
		"_class	Circle\n"
		"class	Circle\n"
		;

	return text;
};


void test12::SetGrammar(ebnf::DefaultGrammar::Ptr& grammar)
{
	grammar->SetTerm("endl");
	ebnf::Grammar::Map& m = grammar->GetMap();	

	//grammar
	m["varname"] = LEX((m["_"] | m["a_zA_Z"]) & 0*(m["_"] | m["a_zA_Z"] | m["0_9"]), TA_VARID, "invalid identifier", 2);
	m["class"] = LEX(new lex::Quote("class"), TA_CLASS, "expected class", 2);
	m["start"] = 
			LEX((m["varname"] != m["class"]), TA_NOT_CLASS, "different than 'class' expected", 1)
		&&	LEX(m["gap"], TA_WS, "expected space", 1)
		&&	LEX(m["varname"], TA_VARNAME, "invalid variable name", 1);
};


void test12::SetSyntax(lex::Base::Syntax& ref)
{	
	const char* p1[]={"class_","\t","Circle"};
	const int a1[]={TA_NOT_CLASS, TA_WS, TA_VARNAME};
	AddAsProduction(ref, p1, a1, sizeof(p1)/sizeof(p1[0]));
	
	
	const char* p2[]={"_class","\t","Circle"};
	const int a2[]={TA_NOT_CLASS, TA_WS, TA_VARNAME};
	AddAsProduction(ref, p2, a2, sizeof(p2)/sizeof(p2[0]));
	//"class	Circle\n"
	
};



void test12::SetReports(lex::Base::Reports& reps)
{
	lex::Report rep[3];
	rep[0].report(lex::Error("invalid identifier", 2), 14, 1, 0);
	rep[0].report(lex::Error("different than 'class' expected", 1), 14, 1, 0);
	rep[1].report(lex::Error("invalid identifier", 2), 28, 2, 0);
	rep[1].report(lex::Error("different than 'class' expected", 1), 28, 2, 0);
	rep[2].report(lex::Error("different than 'class' expected", 1), 33, 2, 5);

	for(int i=0; i<3; ++i)
		reps.push_back(rep[i]);
};


void test12::AddAsProduction(lex::Base::Syntax& ref, const char* p[], const int a[], int lim)
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




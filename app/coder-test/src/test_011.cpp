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



#include "test_011.hpp"




void test11::run(const char* test)
{
	test11 obj;
	obj.test_gen::run(test);
};


char* test11::GetText()
{	
	//IsEq rule
	//class_  == class = false
	//_class == class = false
	//switch == switch = true

	char* text=
		"class_	Circle\n"
		"_class Circle\n"
		"class	Circle\n"
		;

	return text;
};


void test11::SetGrammar(ebnf::DefaultGrammar::Ptr& grammar)
{
	grammar->SetTerm("endl");
	ebnf::Grammar::Map& m = grammar->GetMap();	

	//grammar
	m["varname"] = LEX((m["_"] | m["a_zA_Z"]) & 0*(m["_"] | m["a_zA_Z"] | m["0_9"]), TA_VARID, "invalid token", 2);
	m["class"] = LEX(new lex::Quote("class"), TA_CLASS, "not 'class'", 2);
	m["start"] = 
			LEX((m["varname"] == m["class"]), TA_CLASS, "expect 'class'", 1)
		&&	LEX(m["gap"], TA_WS, "remove space", 1)
		&&	LEX(m["varname"], TA_VARNAME, "not a variable name", 1);
};


void test11::SetSyntax(lex::Base::Syntax& ref)
{	
	//"class_	Circle\n"
	//"_class	Circle\n"
	const char* p1[]={"class","\t","Circle"};
	const int a1[]={TA_CLASS, TA_WS, TA_VARNAME};

	AddAsProduction(ref, p1, a1, sizeof(p1)/sizeof(p1[0]));
};



void test11::SetReports(lex::Base::Reports& reps)
{
	lex::Report rep[3];
	rep[0].report(lex::Error("expect 'class'", 1), 1, 0, 1);
	rep[1].report(lex::Error("not 'class'", 2), 15, 1, 1);
	rep[1].report(lex::Error("expect 'class'", 1), 15, 1, 1);
	rep[2].report(lex::Error("invalid token", 2), 41, 3, 0);
	rep[2].report(lex::Error("expect 'class'", 1), 41, 3, 0);

	for(int i=0; i<3; ++i)
		reps.push_back(rep[i]);
};



void test11::AddAsProduction(lex::Base::Syntax& ref, const char* p[], const int a[], int lim)
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




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



#include "test_14882_2003_2.13.5.hpp"



void test_14882_2003_2_13_5::run(const char* test)
{
	test_14882_2003_2_13_5 obj;
	obj.test_gen::run(test);
};


char* test_14882_2003_2_13_5::GetText()
{	
	char* text=
		"true;\n"
		"false;\n"
		"falsefalse;\n"
		"truefalse;\n"
		"01 true false;\n"
		"true;false;true;false;\n"
		;


	return text;
};


void test_14882_2003_2_13_5::SetGrammar(ebnf::DefaultGrammar::Ptr& grammar)
{
	grammar->SetTerm("endl");
	ebnf::Grammar::Map& m = grammar->GetMap();

	//grammar
	m["false"] = LEX((lex::Base::Ptr)new lex::Quote("false"), TA_BOOLEAN);
	m["true"] = LEX((lex::Base::Ptr) new lex::Quote("true"), TA_BOOLEAN);
	m["boolean-literal"] = m["false"] || m["true"];	
	m["start"] = m["boolean-literal"] && LEX(m[";"], TA_TERMINAL);
};


void test_14882_2003_2_13_5::SetSyntax(lex::Base::Syntax& ref)
{	

	const char* p1[]={"true",";"};
	const char* p2[]={"false",";"};	
	//"falsefalse;\n"
	//"truefalse;\n"
	//"01 true false;\n"	
	const char* p3[]={"true",";"};
	const char* p4[]={"false",";"};
	const char* p5[]={"true",";"};
	const char* p6[]={"false",";"};
	const int a1[]={TA_BOOLEAN,TA_TERMINAL};
	

	//string literal
	AddAsProduction(ref, p1, a1, sizeof(p1)/sizeof(p1[0]));
	AddAsProduction(ref, p2, a1, sizeof(p2)/sizeof(p2[0]));
	AddAsProduction(ref, p3, a1, sizeof(p3)/sizeof(p3[0]));
	AddAsProduction(ref, p4, a1, sizeof(p4)/sizeof(p4[0]));
	AddAsProduction(ref, p5, a1, sizeof(p5)/sizeof(p5[0]));
	AddAsProduction(ref, p6, a1, sizeof(p6)/sizeof(p6[0]));

};



void test_14882_2003_2_13_5::SetReports(lex::Base::Reports& /*rep*/)
{

};



void test_14882_2003_2_13_5::AddAsProduction(lex::Base::Syntax& ref, const char* p[], const int a[], int lim)
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




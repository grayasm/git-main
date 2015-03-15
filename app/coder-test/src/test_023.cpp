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



#include "test_023.hpp"



void test23::run(const char* test)
{
	test23 obj;
	obj.test_gen::run(test);
};


char* test23::GetText()
{	
	char* text=
		"012345;\n"
		"abcdef;\n"
		"012345\n"		
		;

	return text;
};


void test23::SetGrammar(ebnf::DefaultGrammar::Ptr& grammar)
{
	grammar->SetTerm(";");
	ebnf::Grammar::Map& m = grammar->GetMap();

	//grammar
	m["digit"] = LEX((lex::Base::Ptr)new lex::Range('0', '9'), TA_DIGIT, "not a digit", 2);
	m["number"] = m["digit"] & 0 * m["digit"];
	m["start"] = 
		~m["gaps"] &&
		LEX(m["number"], TA_NUMBER, "expected a decimal number", 1) &&
		LEX(m[";"], TA_TERMINAL, "expected ;", 1) ;



};


void test23::SetSyntax(lex::Base::Syntax& ref)
{		
	//[simple-escape-sequence]
	const char* p1[]={"012345",";"};
	const int a1[]={TA_NUMBER, TA_TERMINAL};

	//string literal
	AddAsProduction(ref, p1, a1, sizeof(p1)/sizeof(p1[0]));
};




void test23::SetReports(lex::Base::Reports& reps)
{
	lex::Report rep[2];

	rep[0].report(lex::Error("not a digit", 2), 9, 1, 1);
	rep[0].report(lex::Error("expected a decimal number", 1), 9, 1, 1);
	reps.push_back(rep[0]);
	
	rep[1].report(lex::Error("expected ;", 1), 23, 3, 0);
	reps.push_back(rep[1]);
};



void test23::AddAsProduction(lex::Base::Syntax& ref, const char* p[], const int a[], int lim)
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




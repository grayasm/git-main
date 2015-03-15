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



#include "test_003.hpp"




void test3::run(const char* test)
{
	test3 obj;
	obj.test_gen::run(test);
};


char* test3::GetText()
{
	//token AND &
	char* text=
		"automobil\n"
		"autom0bil\n"
		"@utomobil\n"
		"AuToMoBiL\n"
		"AUTOMOBIL\n"
		"Aut0mob1l\n"
		"autoMOBI1\n"
		"_utomobi_";
	return text;
};


void test3::SetGrammar(ebnf::DefaultGrammar::Ptr& grammar)
{
	grammar->SetTerm("endl");
	ebnf::Grammar::Map& m = grammar->GetMap();
	m["letter"] = LEX(0*m["a_zA_Z"], TA_LETTER, "not a letter", 1);
	m["new-line"] = LEX(m["endl"], TA_END_RULE, "expected new line", 1);
	m["start"] = LEX(m["letter"] & m["new-line"], TA_TEXT, "syntax not ok", 1);
};


void test3::SetSyntax(lex::Base::Syntax& ref)
{
	char* p[] = 
	{
		"automobil\n",
		//"autom0bil\n",
		//"@utomobil\n",
		"AuToMoBiL\n",
		"AUTOMOBIL\n"
		//"Aut0mob1l\n"
		//"autoMOBI1\n"
		//"_utomobi_"
	};

	int a[]=
	{
		TA_TEXT,
		TA_TEXT,
		TA_TEXT
	};

	lex::Base::Production prod;
	ref.clear();
	int lim = sizeof(p)/sizeof(p[0]);
	for(int i=0; i<lim; ++i)
	{
		lex::Token token;
		token.SetToken(p[i]);
		token.SetAttr(a[i]);

		prod.push_back(token);
		ref.push_back(prod);
		prod.clear();
	};	
};



void test3::SetReports(lex::Base::Reports& reps)
{
	
	lex::Report rep[5];
	rep[0].report(lex::Error("expected new line", 1), 16, 1, 6);
	rep[1].report(lex::Error("expected new line", 1), 21, 2, 1);
	rep[2].report(lex::Error("expected new line", 1), 54, 5, 4);
	rep[3].report(lex::Error("expected new line", 1), 69, 6, 9);
	rep[4].report(lex::Error("expected new line", 1), 71, 7, 1);

	for(int i=0; i<5; ++i)
		reps.push_back(rep[i]);
};


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



#include "test_002.hpp"




void test2::run(const char* test)
{
	test2 obj;
	obj.test_gen::run(test);
};


char* test2::GetText()
{
	//Only token rule
	char* text=
		"anatomic"
		"anatomic"
		"anatomic"
		"anatomic";

	return text;
};


void test2::SetGrammar(ebnf::DefaultGrammar::Ptr& grammar)
{
	grammar->SetTerm("endl");
	ebnf::Grammar::Map& m = grammar->GetMap();
	m["start"] = LEX(0*m["a_zA_Z"], A_TEXT, "not a letter", 1);
};


void test2::SetSyntax(lex::Base::Syntax& ref)
{
	char* p[] = 
	{
		"anatomicanatomicanatomicanatomic" 
	};

	int attribute[]={A_TEXT};

	lex::Base::Production prod;
	ref.clear();
	int lim = sizeof(p)/sizeof(p[0]);
	for(int i=0; i<lim; ++i)
	{
		lex::Token token;
		token.SetToken(p[i]);
		token.SetAttr(attribute[i]);		

		prod.push_back(token);
		ref.push_back(prod);
		prod.clear();
	};	
};



void test2::SetReports(lex::Base::Reports& /*rep*/)
{

};



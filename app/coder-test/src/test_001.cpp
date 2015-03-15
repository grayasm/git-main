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



#include "test_001.hpp"




void test1::run(const char* test)
{
	test1 obj;
	obj.test_gen::run(test);
};



char* test1::GetText()
{
	//Token rule, but empty file/stream.
	char* text="";//nothing
	return text;
};


void test1::SetGrammar(ebnf::DefaultGrammar::Ptr& grammar)
{
	grammar->SetTerm(";");
	ebnf::Grammar::Map& m = grammar->GetMap();
	m["letters"] =  0 * m["a_zA_Z"];
	m["start"] = LEX(m["letters"], TA_LETTER, "not a letter", 1);
};


void test1::SetSyntax(lex::Base::Syntax& ref)
{
	char* p[] = { " " };//dummy, not pushed into syntax;
	lex::Token t1;
	t1.SetToken(p[0]);

	lex::Base::Production prod;
	ref.clear();
	//int lim = sizeof(p)/sizeof(p[0]);
	prod.push_back(t1);
	//ref.push_back(prod);//nothing in syntax (empty file)
	prod.clear();	
};


void test1::SetReports(lex::Base::Reports& /*rep*/)
{

};




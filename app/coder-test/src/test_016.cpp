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



#include "test_016.hpp"



void test16::run(const char* test)
{
	test16 obj;
	obj.test_gen::run(test);
};


char* test16::GetText()
{	
	//Repetition rule
	//3*([ long ] & [space]) && [gaps] && [Circle] && [gaps] && [varname]

/*
	"long \n"
	"long long \n"
	"long long long\n"
	"long long long Circle __circle\n"
	"long Long LONG Circle __circle\n"
	"long lonG long Circle __circle\n"
	"Long long long Circle __circle\n"
	"long long long \tCircle __circle\n"
	"long long long long long\n"
*/

	char* text=
		"long \n"
		"long long \n"
		"long long long\n"
		"long long long Circle __circle\n"
		"long Long LONG Circle __circle\n"
		"long lonG long Circle __circle\n"
		"Long long long Circle __circle\n"
		"long long long \tCircle __circle\n"
		"long long long long long\n"
		;

	return text;
};


void test16::SetGrammar(ebnf::DefaultGrammar::Ptr& grammar)
{
	grammar->SetTerm("endl");
	ebnf::Grammar::Map& m = grammar->GetMap();

	//grammar	
	m["varname"] = LEX((m["_"] | m["a_zA_Z"]) & 0*(m["_"] | m["a_zA_Z"] | m["0_9"]), TA_VARID, "invalid token", 2);
	m["long"] = LEX(new lex::Quote("long"), TA_LONG, "expected 'long'", 2);
	m["Circle"] = LEX(new lex::Quote("Circle"), TA_CIRCLE, "expected 'Circle'", 2);
	m["start"] = 
			LEX(3*(m["long"] & m["space"]), TA_EXPRESSION, "not an expression", 1)
		&&	LEX(m["gaps"], TA_WS, "need white space", 1)
		&&	LEX(m["Circle"], TA_CIRCLE)
		&&	LEX(m["gaps"], TA_WS, "need white space", 1)
		&&	LEX(m["varname"], TA_VARNAME, "expected a variable name", 1);
};


void test16::SetSyntax(lex::Base::Syntax& ref)
{	
	//"long \n"
	//"long long \n"
	//"long long long\n"
	//"long long long Circle __circle\n"
	const char* p1[]={"long long long ","Circle"," ", "__circle"};
	const int a1[]={TA_EXPRESSION, TA_CIRCLE, TA_WS, TA_VARNAME};
	AddAsProduction(ref, p1, a1, sizeof(p1)/sizeof(p1[0]));	

	//"long Long LONG Circle __circle\n"
	//"long lonG long Circle __circle\n"
	//"Long long long Circle __circle\n"
	//"long long long \tCircle __circle\n"
	const char* p2[]={"long long long ","\t","Circle"," ","__circle"};
	const int a2[]={TA_EXPRESSION, TA_WS, TA_CIRCLE, TA_WS, TA_VARNAME};
	AddAsProduction(ref, p2, a2, sizeof(p2)/sizeof(p2[0]));	

	//"long long long long long\n"

};



void test16::SetReports(lex::Base::Reports& reps)
{
	lex::Report rep[9];
	rep[0].report(lex::Error("expected 'long'", 2), 6, 1, 0);
	rep[0].report(lex::Error("not an expression", 1), 6, 1, 0);
	rep[1].report(lex::Error("expected 'long'", 2), 17, 2, 0);
	rep[1].report(lex::Error("not an expression", 1), 17, 2, 0);
	rep[2].report(lex::Error("not an expression", 1), 28, 2, 11);
	rep[3].report(lex::Error("expected 'long'", 2), 63, 4, 0);
	rep[3].report(lex::Error("not an expression", 1), 63, 4, 0);
	rep[4].report(lex::Error("expected 'long'", 2), 69, 4, 6);
	rep[4].report(lex::Error("not an expression", 1), 69, 4, 6);
	rep[5].report(lex::Error("expected 'long'", 2), 103, 5, 9);
	rep[5].report(lex::Error("not an expression", 1), 103, 5, 9);
	rep[6].report(lex::Error("expected 'long'", 2), 126, 6, 1);
	rep[6].report(lex::Error("not an expression", 1), 126, 6, 1);
	rep[7].report(lex::Error("expected 'long'", 2), 188, 8, 0);
	rep[7].report(lex::Error("not an expression", 1), 188, 8, 0);
	rep[8].report(lex::Error("expected 'Circle'", 2), 204, 8, 16);

	for(int i=0; i<9; ++i)
		reps.push_back(rep[i]);
};



void test16::AddAsProduction(lex::Base::Syntax& ref, const char* p[], const int a[], int lim)
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




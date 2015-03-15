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



#include "test_018.hpp"



void test18::run(const char* test)
{
	test18 obj;
	obj.test_gen::run(test);
};


char* test18::GetText()
{	
	//RepeatRange {1,3} * ([long] && [gaps]) && ( [Circle] || [varname] ) && [;] ;

	char* text=
		"long ;\n"
		"long long ;\n"
		"long long long ;\n"
		"long long long Circle;\n"
		"long Long LONG __circle;\n"
		"long lonG long __circle;\n"
		"Long long long __circle;\n"
		"long long long \t__circle;\n"
		"long long long long;\n"
		;

	return text;
};


void test18::SetGrammar(ebnf::DefaultGrammar::Ptr& grammar)
{
	grammar->SetTerm("endl");
	ebnf::Grammar::Map& m = grammar->GetMap();

	//grammar	
	//{1,3} * ([long] && [gaps]) && ( [Circle] || [varname] ) && [;] ;
	m["long"] = LEX(new lex::Quote("long"), TA_LONG, "expected 'long'", 2);
	m["p1"] = 
			LEX(m["long"], TA_LONG) 
		&&	LEX(m["gaps"], TA_WS, "expected white space", 2);

	m["varname"] = LEX((m["_"] | m["a_zA_Z"]) & 0*(m["_"] | m["a_zA_Z"] | m["0_9"]), TA_VARID, "invalid token", 2);
	m["Circle"] = LEX(new lex::Quote("Circle"), TA_CIRCLE, "expected 'Circle'", 1);
	m["start"] = 
			LEX(RR(1,3,m["p1"]), TA_LONG, "expected 1 to 3 times 'long'", 1)
		&&	(
				LEX(m["Circle"], TA_CIRCLE)
			||	LEX(m["varname"], TA_VARNAME, "not a variable name", 1)
			) 
		&&	LEX(m[";"], TA_TERMINAL, "expected ;", 1);
};


void test18::SetSyntax(lex::Base::Syntax& ref)
{	
	//"long \n"
	//"long long \n"
	//"long long long \n"	
	const char* p1[]={"long"," ","long"," ","long"," ","Circle",";"};
	const int a1[]={TA_LONG, TA_WS, TA_LONG, TA_WS, TA_LONG, TA_WS, TA_CIRCLE, TA_TERMINAL};
	AddAsProduction(ref, p1, a1, sizeof(p1)/sizeof(p1[0]));	
	//"long Long LONG __circle\n"
	//"long lonG long __circle\n"
	//"Long long long __circle\n"
	//"long long long \t__circle\n"
	const char* p2[]={"long"," ","long"," ","long"," \t","__circle",";"};
	const int a2[]={TA_LONG, TA_WS, TA_LONG, TA_WS, TA_LONG, TA_WS, TA_VARNAME, TA_TERMINAL};
	AddAsProduction(ref, p2, a2, sizeof(p2)/sizeof(p2[0]));	


	const char* p3[]={"long"," ","long"," ","long"," ","long",";"};
	const int a3[]={TA_LONG, TA_WS, TA_LONG, TA_WS, TA_LONG, TA_WS, TA_VARNAME, TA_TERMINAL};
	AddAsProduction(ref, p3, a3, sizeof(p3)/sizeof(p3[0]));	

};



void test18::SetReports(lex::Base::Reports& reps)
{
	lex::Report rep[9];
	rep[0].report(lex::Error("expected 'Circle'", 1), 6, 0, 6);
	rep[1].report(lex::Error("expected 'Circle'", 1), 18, 1, 11);
	rep[2].report(lex::Error("expected 'Circle'", 1), 35, 2, 16);
	rep[3].report(lex::Error("expected 'long'", 2), 59, 4, 0);
	rep[3].report(lex::Error("expected 1 to 3 times 'long'", 1), 59, 4, 0);
	rep[4].report(lex::Error("expected ;", 1), 69, 4, 10);
	rep[5].report(lex::Error("expected ;", 1), 94, 5, 10);
	rep[6].report(lex::Error("expected 'long'", 2), 110, 6, 1);
	rep[6].report(lex::Error("expected 1 to 3 times 'long'", 1), 110, 6, 1);
	rep[7].report(lex::Error("expected 'long'", 2), 160, 8, 0);
	rep[7].report(lex::Error("expected 1 to 3 times 'long'", 1), 160, 8, 0);
	rep[8].report(lex::Error("expected 'long'", 2), 181, 9, 0);
	rep[8].report(lex::Error("expected 1 to 3 times 'long'", 1), 181, 9, 0);

	for(int i=0; i<9; ++i)
		reps.push_back(rep[i]);
};



void test18::AddAsProduction(lex::Base::Syntax& ref, const char* p[], const int a[], int lim)
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




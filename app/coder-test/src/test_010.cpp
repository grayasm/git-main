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



#include "test_010.hpp"




void test10::run(const char* test)
{
	test10 obj;
	obj.test_gen::run(test);
};


char* test10::GetText()
{	
	//HasNot rule
	//HasNot operator -(lex::Base::Ptr, lex::Base::Ptr)
	//stream: "int_0x ;"  rule: m["varname"] - m["auto"], inf2 eof is "int_0x[ ];" (the space)
	//m_right parsed entire inf1 including eof although it did not verified any rule with it.
	//[ ] must be pushed back into the stream or else next parse will start with [;]


	char* text=
		"int_0x ;\n"
		"m00x_2 ;\n"
		"______ ;\n"
		"xx _x ;\n"
		"?_ )? ;\n"
		" _ _ ?;\n"
		"___x_xpp__000cmd ;\n"
		;

	return text;
};


void test10::SetGrammar(ebnf::DefaultGrammar::Ptr& grammar)
{
	grammar->SetTerm("endl");
	ebnf::Grammar::Map& m = grammar->GetMap();	

	//grammar
	m["varname"] = LEX((m["_"] | m["a_zA_Z"]) & 0*(m["_"] | m["a_zA_Z"] | m["0_9"]), TA_VARNAME, "invalid identifier", 2);
	m["auto"] = LEX(new lex::Quote("auto"), TA_AUTO, "expected 'auto'", 1);
	m["start"] = 
			LEX((m["varname"] - m["auto"]), TA_VARNAME, "invalid variable name", 1)
		&&	LEX(m["gap"], TA_WS, "remove white space", 1)
		&&	LEX(m[";"], TA_TERMINAL, "expected ;", 1);
};


void test10::SetSyntax(lex::Base::Syntax& ref)
{

	const char* p1[]={"int_0x"," ",";"};
	const int a1[]={TA_VARNAME, TA_WS, TA_TERMINAL};
	AddAsProduction(ref, p1, a1, sizeof(p1)/sizeof(p1[0]));

	const char* p2[]={"m00x_2"," ",";"};
	const int a2[]={TA_VARNAME, TA_WS, TA_TERMINAL};
	AddAsProduction(ref, p2, a2, sizeof(p2)/sizeof(p2[0]));

	const char* p3[]={"______"," ",";"};
	const int a3[]={TA_VARNAME, TA_WS, TA_TERMINAL};
	AddAsProduction(ref, p3, a3, sizeof(p3)/sizeof(p3[0]));

	//"xx _x ;\n"
	//"?_ )? ;\n"
	//" _ _ ?;\n"
	const char* p4[]={"___x_xpp__000cmd"," ",";"};
	const int a4[]={TA_VARNAME, TA_WS, TA_TERMINAL};
	AddAsProduction(ref, p4, a4, sizeof(p4)/sizeof(p4[0]));

};



void test10::SetReports(lex::Base::Reports& reps)
{
	lex::Report rep[7];
	rep[0].report(lex::Error("invalid identifier", 2), 9, 1, 0);
	rep[0].report(lex::Error("invalid variable name", 1), 9, 1, 0);
	rep[1].report(lex::Error("invalid identifier", 2), 18, 2, 0);
	rep[1].report(lex::Error("invalid variable name", 1), 18, 2, 0);
	rep[2].report(lex::Error("invalid identifier", 2), 27, 3, 0);
	rep[2].report(lex::Error("invalid variable name", 1), 27, 3, 0);
	rep[3].report(lex::Error("expected ;", 1), 31, 3, 4);
	rep[4].report(lex::Error("invalid identifier", 2), 36, 4, 1);
	rep[4].report(lex::Error("invalid variable name", 1), 36, 4, 1);
	rep[5].report(lex::Error("invalid identifier", 2), 44, 5, 1);
	rep[5].report(lex::Error("invalid variable name", 1), 44, 5, 1);
	rep[6].report(lex::Error("invalid identifier", 2), 70, 7, 0);
	rep[6].report(lex::Error("invalid variable name", 1), 70, 7, 0);


	for(int i=0; i<7; ++i)
		reps.push_back(rep[i]);
};



void test10::AddAsProduction(lex::Base::Syntax& ref, const char* p[], const int a[], int lim)
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




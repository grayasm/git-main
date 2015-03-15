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



#include "test_008.hpp"




void test8::run(const char* test)
{
	test8 obj;
	obj.test_gen::run(test);
};


char* test8::GetText()
{	
	//Has operator + (lex::Base::Ptr, lex::Base::Ptr)
	//stream: "auto91v", rule:  m["varname"] + m["auto"], inf3 sets eof on auto[9]1v
	//m_left consumes eof [9] but does not check for it, simply returns true for "varname"
	//[9] must be pushed back into the stream or else next parse will start with [1]
	//if inf3 did not advance nothing should be pushed back

	//+ last string for:
	//stream: "auto ;"  rule: m["varname"] + m["auto"], inf2 eof is "auto[ ];" (the space)
	//m_right parsed entire inf1 including eof although it did not verified any rule with it.
	//[ ] must be pushed back into the stream or else next parse will start with [;]


	char* text=
		"auto91v\n"
		"auto??@\n"
		"auto~ 33\n"
		"auto\n"
		"auto\t00\n"
		"auto ;\n"
		;

	return text;
};


void test8::SetGrammar(ebnf::DefaultGrammar::Ptr& grammar)
{
	grammar->SetTerm("endl");
	ebnf::Grammar::Map& m = grammar->GetMap();	
	
	//grammar
	m["varname"] = (m["_"] | m["a_zA_Z"]) & 0*(m["_"] | m["a_zA_Z"] | m["0_9"]);
	m["auto"] = new lex::Quote("auto");
	m["no-ws"] = 0 * (m["0_9"] | m["a_zA_Z"] | (m["other"] - m["gap"]));

	m["start"] = 
			LEX((m["varname"] + m["auto"]), TA_AUTO, "expected identifier 'auto'", 1)
		&&	LEX(m["no-ws"], TA_OTHER_NO_WS, "white space not expected", 1) ;
};


void test8::SetSyntax(lex::Base::Syntax& ref)
{

	const char* p1[]={"auto","91v"};
	const int a1[]={TA_AUTO, TA_OTHER_NO_WS};
	AddAsProduction(ref, p1, a1, sizeof(p1)/sizeof(p1[0]));


	const char* p2[]={"auto","??@"};
	const int a2[]={TA_AUTO, TA_OTHER_NO_WS};
	AddAsProduction(ref, p2, a2, sizeof(p2)/sizeof(p2[0]));


	const char* p3[]={"auto","~"};
	const int a3[]={TA_AUTO, TA_OTHER_NO_WS};
	AddAsProduction(ref, p3, a3, sizeof(p3)/sizeof(p3[0]));

	const char* p4[]={"auto"};
	const int a4[]={TA_AUTO};
	AddAsProduction(ref, p4, a4, sizeof(p4)/sizeof(p4[0]));

	const char* p5[]={"auto"};
	const int a5[]={TA_AUTO};
	AddAsProduction(ref, p5, a5, sizeof(p5)/sizeof(p5[0]));

	const char* p6[]={"auto"};
	const int a6[]={TA_AUTO};
	AddAsProduction(ref, p6, a6, sizeof(p6)/sizeof(p6[0]));

};




void test8::SetReports(lex::Base::Reports& reps)
{	
	lex::Report rep[6];
	rep[0].report(lex::Error("expected identifier 'auto'", 1), 8, 1, 0);
	rep[1].report(lex::Error("expected identifier 'auto'", 1), 16, 2, 0);
	rep[2].report(lex::Error("expected identifier 'auto'", 1), 22, 2, 6);
	rep[3].report(lex::Error("expected identifier 'auto'", 1), 30, 4, 0);
	rep[4].report(lex::Error("expected identifier 'auto'", 1), 35, 4, 8);
	rep[5].report(lex::Error("expected identifier 'auto'", 1), 43, 5, 5);

	for(int i=0; i<6; ++i)
		reps.push_back(rep[i]);
};



void test8::AddAsProduction(lex::Base::Syntax& ref, const char* p[], const int a[], int lim)
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




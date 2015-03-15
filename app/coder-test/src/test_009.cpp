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



#include "test_009.hpp"




void test9::run(const char* test)
{
	test9 obj;
	obj.test_gen::run(test);
};


char* test9::GetText()
{	
	//HasNot operator -(lex::Base::Ptr, lex::Base::Ptr)
	//stream: "v01auto", rule:  m["varname"] - m["auto"], inf3 sets eof on v01[a]uto
	//m_left consumes eof [a] but does not check for it, simply returns true for "varname"
	//[a] must be pushed back into the stream or else next parse will start with [u]
	//in other cases (e.g. "a[a]utom3@;") m_left validates only current position without advancing inf3 stream;
	//in this nothing should be pushed back


	char* text=
		"v01auto\n"
		"v22_?auto\n"
		"auto\n"
		"xauto\n"
		"01auto\n"
		"aautom3@\n"
		"auto v x\n"
		"xdistrict_09999auto\n"
		;

	return text;
};


void test9::SetGrammar(ebnf::DefaultGrammar::Ptr& grammar)
{
	grammar->SetTerm("endl");
	ebnf::Grammar::Map& m = grammar->GetMap();	

	//grammar
	m["varbeg"] = LEX(m["_"] | m["a_zA_Z"], TA_VARNAME, "expected: _ a-z A-Z", 2);
	m["varid"] = LEX(0*(m["_"] | m["a_zA_Z"] | m["0_9"]), TA_VARNAME, "expected: _ a-z A-Z 0-9", 2);
	m["varname"] = m["varbeg"] & m["varid"];

	m["auto"] = new lex::Quote("auto");	
	m["non-ws"] = LEX(m["0_9"] | m["a_zA_Z"] | (m["other"] - m["gap"]), TA_OTHER_NO_WS, "remove white spaces", 1);

	m["start"] = 
			LEX((m["varname"] - m["auto"]), TA_NOT_AUTO, "anything but 'auto'", 1)
		&&	LEX(m["auto"], TA_AUTO, "only word 'auto'", 1)
		&&	LEX(0 * m["non-ws"], TA_OTHER_NO_WS) ;
};


void test9::SetSyntax(lex::Base::Syntax& ref)
{

	const char* p1[]={"v01","auto"};
	const int a1[]={TA_NOT_AUTO, TA_AUTO};
	//"v22_?auto\n"
	//"auto\n"
	const char* p2[]={"x","auto"};
	const int a2[]={TA_NOT_AUTO, TA_AUTO};
	//"01auto\n"
	const char* p3[]={"a","auto","m3@"};
	const int a3[]={TA_NOT_AUTO, TA_AUTO, TA_OTHER_NO_WS};
	//"auto v x\n"
	const char* p4[]={"xdistrict_09999","auto"};
	const int a4[]={TA_NOT_AUTO, TA_AUTO};


	AddAsProduction(ref, p1, a1, sizeof(p1)/sizeof(p1[0]));
	AddAsProduction(ref, p2, a2, sizeof(p2)/sizeof(p2[0]));
	AddAsProduction(ref, p3, a3, sizeof(p3)/sizeof(p3[0]));
	AddAsProduction(ref, p4, a4, sizeof(p4)/sizeof(p4[0]));

};



void test9::SetReports(lex::Base::Reports& reps)
{	
	lex::Report rep[8];
	rep[0].report(lex::Error("expected: _ a-z A-Z", 2), 8, 1, 0);
	rep[0].report(lex::Error("anything but 'auto'", 1), 8, 1, 0);
	rep[1].report(lex::Error("only word 'auto'", 1), 13, 1, 5);
	rep[2].report(lex::Error("anything but 'auto'", 1), 22, 2, 4);
	rep[3].report(lex::Error("expected: _ a-z A-Z", 2), 29, 4, 0);
	rep[3].report(lex::Error("anything but 'auto'", 1), 29, 4, 0);
	rep[4].report(lex::Error("expected: _ a-z A-Z", 2), 30, 4, 1);
	rep[4].report(lex::Error("anything but 'auto'", 1), 30, 4, 1);	
	rep[5].report(lex::Error("expected: _ a-z A-Z", 2), 45, 6, 0);
	rep[5].report(lex::Error("anything but 'auto'", 1), 45, 6, 0);
	rep[6].report(lex::Error("anything but 'auto'", 1), 49, 6, 4);
	rep[7].report(lex::Error("expected: _ a-z A-Z", 2), 74, 8, 0);
	rep[7].report(lex::Error("anything but 'auto'", 1), 74, 8, 0);
	
	
	for(int i=0; i<8; i++)
		reps.push_back(rep[i]);
};



void test9::AddAsProduction(lex::Base::Syntax& ref, const char* p[], const int a[], int lim)
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




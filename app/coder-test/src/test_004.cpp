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



#include "test_004.hpp"




void test4::run(const char* test)
{
	test4 obj;
	obj.test_gen::run(test);
};


char* test4::GetText()
{
	//Stream AND && and Stream OR ||
	char* text=
		"x + y\n"
		"\tAddition. \n"
		"x - y\n"
		"\tSubtraction. \n"
		"- x\n"
		"\tNegation. \n"
		"+ x\n"
		"\tUnary plus.\n"
		"x * y\n"
		"\tMultiplication. \n"
		"x / y\n"
		"\tDivision.\n"
		"x % y\n"
		"\tRemainder.\n"
		"b * int(a / b) + (a % b) == a\n"
		"-17 % 8 = -1\n"
		"x ^ y\n"
		"x ** y\n"
		;

	return text;
};


void test4::SetGrammar(ebnf::DefaultGrammar::Ptr& grammar)
{
	grammar->SetTerm("endl");
	ebnf::Grammar::Map& m = grammar->GetMap();

	//tokens
	m["Addition"] = new lex::Quote("Addition");
	m["Subtraction"] = new lex::Quote("Subtraction");
	m["Negation"] = new lex::Quote("Negation");
	m["Unary plus"] = new lex::Quote("Unary plus");
	m["Multiplication"] = new lex::Quote("Multiplication");
	m["Division"] = new lex::Quote("Division");
	m["Remainder"] = new lex::Quote("Remainder");

	m["token"] = 
		    LEX(m["gaps"], A_WS, "expected white space", 1) 
		&& 
		(
			LEX(m["Addition"], A_TEXT, "expected \"Addition\"", 1)
		||	LEX(m["Subtraction"], A_TEXT, "expected \"Subtraction\"", 1)
		||	LEX(m["Negation"], A_TEXT, "expected \"Negation\"", 1)
		||	LEX(m["Unary plus"], A_TEXT, "expected \"Unary plus\"", 1)
		||	LEX(m["Multiplication"], A_TEXT, "expected \"Multiplication\"", 1)
		||	LEX(m["Division"], A_TEXT, "expected \"Division\"", 1)
		||	LEX(m["Remainder"], A_TEXT, "expected \"Remainder\"", 1)
		)
		;

	m["**"] = m["*"] & m["*"];
	//expressions (simple ones)
	m["expr"] =		
				LEX(m["a_zA_Z"], A_IDENTIFIER, "not a char literal: a-z or A-Z", 1)
		&&		LEX(m["gaps"], A_WS, "white space expected", 1)
		&& (
				LEX(m["+"], A_PLUS, "expected arithmetic operator +", 1)
			||	LEX(m["-"], A_MINUS, "expected arithmetic operator -", 1)
			||	LEX(m["**"], A_POWER, "expected arithmetic operator **", 1) 
			||	LEX(m["*"], A_MULTIPLICATION, "expected arithmetic operator *", 1)
			||	LEX(m["/"], A_DIVIZION, "expected arithmetic operator /", 1)
			||	LEX(m["%"], A_REMAINDER, "expected arithmetic operator %", 1)
			||	LEX(m["^"], A_XOR, "expected arithmetic operator ^", 1)
			)
		&&		LEX(m["gaps"], A_WS, "expected white space", 1)
		&&		LEX(m["a_zA_Z"], A_IDENTIFIER, "not a char literal: a-z or A-Z", 1)
		&&		LEX(m["endl"], A_TERMINATOR, "new line expected", 1);

	m["start"] = m["expr"] || m["token"];
};


void test4::SetSyntax(lex::Base::Syntax& ref)
{
		
	const char* p1[]={"x"," ","+"," ","y","\n"};
	const int a1[]={A_IDENTIFIER, A_WS, A_PLUS, A_WS, A_IDENTIFIER, A_TERMINATOR};
	AddAsProduction(ref, p1, a1, 6);

	const char* p2[]={"\t","Addition"};
	const int a2[]={A_WS, A_TEXT};
	AddAsProduction(ref, p2, a2, 2);

	const char* p3[]={"x"," ","-"," ","y","\n"};
	const int a3[]={A_IDENTIFIER, A_WS, A_MINUS, A_WS, A_IDENTIFIER, A_TERMINATOR};
	AddAsProduction(ref, p3, a3, 6);


	const char* p4[]={"\t","Subtraction"};
	const int a4[]={A_WS, A_TEXT};
	AddAsProduction(ref, p4, a4, 2);
	//"- x\n"
	const char* p5[]={"\t","Negation"};
	const int a5[]={A_WS, A_TEXT};
	AddAsProduction(ref, p5, a5, 2);
	//"+ x\n"
	const char* p6[]={"\t","Unary plus"};
	const int a6[]={A_WS, A_TEXT};
	AddAsProduction(ref, p6, a6, 2);

	const char* p7[]={"x"," ","*"," ","y","\n"};
	const int a7[]={A_IDENTIFIER, A_WS, A_MULTIPLICATION, A_WS, A_IDENTIFIER, A_TERMINATOR};
	AddAsProduction(ref, p7, a7, 6);

	const char* p8[]={"\t","Multiplication"};
	const int a8[]={A_WS, A_TEXT};
	AddAsProduction(ref, p8, a8, 2);

	const char* p9[]={"x"," ","/"," ","y","\n"};
	const int a9[]={A_IDENTIFIER, A_WS, A_DIVIZION, A_WS, A_IDENTIFIER, A_TERMINATOR};
	AddAsProduction(ref, p9, a9, 6);

	const char* p10[]={"\t","Division"};
	const int a10[]={A_WS, A_TEXT};
	AddAsProduction(ref, p10, a10, 2);

	const char* p11[]={"x"," ","%"," ","y","\n"};
	const int a11[]={A_IDENTIFIER, A_WS, A_REMAINDER, A_WS, A_IDENTIFIER, A_TERMINATOR};
	AddAsProduction(ref, p11, a11, 6);

	const char* p12[]={"\t","Remainder"};
	const int a12[]={A_WS, A_TEXT};
	AddAsProduction(ref, p12, a12, 2);

	//"b * int(a / b) + (a % b) == a\n"
	//"-17 % 8 = -1\n"
	const char* p13[]={"x"," ","^"," ","y","\n"};
	const int a13[]={A_IDENTIFIER, A_WS, A_XOR, A_WS, A_IDENTIFIER, A_TERMINATOR};
	AddAsProduction(ref, p13, a13, 6);

	const char* p14[]={"x"," ","**"," ","y","\n"};
	const int a14[]={A_IDENTIFIER, A_WS, A_POWER, A_WS, A_IDENTIFIER, A_TERMINATOR};
	AddAsProduction(ref, p14, a14, 6);
};



void test4::SetReports(lex::Base::Reports& reps)
{
	lex::Report rep[11];
	rep[0].report(lex::Error("not a char literal: a-z or A-Z", 1), 16, 1, 13);
	rep[1].report(lex::Error("not a char literal: a-z or A-Z", 1), 37, 3, 16);
	rep[2].report(lex::Error("not a char literal: a-z or A-Z", 1), 40, 4, 1);
	rep[3].report(lex::Error("not a char literal: a-z or A-Z", 1), 53, 5, 13);
	rep[4].report(lex::Error("not a char literal: a-z or A-Z", 1), 56, 6, 1);
	rep[5].report(lex::Error("not a char literal: a-z or A-Z", 1), 71, 7, 15);
	rep[6].report(lex::Error("not a char literal: a-z or A-Z", 1), 94, 9, 19);
	rep[7].report(lex::Error("not a char literal: a-z or A-Z", 1), 112, 11, 13);
	rep[8].report(lex::Error("not a char literal: a-z or A-Z", 1), 130, 13, 14);
	rep[9].report(lex::Error("new line expected", 1), 137, 14, 6);
	rep[10].report(lex::Error("not a char literal: a-z or A-Z", 1), 162, 15, 1);

	for(int i=0; i<11; ++i)
		reps.push_back(rep[i]);
};


void test4::AddAsProduction(lex::Base::Syntax& ref, const char* p[], const int a[], int lim)
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




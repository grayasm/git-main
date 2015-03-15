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



#include "test_999.hpp"



void test999::run(const char* test)
{
	test999 obj;
	obj.test_gen::run(test, true);
};


char* test999::GetText()
{	/*
		[floating-literal]
		(error corrected in Optional: in << 1)

		rule composition:
		m["fractional-constant"] = 
			(OP(m["digit-sequence"]) & m["."] & m["digit-sequence"]) |
			(m["digit-sequence"] & m["."])
			;

		///rule above requires '|' instead of '||' due to next rule's composition:   m["fractional-constant"] & OP(...) ..
		///((a & b & c) || (d & b)) & e & f    :ambiguous

		m["floating-literal"] =
			(m["fractional-constant"] & OP(m["exponent-part"]) & OP(m["floating-suffix"])) ||
			(m["digit-sequence"] & m["exponent-part"] & OP(m["floating-suffix"]))
			;

	*/
	char* text=	
		"1.2eE+1F;\n"
		;

	return text;
};


void test999::SetGrammar(ebnf::DefaultGrammar::Ptr& grammar)
{
	grammar->SetTerm("endl");
	ebnf::Grammar::Map& m = grammar->GetMap();

	//grammar

	//[digit]: 
	//one of
	//	0 1 2 3 4 5 6 7 8 9
	m["digit"] = LEX(m["0_9"], TA_DIGIT);

	//	[digit-sequence]:
	//digit
	//digit-sequence digit
	m["digit-sequence"] = 
			LEX(
			m["digit"] & 0*m["digit"],
			TA_DECIMAL, "expected digits", 1);


	//	[fractional-constant]:
	//digit-sequence[opt] . digit-sequence
	//digit-sequence .
	m["fractional-constant"] = 
		LEX(
		(OP(m["digit-sequence"]) & m["."] & m["digit-sequence"]) |
		(m["digit-sequence"] & m["."])
		, TA_FRACTIONAL, "fractional constant not ok", 1)
		;


	m["e"] = LEX(new lex::Integer('e'), TA_EXPONENT, "expected 'e'", 2);
	m["E"] = LEX(new lex::Integer('E'), TA_EXPONENT, "expected 'E'", 2);
	//	[exponent-part]:
	//e sign[opt] digit-sequence
	//E sign[opt] digit-sequence
	m["exponent-part"] =
		LEX(
		(m["e"] & OP(m["+"] | m["-"]) & m["digit-sequence"]) |
		(m["E"] & OP(m["+"] | m["-"]) & m["digit-sequence"])
		, TA_EXPONENT, "exponent part not ok", 1)
		;

	m["f"] = LEX(new lex::Integer('f'), TA_SUFFIX, "expected 'f'", 2);
	m["l"] = LEX(new lex::Integer('l'), TA_SUFFIX, "expected 'l'", 2);
	m["F"] = LEX(new lex::Integer('F'), TA_SUFFIX, "expected 'F'", 2);
	m["L"] = LEX(new lex::Integer('L'), TA_SUFFIX, "expected 'L'", 2);
	//	[floating-suffix]:
	//one of
	//	f l F L
	m["floating-suffix"] =
		LEX(
		m["f"] | m["l"] | m["F"] | m["L"],
		TA_SUFFIX, "floating suffix not ok", 1)
		;



	//	[floating-literal]:
	//fractional-constant exponent-part[opt] floating-suffix[opt]
	//digit-sequence exponent-part floating-suffix[opt]

	m["f_1"] = (m["fractional-constant"] & OP(m["exponent-part"]) & OP(m["floating-suffix"]));
	m["f_2"] = (m["digit-sequence"] & m["exponent-part"] & OP(m["floating-suffix"]));
	m["floating-literal"] = 			
			LEX(m["f_1"], TA_FLOAT)
		||	LEX(m["f_2"], TA_FLOAT);


	//Token attribute needs to be set on the rule that pushes the token into production, not anywhere else.
	//"floating-literal" pushes a token into production in the rule above, not here below.
	m["start"] = 
			~m["gaps"] 
		&&	m["floating-literal"]
		&&	LEX(m[";"], TA_TERMINAL, "expected ;", 1);
};


void test999::SetSyntax(lex::Base::Syntax& /*ref*/)
{	

};



void test999::SetReports(lex::Base::Reports& /*rep*/)
{

};



void test999::AddAsProduction(lex::Base::Syntax& ref, const char* p[], const int a[], int lim)
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




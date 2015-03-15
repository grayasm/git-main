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





#include "test_14882_2003_2.13.1.hpp"


void test_14882_2003_2_13_1::run(const char* test)
{
	test_14882_2003_2_13_1 obj;
	obj.test_gen::run(test);
};


char* test_14882_2003_2_13_1::GetText()
{	
	char* text=
		//decimal
		"0;\n"
		"1;\n"
		"1234567890;\n"
		"10000000001000000000100000000010000000001000000000100000000010000000001000000000100000000010000000001000000000100000000010000000001000000000100000000010000000001000000000100000000010000000001000000000;\n"
		//octal
		"01;\n"
		"01234567;\n"
		"08;\n"//not an octal digit '8'
		"09;\n"//not an octal digit '9'
		//hexadecimal 'x'
		"0x0;\n"
		"0x;\n"//not ok
		"00x124;\n"//not ok
		"0x124;\n"
		"0x124ul;\n"
		"0x124UL;\n"
		"0x124ull;\n"
		"0x124Ull;\n"
		"0x124uLL;\n"
		"0x124ULL;\n"
		"0x124uLl;\n"//bad hexadecimal suffix Ll
		"0x124UlL;\n"//bad hexadecimal suffix lL
		"0 x124;\n"//not ok
		"0xa1b2C3D4e5f6;\n"
		"0xABCDEFabcdef;\n"
		"0x ab;\n"//not ok
		"0x0AG;\n"//not ok


		//hexadecimal 'X'
		"0X0;\n"
		"00X124;\n"//not ok
		"0X;\n"//not ok
		"0X124;\n"
		"0X124ul;\n"
		"0X124UL;\n"
		"0X124ull;\n"
		"0X124Ull;\n"
		"0X124uLL;\n"
		"0X124ULL;\n"
		"0X124uLl;\n"//bad heXadecimal suffix Ll
		"0X124UlL;\n"//bad hexadecimal suffix lL
		"0 X124;\n"//not ok
		"0Xa1b2C3D4e5f6;\n"
		"0XABCDEFabcdef;\n"
		"0X ab;\n"//not ok
		"0X0AG;\n"//not ok

		;

	return text;
};


void test_14882_2003_2_13_1::SetGrammar(ebnf::DefaultGrammar::Ptr& grammar)
{
	grammar->SetTerm("endl");
	ebnf::Grammar::Map& m = grammar->GetMap();


	//grammar
	//	[nonzero-digit]: one of
	//	1 2 3 4 5 6 7 8 9
	m["nonzero-digit"] = new lex::Range('1', '9');


	//	[hexadecimal-digit]: one of
	//	0 1 2 3 4 5 6 7 8 9
	//	a b c d e f
	//	A B C D E F
	m["a_f"] = new lex::Range('a', 'f');
	m["A_F"] = new lex::Range('A', 'F');
	m["hexadecimal-digit"] = m["0_9"] | m["a_f"] | m["A_F"];


	//	[hexadecimal-literal]:
	//	0x hexadecimal-digit
	//	0X hexadecimal-digit
	//	hexadecimal-literal hexadecimal-digit
	m["0"] = new lex::Integer('0');
	m["x"] = new lex::Integer('x');
	m["X"] = new lex::Integer('X');	
	m["hexadecimal-literal"] = 
		(m["0"] & m["x"] & m["hexadecimal-digit"] & 0*m["hexadecimal-digit"]) |
		(m["0"] & m["X"] & m["hexadecimal-digit"] & 0*m["hexadecimal-digit"])		
		;

	//	[octal-digit]: one of
	//	0 1 2 3 4 5 6 7
	m["octal-digit"] = new lex::Range('0', '7');

	//	[octal-literal]:
	//	0
	//	octal-literal octal-digit	
	m["octal-literal"] = m["0"] & 0*m["octal-digit"];


	//	[decimal-literal]:
	//	nonzero-digit
	//	decimal-literal digit		
	m["decimal-literal"] = (m["nonzero-digit"] & 0*m["0_9"]);


	//	[unsigned-suffix]: one of
	//	u U
	m["u"] = new lex::Integer('u');
	m["U"] = new lex::Integer('U');
	m["unsigned-suffix"] = m["u"] | m["U"];

	//	[long-suffix]: one of
	//	l L
	m["l"] = new lex::Integer('l');
	m["L"] = new lex::Integer('L');
	m["long-suffix"] = m["l"] | m["L"];	
	m["long-long-suffix"] = 
		(m["l"] & m["l"]) |
		(m["L"] & m["L"])
		;

	//	[integer-suffix]: (C99 ISO 9899/1999 with long_long_suffix)
	//	unsigned-suffix long-suffix[opt]
	//	unsigned-suffix long-long-suffix
	//	long-suffix unsigned-suffix[opt]
	//	long-long-suffix unsigned-suffix[opt]
	m["integer-suffix"] =
		(m["unsigned-suffix"] & m["long-long-suffix"]) |
		(m["unsigned-suffix"] & OP(m["long-suffix"])) |		
		(m["long-long-suffix"] & OP(m["unsigned-suffix"])) |
		(m["long-suffix"] & OP(m["unsigned-suffix"]))
		;

	//	[integer-literal]:
	//	decimal-literal integer-suffix[opt]
	//	octal-literal integer-suffix[opt]
	//	hexadecimal-literal integer-suffix[opt]

	//apply attribute where the rule pushes token into production. Look for ||  &&  and similar.
	m["integer-literal"] =		
		LEX((m["decimal-literal"] & OP(m["integer-suffix"])), TA_DECIMAL)
		||	LEX((m["hexadecimal-literal"] & OP(m["integer-suffix"])), TA_HEXADECIMAL)
		||	LEX((m["octal-literal"] & OP(m["integer-suffix"])), TA_OCTAL)
		;

	m["start"] = 
		m["integer-literal"] 
	&&	LEX(m[";"], TA_TERMINAL);

};


void test_14882_2003_2_13_1::SetSyntax(lex::Base::Syntax& ref)
{	

	//decimal
	const char* p1[]={"0",";"};
	const int a1[]={TA_OCTAL, TA_TERMINAL};

	const char* p2[]={"1",";"};
	const char* p3[]={"1234567890",";"};
	const char* p4[]={"10000000001000000000100000000010000000001000000000100000000010000000001000000000100000000010000000001000000000100000000010000000001000000000100000000010000000001000000000100000000010000000001000000000",";"};
	const int a2[]={TA_DECIMAL, TA_TERMINAL};

	//octal
	const char* p5[]={"01",";"};
	const char* p6[]={"01234567",";"};
	//const char* p[]={"08",";"};//not an octal digit '8'
	//const char* p[]={"09",";"};//not an octal digit '9'
	const int a5[] = {TA_OCTAL, TA_TERMINAL};

	//hexadecimal 'x'
	const char* p7[]={"0x0",";"};
	//const char* p[]={"0x",";"};//not ok
	//const char* p[]={"00x124",";"};//not ok
	const char* p8[]={"0x124",";"};
	const char* p9[]={"0x124ul",";"};
	const char* p10[]={"0x124UL",";"};
	const char* p11[]={"0x124ull",";"};
	const char* p12[]={"0x124Ull",";"};
	const char* p13[]={"0x124uLL",";"};
	const char* p14[]={"0x124ULL",";"};
	//const char* p[]={"0x124uLl",";"};//bad hexadecimal suffix Ll
	//const char* p[]={"0x124UlL",";"};//bad hexadecimal suffix lL
	//const char* p[]={"0 x124",";"};//not ok
	const char* p15[]={"0xa1b2C3D4e5f6",";"};
	const char* p16[]={"0xABCDEFabcdef",";"};
	//const char* p[]={"0x ab",";"};//not ok
	//const char* p[]={"0x0AG",";"};//not ok



	//hexadecimal 'X'
	const char* p17[]={"0X0",";"};
	//const char* p[]={"00X124",";"};//not ok
	//const char* p[]={"0X",";"};//not ok
	const char* p18[]={"0X124",";"};
	const char* p19[]={"0X124ul",";"};
	const char* p20[]={"0X124UL",";"};
	const char* p21[]={"0X124ull",";"};
	const char* p22[]={"0X124Ull",";"};
	const char* p23[]={"0X124uLL",";"};
	const char* p24[]={"0X124ULL",";"};
	//const char* p[]={"0X124uLl",";"};//bad heXadecimal suffix Ll
	//const char* p[]={"0X124UlL",";"};//bad hexadecimal suffix lL
	//const char* p[]={"0 X124",";"};//not ok
	const char* p25[]={"0Xa1b2C3D4e5f6",";"};
	const char* p26[]={"0XABCDEFabcdef",";"};
	//const char* p[]={"0X ab",";"};//not ok
	//const char* p[]={"0X0AG",";"};//not ok
	const int a7[]={TA_HEXADECIMAL, TA_TERMINAL};


	//decimal
	AddAsProduction(ref, p1, a1, sizeof(p1)/sizeof(p1[0]));
	AddAsProduction(ref, p2, a2, sizeof(p2)/sizeof(p2[0]));
	AddAsProduction(ref, p3, a2, sizeof(p3)/sizeof(p3[0]));
	AddAsProduction(ref, p4, a2, sizeof(p4)/sizeof(p4[0]));
	//octal
	AddAsProduction(ref, p5, a5, sizeof(p5)/sizeof(p5[0]));
	AddAsProduction(ref, p6, a5, sizeof(p6)/sizeof(p6[0]));
	//hexadecimal
	AddAsProduction(ref, p7, a7, sizeof(p7)/sizeof(p7[0]));
	AddAsProduction(ref, p8, a7, sizeof(p8)/sizeof(p8[0]));
	AddAsProduction(ref, p9, a7, sizeof(p9)/sizeof(p9[0]));
	AddAsProduction(ref, p10, a7, sizeof(p10)/sizeof(p10[0]));
	AddAsProduction(ref, p11, a7, sizeof(p11)/sizeof(p11[0]));
	AddAsProduction(ref, p12, a7, sizeof(p12)/sizeof(p12[0]));
	AddAsProduction(ref, p13, a7, sizeof(p13)/sizeof(p13[0]));
	AddAsProduction(ref, p14, a7, sizeof(p14)/sizeof(p14[0]));
	AddAsProduction(ref, p15, a7, sizeof(p15)/sizeof(p15[0]));
	AddAsProduction(ref, p16, a7, sizeof(p16)/sizeof(p16[0]));
	AddAsProduction(ref, p17, a7, sizeof(p17)/sizeof(p17[0]));
	AddAsProduction(ref, p18, a7, sizeof(p18)/sizeof(p18[0]));
	AddAsProduction(ref, p19, a7, sizeof(p19)/sizeof(p19[0]));
	AddAsProduction(ref, p20, a7, sizeof(p20)/sizeof(p20[0]));
	AddAsProduction(ref, p21, a7, sizeof(p21)/sizeof(p21[0]));
	AddAsProduction(ref, p22, a7, sizeof(p22)/sizeof(p22[0]));
	AddAsProduction(ref, p23, a7, sizeof(p23)/sizeof(p23[0]));
	AddAsProduction(ref, p24, a7, sizeof(p24)/sizeof(p24[0]));
	AddAsProduction(ref, p25, a7, sizeof(p25)/sizeof(p25[0]));
	AddAsProduction(ref, p26, a7, sizeof(p26)/sizeof(p26[0]));


};




void test_14882_2003_2_13_1::SetReports(lex::Base::Reports& /*rep*/)
{

};



void test_14882_2003_2_13_1::AddAsProduction(lex::Base::Syntax& ref, const char* p[], const int a[], int lim)
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




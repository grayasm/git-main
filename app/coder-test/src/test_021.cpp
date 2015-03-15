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



#include "test_021.hpp"



void test21::run(const char* test)
{
	test21 obj;
	obj.test_gen::run(test);
};


char* test21::GetText()
{	
	char* text=
		//simple escape sequence
		"' ';\n"
		"'\\'';\n"
		"'\\\"';\n"
		"'\\?';\n"
		"'\\\\';\n"
		"'\\a';\n"		
		"'\\b';\n"
		"'\\a\\b\\f\\n\\r\\t\\v';\n"//possible due to grammar
		"'\\f';\n"
		"'\\n';\n"
		"'\\r';\n"
		"'\\t';\n"
		"'\\v';\n"
		//octal escape sequence		
		"'\\101';\n"
		"'\\077';\n"
		"'\\055\\023\\033\\101\\141\\142\\143';\n"//possible due to grammar
		"'\\111111111111111111111111111';\n"//possible due to grammar
		//hexadecimal escape sequence
		"'\\xFF';\n"
		"'\\xAE\\xff';\n"
		"'\\xffffffffffffffffffffffffff';\n"//possible due to grammar
		//any member of the source character set except ' \ \n		
		"'\a';\n"
		"'\b';\n"
		"'\f';\n"
		//"'\n';\n" not allowed
		"'\r';\n"
		"'\t';\n"
		"'\v';\n"
		"'z';\n"
		//L'c-char-sequence'
		"L' ';\n"
		"L'\\'';\n"
		"L'\\\"';\n"
		"L'\\?';\n"
		"L'\\\\';\n"
		"L'\\a';\n"		
		"L'\\b';\n"
		"L'\\a\\b\\f\\n\\r\\t\\v';\n"//possible due to grammar
		"L'\\f';\n"
		"L'\\n';\n"
		"L'\\r';\n"
		"L'\\t';\n"
		"L'\\v';\n"
		//octal escape sequence		
		"L'\\101';\n"
		"L'\\077';\n"
		"L'\\055\\023\\033\\101\\141\\142\\143';\n"//possible due to grammar
		"L'\\111111111111111111111111111';\n"//possible due to grammar
		//hexadecimal escape sequence
		"L'\\xFF';\n"
		"L'\\xAE\\xff';\n"
		"L'\\xffffffffffffffffffffffffff';\n"//possible due to grammar
		//any member of the source character set except ' \ \n		
		"L'\a';\n"
		"L'\b';\n"
		"L'\f';\n"
		//"'\n';\n" not allowed
		"L'\r';\n"
		"L'\t';\n"
		"L'\v';\n"
		"L'z';\n"

		//malformed character-literal - not recognized by the Lexer.
		"'\\w';\n"
		"''';\n"
		"'\\';\n"

		"L'\\w';\n"
		"L''';\n"
		"L'\\';\n"
		;

	
	//There are other character-literals which although are wrong as value, can be parsed ok by grammar;

	//warnings for:
/*
	'c-char-sequence' syntax

		"'\\w';\n"		-unknown escape sequence 
		"'\\079';\n"	-not an octal digit
		"'\\xAG';\n"	-not a hexadecimal digit
		"''';\n"		-any literal except ' \ \n
		"'\\';\n"
	
	L'c-char-sequence' syntax

		"L'\\w';\n"		-unknown escape sequence
		"L'\\079';\n"	-not an octal digit
		"L'\\xAG';\n"	-not a hexadecimal digit
		"L''';\n"		-any literal except ' \ \n
		"L'\\';\n"
*/

	return text;
};


void test21::SetGrammar(ebnf::DefaultGrammar::Ptr& grammar)
{
	grammar->SetTerm("endl");
	ebnf::Grammar::Map& m = grammar->GetMap();

	
	m["\\'"] = m["\\"] & m["'"];
	m["\\\""] = m["\\"] & m["\""];
	m["\\?"] = m["\\"] & m["?"];
	m["\\\\"] = m["\\"] & m["\\"];
	
	m["a"] = new lex::Integer('a');
	m["b"] = new lex::Integer('b');
	m["f"] = new lex::Integer('f');
	m["n"] = new lex::Integer('n');
	m["r"] = new lex::Integer('r');
	m["t"] = new lex::Integer('t');
	m["v"] = new lex::Integer('v');

	m["\\a"] = m["\\"] & LEX(m["a"], TA_SIMPLE_ESCAPE_SEQ, "Invalid escaped token. Use only one of: a,b,f,n,r,t,v .", 1);
	m["\\b"] = m["\\"] & m["b"];
	m["\\f"] = m["\\"] & m["f"];
	m["\\n"] = m["\\"] & m["n"];
	m["\\r"] = m["\\"] & m["r"];
	m["\\t"] = m["\\"] & m["t"];
	m["\\v"] = m["\\"] & m["v"];
	
	//grammar
	m["simple-escape-sequence"] =	
		m["\\'"] 
	|	m["\\\""]
	|	m["\\?"]
	|	m["\\\\"]
	|	m["\\a"]
	|	m["\\b"]
	|	m["\\f"]
	|	m["\\n"]
	|	m["\\r"]
	|	m["\\t"]
	|	m["\\v"]
	;
	

	m["octal-digit"] = new lex::Range('0', '7');
	m["octal-escape-sequence"] = 		
		(m["\\"] & m["octal-digit"] & m["octal-digit"] & m["octal-digit"]) |
		(m["\\"] & m["octal-digit"] & m["octal-digit"]) |
		(m["\\"] & m["octal-digit"])		
		;

	m["a_f"] = new lex::Range('a', 'f');
	m["A_F"] = new lex::Range('A', 'F');
	m["hexadecimal-digit"] = m["0_9"] | m["a_f"] | m["A_F"];

	m["x"] = new lex::Integer('x');
	m["\\x"] = m["\\"] & m["x"];
	m["hexadecimal-escape-sequence"] = 
		m["\\x"] & m["hexadecimal-digit"] & 0*m["hexadecimal-digit"]
		;


	m["escape-sequence"] =	
		m["simple-escape-sequence"] |
		m["octal-escape-sequence"] |
		m["hexadecimal-escape-sequence"]
	;


	m["0_65535"] = new lex::Range(0, 65535);
	m["c-char"] =		
			LEX(
			(m["0_65535"] - (m["'"] | m["\\"] | m["endl"])),
			TA_INVALID_SEQ, "Tokens: ' \\ and new-line-character cannot be quoted.", 1)
		|	m["escape-sequence"]
		;

	m["c-char-sequence"] =
		m["c-char"] & 0*m["c-char"];

	m["L"] = new lex::Integer('L');
	m["character-literal"] =
			LEX((m["L"] & m["'"] & m["c-char-sequence"] & m["'"]), TA_WIDE_CHAR_SEQUENCE)
		||	LEX((m["'"] & m["c-char-sequence"] & m["'"]), TA_CHAR_SEQUENCE)
		;

	m["start"] = 
			~m["gaps"]
		&&	m["character-literal"] 
		&&	LEX(m[";"], TA_TERMINAL, "expected ;", 1)
		&&	~m["gaps"]
		;

};


void test21::SetSyntax(lex::Base::Syntax& ref)
{	

	//simple escape sequence
	const char* p1[]={"' '",";"};
	const char* p1_1[]={"'\\''",";"};
	const char* p2[]={"'\\\"'",";"};
	const char* p3[]={"'\\?'",";"};
	const char* p4[]={"'\\\\'",";"};
	const char* p5[]={"'\\a'",";"};
	const char* p6[]={"'\\b'",";"};
	const char* p7[]={"'\\a\\b\\f\\n\\r\\t\\v'",";"};//possible due to grammar
	const char* p8[]={"'\\f'",";"};
	const char* p9[]={"'\\n'",";"};
	const char* p10[]={"'\\r'",";"};
	const char* p11[]={"'\\t'",";"};
	const char* p12[]={"'\\v'",";"};
	//octal escape sequence		
	const char* p13[]={"'\\101'",";"};
	const char* p14[]={"'\\077'",";"};
	const char* p15[]={"'\\055\\023\\033\\101\\141\\142\\143'",";"};//possible due to grammar
	const char* p16[]={"'\\111111111111111111111111111'",";"};//possible due to grammar
	//hexadecimal escape sequence
	const char* p17[]={"'\\xFF'",";"};
	const char* p18[]={"'\\xAE\\xff'",";"};
	const char* p19[]={"'\\xffffffffffffffffffffffffff'",";"};//possible due to grammar
	//any member of the source character set except ' \ \n
	const char* p20[]={"'\a'",";"};
	const char* p21[]={"'\b'",";"};
	const char* p22[]={"'\f'",";"};
	//"'\n';\n" not allowed
	const char* p23[]={"'\r'",";"};
	const char* p24[]={"'\t'",";"};
	const char* p25[]={"'\v'",";"};
	const char* p26[]={"'z'",";"};
	const int a1[]={TA_CHAR_SEQUENCE, TA_TERMINAL};


		//L'c-char-sequence'
	const char* p27[]={"L' '",";"};
	const char* p27_1[]={"L'\\''",";"};
	const char* p28[]={"L'\\\"'",";"};
	const char* p29[]={"L'\\?'",";"};
	const char* p30[]={"L'\\\\'",";"};
	const char* p31[]={"L'\\a'",";"};
	const char* p32[]={"L'\\b'",";"};
	const char* p33[]={"L'\\a\\b\\f\\n\\r\\t\\v'",";"};//possible due to grammar
	const char* p34[]={"L'\\f'",";"};
	const char* p35[]={"L'\\n'",";"};
	const char* p36[]={"L'\\r'",";"};
	const char* p37[]={"L'\\t'",";"};
	const char* p38[]={"L'\\v'",";"};
		//octal escape sequence		
	const char* p39[]={"L'\\101'",";"};
	const char* p40[]={"L'\\077'",";"};
	const char* p41[]={"L'\\055\\023\\033\\101\\141\\142\\143'",";"};//possible due to grammar
	const char* p42[]={"L'\\111111111111111111111111111'",";"};//possible due to grammar
	//hexadecimal escape sequence
	const char* p43[]={"L'\\xFF'",";"};
	const char* p44[]={"L'\\xAE\\xff'",";"};
	const char* p45[]={"L'\\xffffffffffffffffffffffffff'",";"};//possible due to grammar
	//any member of the source character set except ' \ \n
	const char* p46[]={"L'\a'",";"};
	const char* p47[]={"L'\b'",";"};
	const char* p48[]={"L'\f'",";"};
		//"'\n';\n" not allowed
	const char* p49[]={"L'\r'",";"};
	const char* p50[]={"L'\t'",";"};
	const char* p51[]={"L'\v'",";"};
	const char* p52[]={"L'z'",";"};
	const int a27[]={TA_WIDE_CHAR_SEQUENCE, TA_TERMINAL};

	//malformed character-literal
	//const char* p53[]={"'\\w'",";"};

	

	//simple escape sequence
	AddAsProduction(ref, p1, a1, sizeof(p1)/sizeof(p1[0]));
	AddAsProduction(ref, p1_1, a1, sizeof(p1_1)/sizeof(p1_1[0]));
	AddAsProduction(ref, p2, a1, sizeof(p2)/sizeof(p2[0]));
	AddAsProduction(ref, p3, a1, sizeof(p3)/sizeof(p3[0]));
	AddAsProduction(ref, p4, a1, sizeof(p4)/sizeof(p4[0]));
	AddAsProduction(ref, p5, a1, sizeof(p5)/sizeof(p5[0]));
	AddAsProduction(ref, p6, a1, sizeof(p6)/sizeof(p6[0]));
	AddAsProduction(ref, p7, a1, sizeof(p7)/sizeof(p7[0]));
	AddAsProduction(ref, p8, a1, sizeof(p8)/sizeof(p8[0]));
	AddAsProduction(ref, p9, a1, sizeof(p9)/sizeof(p9[0]));
	AddAsProduction(ref, p10, a1, sizeof(p10)/sizeof(p10[0]));
	AddAsProduction(ref, p11, a1, sizeof(p11)/sizeof(p11[0]));
	AddAsProduction(ref, p12, a1, sizeof(p12)/sizeof(p12[0]));
	//octal escape sequence	
	AddAsProduction(ref, p13, a1, sizeof(p13)/sizeof(p13[0]));
	AddAsProduction(ref, p14, a1, sizeof(p14)/sizeof(p14 [0]));
	AddAsProduction(ref, p15, a1, sizeof(p15)/sizeof(p15 [0]));
	AddAsProduction(ref, p16, a1, sizeof(p16)/sizeof(p16[0]));
	//hexadecimal escape sequence
	AddAsProduction(ref, p17, a1, sizeof(p17)/sizeof(p17[0]));
	AddAsProduction(ref, p18, a1, sizeof(p18)/sizeof(p18[0]));
	AddAsProduction(ref, p19, a1, sizeof(p19)/sizeof(p19[0]));
	//any member of the source character set except ' \ \n		
	AddAsProduction(ref, p20, a1, sizeof(p20)/sizeof(p20 [0]));
	AddAsProduction(ref, p21, a1, sizeof(p21)/sizeof(p21[0]));
	AddAsProduction(ref, p22, a1, sizeof(p22)/sizeof(p22[0]));
	AddAsProduction(ref, p23, a1, sizeof(p23)/sizeof(p23[0]));
	AddAsProduction(ref, p24, a1, sizeof(p24)/sizeof(p24[0]));
	AddAsProduction(ref, p25, a1, sizeof(p25)/sizeof(p25[0]));
	AddAsProduction(ref, p26, a1, sizeof(p26)/sizeof(p26[0]));
	
	//L'c-char-sequence'
	AddAsProduction(ref, p27, a27, sizeof(p27)/sizeof(p27[0]));
	AddAsProduction(ref, p27_1, a27, sizeof(p27_1)/sizeof(p27_1[0]));
	AddAsProduction(ref, p28, a27, sizeof(p28)/sizeof(p28[0]));
	AddAsProduction(ref, p29, a27, sizeof(p29)/sizeof(p29[0]));
	AddAsProduction(ref, p30, a27, sizeof(p30)/sizeof(p30[0]));
	AddAsProduction(ref, p31, a27, sizeof(p31)/sizeof(p31[0]));
	AddAsProduction(ref, p32, a27, sizeof(p32)/sizeof(p32[0]));
	AddAsProduction(ref, p33, a27, sizeof(p33)/sizeof(p33[0]));
	AddAsProduction(ref, p34, a27, sizeof(p34)/sizeof(p34[0]));
	AddAsProduction(ref, p35, a27, sizeof(p35)/sizeof(p35[0]));
	AddAsProduction(ref, p36, a27, sizeof(p36)/sizeof(p36[0]));
	AddAsProduction(ref, p37, a27, sizeof(p37)/sizeof(p37[0]));
	AddAsProduction(ref, p38, a27, sizeof(p38)/sizeof(p38[0]));
	//octal escape sequence
	AddAsProduction(ref, p39, a27, sizeof(p39)/sizeof(p39[0]));
	AddAsProduction(ref, p40, a27, sizeof(p40)/sizeof(p40[0]));
	AddAsProduction(ref, p41, a27, sizeof(p41)/sizeof(p41[0]));
	AddAsProduction(ref, p42, a27, sizeof(p42)/sizeof(p42[0]));
	//hexadecimal escape sequence
	AddAsProduction(ref, p43, a27, sizeof(p43)/sizeof(p43[0]));
	AddAsProduction(ref, p44, a27, sizeof(p44)/sizeof(p44[0]));
	AddAsProduction(ref, p45, a27, sizeof(p45)/sizeof(p45[0]));
	//any member of the source character set except ' \ \n		
	AddAsProduction(ref, p46, a27, sizeof(p46)/sizeof(p46 [0]));
	AddAsProduction(ref, p47, a27, sizeof(p47)/sizeof(p47[0]));
	AddAsProduction(ref, p48, a27, sizeof(p48)/sizeof(p48[0]));
	//"'\n';\n" not allowed
	AddAsProduction(ref, p49, a27, sizeof(p49)/sizeof(p49[0]));
	AddAsProduction(ref, p50, a27, sizeof(p50)/sizeof(p50[0]));
	AddAsProduction(ref, p51, a27, sizeof(p51)/sizeof(p51[0]));
	AddAsProduction(ref, p52, a27, sizeof(p52)/sizeof(p52[0]));

};



void test21::SetReports(lex::Base::Reports& reps)
{
	lex::Report rep[6];
	rep[0].report(lex::Error("Invalid escaped token. Use only one of: a,b,f,n,r,t,v .", 1), 542, 54, 3);
	rep[1].report(lex::Error("Tokens: ' \\ and new-line-character cannot be quoted.", 1), 547, 55, 2);
	rep[2].report(lex::Error("Tokens: ' \\ and new-line-character cannot be quoted.", 1), 552, 56, 2);
	rep[3].report(lex::Error("Invalid escaped token. Use only one of: a,b,f,n,r,t,v .", 1), 559, 57, 4);
	rep[4].report(lex::Error("Tokens: ' \\ and new-line-character cannot be quoted.", 1), 565, 58, 3);
	rep[5].report(lex::Error("Tokens: ' \\ and new-line-character cannot be quoted.", 1), 571, 59, 3);

	for(int i=0; i<6; ++i)
		reps.push_back(rep[i]);
};



void test21::AddAsProduction(lex::Base::Syntax& ref, const char* p[], const int a[], int lim)
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




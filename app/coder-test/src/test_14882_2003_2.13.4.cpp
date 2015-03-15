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



#include "test_14882_2003_2.13.4.hpp"



void test_14882_2003_2_13_4::run(const char* test)
{
	test_14882_2003_2_13_4 obj;
	obj.test_gen::run(test);
};


char* test_14882_2003_2_13_4::GetText()
{	
	char* text=
		//[simple-escape-sequence]
		"\" \";\n"
		"\"\\'\";\n"
		"\"\\\"\";\n"
		"\"\\?\";\n"
		"\"\\\\\";\n"
		"\"\\a\";\n"
		"\"\\b\";\n"
		"\"\\f\";\n"
		"\"\\n\";\n"
		"\"\\r\";\n"
		"\"\\t\";\n"
		"\"\\v\";\n"
		//[octal-escape-sequence]
		"\"\\101\";\n"
		"\"\\077\";\n"
		"\"\\055\\023\\033\\101\\141\\142\\143\";\n"//parsed by lexer due to grammar, rejected in semantic of language
		"\"\\111111111111111111111111111\";\n"//possible due to grammar
		//[hexadecimal-escape-sequence]
		"\"\\xFF\";\n"
		"\"\\xAE\\xff\";\n"
		"\"\\xffffffffffffffffffffffffff\";\n"//parsed by lexer due due to grammar, rejected in semantic of language
		//any member of the source character set except ' \ \n		
		"\"\a\";\n"
		"\"\b\";\n"
		"\"\f\";\n"
		//"'\n';\n" not allowed
		"\"\r\";\n"
		"\"\t\";\n"
		"\"\v\";\n"
		"\"\";\n"//empty string
		"\"z\";\n"

		//sequence above + additional strings around rule
		"\"  \";\n"
		"\"\\'escape\\'double\";\n"
		"\"\\\"escape\\\"double\";\n"
		"\"\\?escape\\?triple\\?\";\n"
		"\"\\\\escape\\\\for\\\\4\\\\times\";\n"
		"\"\\a5times\\a4times\\a\\a1time only\\a\";\n"
		"\"6times\\b\\b\\b\\b\\b\\b\";\n"
		"\"\\f65335\\ffeed\\fit\\ffor\\fme\";\n"
		"\"7\\n6\\n5\\n4\\n3\\n2\\n1\\nnon\\ntoken\\n\";\n"
		"\"\\r\\rr\\rrr\\rrrrr\\rrrrrr\\r\";\n"
		"\"\\ttab\\ttab\\ttab\\t\";\n"
		"\"\\vvertical\\vtab;\";\n"
		//[octal-escape-sequence]
		"\"\\101 000:\\101 OCTAL:\\101 octal:\\101 \";\n"
		"\"\\077is this octal?\\077:??\";\n"
		"\"\\055a\\023b\\033c\\101d\\141e\\142f\\143g\";\n"//parsed by lexer due to grammar, rejected in semantic of language
		"\"\\111111111111111111111111111bin\";\n"//possible due to grammar
		//[hexadecimal-escape-sequence]
		"\"\\xFFc\\xFFd\\xFFe\\xFFf\\xFFg\\xFFh\\xFFi\\xFFj\\xFF\";\n"
		"\"\\xAE\\xfffactory\\xAE\\xffaction\";\n"
		"\"\\xffffffffffffffffffffffffff\";\n"//parsed by lexer due due to grammar, rejected in semantic of language
		//any member of the source character set except ' \ \n		
		"\"\a-\a-\aa\aa\a\";\n"
		"\"\bb\bb\";\n"
		"\"\ff\ff\";\n"
		//"'\n';\n" not allowed
		"\"\rreport\rreported\rrevision\rrrr3times\r\r\r\";\n"
		"\"\ttab\ttelevision\tttt3times\t\t\t\";\n"
		"\"\vvirtue\vwhat's wrong with v\v?\";\n"
		"\"normal string\";\n"
		
		//L'c-char-sequence'
		"L\" \";\n"
		"L\"\\'\";\n"
		"L\"\\\"\";\n"
		"L\"\\?\";\n"
		"L\"\\\\\";\n"
		"L\"\\a\";\n"
		"L\"\\b\";\n"
		"L\"\\f\";\n"
		"L\"\\n\";\n"
		"L\"\\r\";\n"
		"L\"\\t\";\n"
		"L\"\\v\";\n"
		//[octal-escape-sequence]
		"L\"\\101\";\n"
		"L\"\\077\";\n"
		"L\"\\055\\023\\033\\101\\141\\142\\143\";\n"//parsed by lexer due to grammar, rejected in semantic of language
		"L\"\\111111111111111111111111111\";\n"//possible due to grammar
		//[hexadecimal-escape-sequence]
		"L\"\\xFF\";\n"
		"L\"\\xAE\\xff\";\n"
		"L\"\\xffffffffffffffffffffffffff\";\n"//parsed by lexer due due to grammar, rejected in semantic of language
		//any member of the source character set except ' \ \n		
		"L\"\a\";\n"
		"L\"\b\";\n"
		"L\"\f\";\n"
		//"'\n';\n" not allowed
		"L\"\r\";\n"
		"L\"\t\";\n"
		"L\"\v\";\n"
		"L\"\";\n"//empty string
		"L\"z\";\n"

		//malformed string-literal
		"\"\"\";\n"
		"\"\\\";\n"
		"\"\n\";\n"
		;


	return text;
};


void test_14882_2003_2_13_4::SetGrammar(ebnf::DefaultGrammar::Ptr& grammar)
{
	grammar->SetTerm("endl");
	ebnf::Grammar::Map& m = grammar->GetMap();

	//grammar
	//[simple-escape-sequence]: one of
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

	m["\\a"] = m["\\"] & m["a"];
	m["\\b"] = m["\\"] & m["b"];
	m["\\f"] = m["\\"] & m["f"];
	m["\\n"] = m["\\"] & m["n"];
	m["\\r"] = m["\\"] & m["r"];
	m["\\t"] = m["\\"] & m["t"];
	m["\\v"] = m["\\"] & m["v"];

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

	//[octal-escape-sequence]:
	m["octal-digit"] = new lex::Range('0', '7');
	m["octal-escape-sequence"] = 
		(m["\\"] & m["octal-digit"] & m["octal-digit"] & m["octal-digit"]) |
		(m["\\"] & m["octal-digit"] & m["octal-digit"]) |
		(m["\\"] & m["octal-digit"])
		;

	//[hexadecimal-escape-sequence]:
	m["a_f"] = new lex::Range('a', 'f');
	m["A_F"] = new lex::Range('A', 'F');
	m["hexadecimal-digit"] = m["0_9"] | m["a_f"] | m["A_F"];

	m["x"] = new lex::Integer('x');
	m["\\x"] = m["\\"] & m["x"];
	m["hexadecimal-escape-sequence"] = 
		m["\\x"] & m["hexadecimal-digit"] & 0*m["hexadecimal-digit"];

	//[escape-sequence]:
	m["escape-sequence"] =		 
		m["simple-escape-sequence"] |
		m["octal-escape-sequence"] |
		m["hexadecimal-escape-sequence"]
	;

	//[source_character_set]:
	m["0_255"] = new lex::Range(0, 255);
	//[universal-character-name]:
	m["0_65535"] = new lex::Range(0, 65535);

	//[s-char]:
	m["s-char"] = 
		(m["0_255"] - (m["\""] | m["\\"] | m["endl"])) |
		(m["escape-sequence"]) |
		(m["0_65535"]- (m["\""] | m["\\"] | m["endl"]))
		;
	//[s-char-sequence]:
	m["s-char-sequence"] = m["s-char"] & 0*m["s-char"];


	//[string-literal]:
	m["L"] = new lex::Integer('L');
	m["string-literal"] =
			LEX((m["\""] & OP(m["s-char-sequence"]) & m["\""]), TA_STRING_SEQEUENCE)
		||	LEX((m["L"] & m["\""] & OP(m["s-char-sequence"]) & m["\""]),  TA_WIDE_STRING_SEQEUENCE)
		;
	
	m["start"] = m["string-literal"] && LEX(m[";"], TA_TERMINAL);
};


void test_14882_2003_2_13_4::SetSyntax(lex::Base::Syntax& ref)
{	

	//[simple-escape-sequence]
	const char* p1[]={"\" \"",";"};
	const char* p2[]={"\"\\'\"",";"};
	const char* p3[]={"\"\\\"\"",";"};
	const char* p4[]={"\"\\?\"",";"};
	const char* p5[]={"\"\\\\\"",";"};
	const char* p6[]={"\"\\a\"",";"};
	const char* p7[]={"\"\\b\"",";"};
	const char* p8[]={"\"\\f\"",";"};
	const char* p9[]={"\"\\n\"",";"};
	const char* p10[]={"\"\\r\"",";"};
	const char* p11[]={"\"\\t\"",";"};
	const char* p12[]={"\"\\v\"",";"};
	//[octal-escape-sequence]
	const char* p13[]={"\"\\101\"",";"};
	const char* p14[]={"\"\\077\"",";"};
	const char* p15[]={"\"\\055\\023\\033\\101\\141\\142\\143\"",";"};//parsed by lexer due to grammar, rejected in semantic of language
	const char* p16[]={"\"\\111111111111111111111111111\"",";"};//possible due to grammar
	//[hexadecimal-escape-sequence]
	const char* p17[]={"\"\\xFF\"",";"};
	const char* p18[]={"\"\\xAE\\xff\"",";"};
	const char* p19[]={"\"\\xffffffffffffffffffffffffff\"",";"};//parsed by lexer due due to grammar, rejected in semantic of language
	//any member of the source character set except ' \ \n		
	const char* p20[]={"\"\a\"",";"};
	const char* p21[]={"\"\b\"",";"};
	const char* p22[]={"\"\f\"",";"};
	//"'\n';\n" not allowed
	const char* p23[]={"\"\r\"",";"};
	const char* p24[]={"\"\t\"",";"};
	const char* p25[]={"\"\v\"",";"};
	const char* p26[]={"\"\"",";"};//empty string
	const char* p27[]={"\"z\"",";"};

	//sequence above + additional strings around rule
	const char* p28[]={"\"  \"",";"};
	const char* p29[]={"\"\\'escape\\'double\"",";"};
	const char* p30[]={"\"\\\"escape\\\"double\"",";"};
	const char* p31[]={"\"\\?escape\\?triple\\?\"",";"};
	const char* p32[]={"\"\\\\escape\\\\for\\\\4\\\\times\"",";"};
	const char* p33[]={"\"\\a5times\\a4times\\a\\a1time only\\a\"",";"};
	const char* p34[]={"\"6times\\b\\b\\b\\b\\b\\b\"",";"};
	const char* p35[]={"\"\\f65335\\ffeed\\fit\\ffor\\fme\"",";"};
	const char* p36[]={"\"7\\n6\\n5\\n4\\n3\\n2\\n1\\nnon\\ntoken\\n\"",";"};
	const char* p37[]={"\"\\r\\rr\\rrr\\rrrrr\\rrrrrr\\r\"",";"};
	const char* p38[]={"\"\\ttab\\ttab\\ttab\\t\"",";"};
	const char* p39[]={"\"\\vvertical\\vtab;\"",";"};
	//[octal-escape-sequence]
	const char* p40[]={"\"\\101 000:\\101 OCTAL:\\101 octal:\\101 \"",";"};
	const char* p41[]={"\"\\077is this octal?\\077:??\"",";"};
	const char* p42[]={"\"\\055a\\023b\\033c\\101d\\141e\\142f\\143g\"",";"};//parsed by lexer due to grammar, rejected in semantic of language
	const char* p43[]={"\"\\111111111111111111111111111bin\"",";"};//possible due to grammar
	//[hexadecimal-escape-sequence]
	const char* p44[]={"\"\\xFFc\\xFFd\\xFFe\\xFFf\\xFFg\\xFFh\\xFFi\\xFFj\\xFF\"",";"};
	const char* p45[]={"\"\\xAE\\xfffactory\\xAE\\xffaction\"",";"};
	const char* p46[]={"\"\\xffffffffffffffffffffffffff\"",";"};//parsed by lexer due due to grammar, rejected in semantic of language
	//any member of the source character set except ' \ \n		
	const char* p47[]={"\"\a-\a-\aa\aa\a\"",";"};
	const char* p48[]={"\"\bb\bb\"",";"};
	const char* p49[]={"\"\ff\ff\"",";"};
	//"'\n';\n" not allowed
	const char* p50[]={"\"\rreport\rreported\rrevision\rrrr3times\r\r\r\"",";"};
	const char* p51[]={"\"\ttab\ttelevision\tttt3times\t\t\t\"",";"};
	const char* p52[]={"\"\vvirtue\vwhat's wrong with v\v?\"",";"};
	const char* p53[]={"\"normal string\"",";"};
	const int a1[]={TA_STRING_SEQEUENCE, TA_TERMINAL};

	//L'c-char-sequence'
	const char* p54[]={"L\" \"",";"};
	const char* p55[]={"L\"\\'\"",";"};
	const char* p56[]={"L\"\\\"\"",";"};
	const char* p57[]={"L\"\\?\"",";"};
	const char* p58[]={"L\"\\\\\"",";"};
	const char* p59[]={"L\"\\a\"",";"};
	const char* p60[]={"L\"\\b\"",";"};
	const char* p61[]={"L\"\\f\"",";"};
	const char* p62[]={"L\"\\n\"",";"};
	const char* p63[]={"L\"\\r\"",";"};
	const char* p64[]={"L\"\\t\"",";"};
	const char* p65[]={"L\"\\v\"",";"};
	//[octal-escape-sequence]
	const char* p66[]={"L\"\\101\"",";"};
	const char* p67[]={"L\"\\077\"",";"};
	const char* p68[]={"L\"\\055\\023\\033\\101\\141\\142\\143\"",";"};//parsed by lexer due to grammar, rejected in semantic of language
	const char* p69[]={"L\"\\111111111111111111111111111\"",";"};//possible due to grammar
	//[hexadecimal-escape-sequence]
	const char* p70[]={"L\"\\xFF\"",";"};
	const char* p71[]={"L\"\\xAE\\xff\"",";"};
	const char* p72[]={"L\"\\xffffffffffffffffffffffffff\"",";"};//parsed by lexer due due to grammar, rejected in semantic of language
	//any member of the source character set except ' \ \n		
	const char* p73[]={"L\"\a\"",";"};
	const char* p74[]={"L\"\b\"",";"};
	const char* p75[]={"L\"\f\"",";"};
	//"'\n';\n" not allowed
	const char* p76[]={"L\"\r\"",";"};
	const char* p77[]={"L\"\t\"",";"};
	const char* p78[]={"L\"\v\"",";"};
	const char* p79[]={"L\"\"",";"};//empty string
	const char* p80[]={"L\"z\"",";"};
	const int a54[]={TA_WIDE_STRING_SEQEUENCE, TA_TERMINAL};


	//string literal
	AddAsProduction(ref, p1, a1, sizeof(p1)/sizeof(p1[0]));
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
	AddAsProduction(ref, p13, a1, sizeof(p13)/sizeof(p13[0]));
	AddAsProduction(ref, p14, a1, sizeof(p14)/sizeof(p14[0]));
	AddAsProduction(ref, p15, a1, sizeof(p15)/sizeof(p15[0]));
	AddAsProduction(ref, p16, a1, sizeof(p16)/sizeof(p16[0]));
	AddAsProduction(ref, p17, a1, sizeof(p17)/sizeof(p17 [0]));
	AddAsProduction(ref, p18, a1, sizeof(p18)/sizeof(p18[0]));
	AddAsProduction(ref, p19, a1, sizeof(p19)/sizeof(p19[0]));
	AddAsProduction(ref, p20, a1, sizeof(p20)/sizeof(p20[0]));
	AddAsProduction(ref, p21, a1, sizeof(p21)/sizeof(p21[0]));
	AddAsProduction(ref, p22, a1, sizeof(p22)/sizeof(p22[0]));
	AddAsProduction(ref, p23, a1, sizeof(p23)/sizeof(p23[0]));
	AddAsProduction(ref, p24, a1, sizeof(p24)/sizeof(p24[0]));
	AddAsProduction(ref, p25, a1, sizeof(p25)/sizeof(p25[0]));
	AddAsProduction(ref, p26, a1, sizeof(p26)/sizeof(p26[0]));
	AddAsProduction(ref, p27, a1, sizeof(p27)/sizeof(p27[0]));
	AddAsProduction(ref, p28, a1, sizeof(p28)/sizeof(p28[0]));
	AddAsProduction(ref, p29, a1, sizeof(p29)/sizeof(p29[0]));
	AddAsProduction(ref, p30, a1, sizeof(p30)/sizeof(p30[0]));
	AddAsProduction(ref, p31, a1, sizeof(p31)/sizeof(p31[0]));
	AddAsProduction(ref, p32, a1, sizeof(p32)/sizeof(p32[0]));
	AddAsProduction(ref, p33, a1, sizeof(p33)/sizeof(p33[0]));
	AddAsProduction(ref, p34, a1, sizeof(p34)/sizeof(p34[0]));
	AddAsProduction(ref, p35, a1, sizeof(p35)/sizeof(p35[0]));
	AddAsProduction(ref, p36, a1, sizeof(p36)/sizeof(p36[0]));
	AddAsProduction(ref, p37, a1, sizeof(p37)/sizeof(p37[0]));
	AddAsProduction(ref, p38, a1, sizeof(p38)/sizeof(p38[0]));
	AddAsProduction(ref, p39, a1, sizeof(p39)/sizeof(p39[0]));
	AddAsProduction(ref, p40, a1, sizeof(p40)/sizeof(p40[0]));
	AddAsProduction(ref, p41, a1, sizeof(p41)/sizeof(p41[0]));
	AddAsProduction(ref, p42, a1, sizeof(p42)/sizeof(p42[0]));
	AddAsProduction(ref, p43, a1, sizeof(p43)/sizeof(p43[0]));
	AddAsProduction(ref, p44, a1, sizeof(p44)/sizeof(p44[0]));
	AddAsProduction(ref, p45, a1, sizeof(p45)/sizeof(p45[0]));
	AddAsProduction(ref, p46, a1, sizeof(p46)/sizeof(p46[0]));
	AddAsProduction(ref, p47, a1, sizeof(p47)/sizeof(p47[0]));
	AddAsProduction(ref, p48, a1, sizeof(p48)/sizeof(p48[0]));
	AddAsProduction(ref, p49, a1, sizeof(p49)/sizeof(p49[0]));
	AddAsProduction(ref, p50, a1, sizeof(p50)/sizeof(p50[0]));
	AddAsProduction(ref, p51, a1, sizeof(p51)/sizeof(p51[0]));
	AddAsProduction(ref, p52, a1, sizeof(p52)/sizeof(p52[0]));
	AddAsProduction(ref, p53, a1, sizeof(p53)/sizeof(p53[0]));
	//wide string literal
	AddAsProduction(ref, p54, a54, sizeof(p54)/sizeof(p54[0]));
	AddAsProduction(ref, p55, a54, sizeof(p55)/sizeof(p55[0]));
	AddAsProduction(ref, p56, a54, sizeof(p56)/sizeof(p56[0]));
	AddAsProduction(ref, p57, a54, sizeof(p57)/sizeof(p57[0]));
	AddAsProduction(ref, p58, a54, sizeof(p58)/sizeof(p58[0]));
	AddAsProduction(ref, p59, a54, sizeof(p59)/sizeof(p59[0]));
	AddAsProduction(ref, p60, a54, sizeof(p60)/sizeof(p60[0]));
	AddAsProduction(ref, p61, a54, sizeof(p61)/sizeof(p61[0]));
	AddAsProduction(ref, p62, a54, sizeof(p62)/sizeof(p62[0]));
	AddAsProduction(ref, p63, a54, sizeof(p63)/sizeof(p63[0]));
	AddAsProduction(ref, p64, a54, sizeof(p64)/sizeof(p64[0]));
	AddAsProduction(ref, p65, a54, sizeof(p65)/sizeof(p65[0]));
	AddAsProduction(ref, p66, a54, sizeof(p66)/sizeof(p66[0]));
	AddAsProduction(ref, p67, a54, sizeof(p67)/sizeof(p67[0]));
	AddAsProduction(ref, p68, a54, sizeof(p68)/sizeof(p68[0]));
	AddAsProduction(ref, p69, a54, sizeof(p69)/sizeof(p69[0]));
	AddAsProduction(ref, p70, a54, sizeof(p70)/sizeof(p70[0]));
	AddAsProduction(ref, p71, a54, sizeof(p71)/sizeof(p71[0]));
	AddAsProduction(ref, p72, a54, sizeof(p72)/sizeof(p72[0]));
	AddAsProduction(ref, p73, a54, sizeof(p73)/sizeof(p73[0]));
	AddAsProduction(ref, p74, a54, sizeof(p74)/sizeof(p74[0]));
	AddAsProduction(ref, p75, a54, sizeof(p75)/sizeof(p75[0]));
	AddAsProduction(ref, p76, a54, sizeof(p76)/sizeof(p76[0]));
	AddAsProduction(ref, p77, a54, sizeof(p77)/sizeof(p77 [0]));
	AddAsProduction(ref, p78, a54, sizeof(p78)/sizeof(p78[0]));
	AddAsProduction(ref, p79, a54, sizeof(p79)/sizeof(p79[0]));
	AddAsProduction(ref, p80, a54, sizeof(p80)/sizeof(p80[0]));
};



void test_14882_2003_2_13_4::SetReports(lex::Base::Reports& /*rep*/)
{

};




void test_14882_2003_2_13_4::AddAsProduction(lex::Base::Syntax& ref, const char* p[], const int a[], int lim)
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




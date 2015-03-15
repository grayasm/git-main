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


#include "test_14882_2003_2.13.3.hpp"




void test_14882_2003_2_13_3::run(const char* test)
{
	test_14882_2003_2_13_3 obj;
	obj.test_gen::run(test);
};


char* test_14882_2003_2_13_3::GetText()
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

		".2;\n"
		"1.;\n"		
		"1.2;\n"
		//e
		"1.e1;\n"
		"1.e+1;\n"
		"1.e-1;\n"
		"1.2e1;\n"
		"1.2e+1;\n"
		"1.2e-1;\n"
		//E
		"1.E1;\n"
		"1.E+1;\n"
		"1.E-1;\n"
		"1.2E1;\n"
		"1.2E+1;\n"
		"1.2E-1;\n"		
		//f
		".2f;\n"
		"1.f;\n"
		"1.2f;\n"
		"1.e1f;\n"
		"1.e+1f;\n"
		"1.e-1f;\n"
		"1.2e1f;\n"
		"1.2e+1f;\n"
		"1.2e-1f;\n"
		"1.E1f;\n"
		"1.E+1f;\n"
		"1.E-1f;\n"
		"1.2E1f;\n"
		"1.2E+1f;\n"
		"1.2E-1f;\n"
		//l
		".2l;\n"
		"1.l;\n"
		"1.2l;\n"
		"1.e1l;\n"
		"1.e+1l;\n"
		"1.e-1l;\n"
		"1.2e1l;\n"
		"1.2e+1l;\n"
		"1.2e-1l;\n"
		"1.E1l;\n"
		"1.E+1l;\n"
		"1.E-1l;\n"
		"1.2E1l;\n"
		"1.2E+1l;\n"
		"1.2E-1l;\n"
		//F
		".2F;\n"
		"1.F;\n"
		"1.2F;\n"
		"1.e1F;\n"
		"1.e+1F;\n"
		"1.e-1F;\n"
		"1.2e1F;\n"
		"1.2e+1F;\n"
		"1.2e-1F;\n"
		"1.E1F;\n"
		"1.E+1F;\n"
		"1.E-1F;\n"
		"1.2E1F;\n"
		"1.2E+1F;\n"
		"1.2E-1F;\n"
		//L
		".2L;\n"
		"1.L;\n"
		"1.2L;\n"
		"1.e1L;\n"
		"1.e+1L;\n"
		"1.e-1L;\n"
		"1.2e1L;\n"
		"1.2e+1L;\n"
		"1.2e-1L;\n"
		"1.E1L;\n"
		"1.E+1L;\n"
		"1.E-1L;\n"
		"1.2E1L;\n"
		"1.2E+1L;\n"
		"1.2E-1L;\n"
		///
		"1e1;\n"
		"1e+1;\n"
		"1e-1;\n"
		"1E1;\n"
		"1E+1;\n"
		"1E-1;\n"
		//f
		"1e1f;\n"
		"1e+1f;\n"
		"1e-1f;\n"
		"1E1f;\n"
		"1E+1f;\n"
		"1E-1f;\n"
		//l
		"1e1l;\n"
		"1e+1l;\n"
		"1e-1l;\n"
		"1E1l;\n"
		"1E+1l;\n"
		"1E-1l;\n"

		//F
		"1e1F;\n"
		"1e+1F;\n"
		"1e-1F;\n"
		"1E1F;\n"
		"1E+1F;\n"
		"1E-1F;\n"

		//L
		"1e1L;\n"
		"1e+1L;\n"
		"1e-1L;\n"
		"1E1L;\n"
		"1E+1L;\n"
		"1E-1L;\n" 
		
		//lexer should parse
		"1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111.e1;\n"

		//invalid floating literals
		".e333-1L;\n"		
		"..222;\n"
		". 2;\n"
		//e
		"1.ee1;\n"
		"1. e1;\n"
		"1.ef1;\n"
		"1.e 1;\n"
		//E
		"1.Ee;\n"
		"1.E-0e;\n"
		//f
		".2fF;\n"
		"1.2E-1Ff;\n"
		//l
		".2Ll;\n"
		"1.lL;\n"
		//F
		".2fF;\n"
		"1.e-1Ff;\n"
		"1.2Ee+1F;\n"
		;

	return text;
};


void test_14882_2003_2_13_3::SetGrammar(ebnf::DefaultGrammar::Ptr& grammar)
{
	grammar->SetTerm("endl");
	ebnf::Grammar::Map& m = grammar->GetMap();

	//grammar

	//[digit]: 
	//one of
	//	0 1 2 3 4 5 6 7 8 9
	m["digit"] = m["0_9"];

	//	[digit-sequence]:
	//digit
	//digit-sequence digit
	m["digit-sequence"] = m["digit"] & 0*m["digit"];


	//	[fractional-constant]:
	//digit-sequence[opt] . digit-sequence
	//digit-sequence .
	m["fractional-constant"] = 
		(OP(m["digit-sequence"]) & m["."] & m["digit-sequence"]) |
		(m["digit-sequence"] & m["."])
		;


	m["e"] = new lex::Integer('e');
	m["E"] = new lex::Integer('E');
	//	[exponent-part]:
	//e sign[opt] digit-sequence
	//E sign[opt] digit-sequence
	m["exponent-part"] =
		(m["e"] & OP(m["+"] | m["-"]) & m["digit-sequence"]) |
		(m["E"] & OP(m["+"] | m["-"]) & m["digit-sequence"])
		;

	m["f"] = new lex::Integer('f');
	m["l"] = new lex::Integer('l');
	m["F"] = new lex::Integer('F');
	m["L"] = new lex::Integer('L');
	//	[floating-suffix]:
	//one of
	//	f l F L
	m["floating-suffix"] =
		m["f"] | m["l"] | m["F"] | m["L"];



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
			m["floating-literal"]
		&&	LEX(m[";"], TA_TERMINAL);
};


void test_14882_2003_2_13_3::SetSyntax(lex::Base::Syntax& ref)
{	
	const char* p1[]={".2",";"};
	const char* p2[]={"1.",";"};
	const char* p3[]={"1.2",";"};
		//e
	const char* p4[]={"1.e1",";"};
	const char* p5[]={"1.e+1",";"};
	const char* p6[]={"1.e-1",";"};
	const char* p7[]={"1.2e1",";"};
	const char* p8[]={"1.2e+1",";"};
	const char* p9[]={"1.2e-1",";"};
		//E
	const char* p10[]={"1.E1",";"};
	const char* p11[]={"1.E+1",";"};
	const char* p12[]={"1.E-1",";"};
	const char* p13[]={"1.2E1",";"};
	const char* p14[]={"1.2E+1",";"};
	const char* p15[]={"1.2E-1",";"};		
		//f
	const char* p16[]={".2f",";"};
	const char* p17[]={"1.f",";"};
	const char* p18[]={"1.2f",";"};
	const char* p19[]={"1.e1f",";"};
	const char* p20[]={"1.e+1f",";"};
	const char* p21[]={"1.e-1f",";"};
	const char* p22[]={"1.2e1f",";"};
	const char* p23[]={"1.2e+1f",";"};
	const char* p24[]={"1.2e-1f",";"};
	const char* p25[]={"1.E1f",";"};
	const char* p26[]={"1.E+1f",";"};
	const char* p27[]={"1.E-1f",";"};
	const char* p28[]={"1.2E1f",";"};
	const char* p29[]={"1.2E+1f",";"};
	const char* p30[]={"1.2E-1f",";"};
		//l
	const char* p31[]={".2l",";"};
	const char* p32[]={"1.l",";"};
	const char* p33[]={"1.2l",";"};
	const char* p34[]={"1.e1l",";"};
	const char* p35[]={"1.e+1l",";"};
	const char* p36[]={"1.e-1l",";"};
	const char* p37[]={"1.2e1l",";"};
	const char* p38[]={"1.2e+1l",";"};
	const char* p39[]={"1.2e-1l",";"};
	const char* p40[]={"1.E1l",";"};
	const char* p41[]={"1.E+1l",";"};
	const char* p42[]={"1.E-1l",";"};
	const char* p43[]={"1.2E1l",";"};
	const char* p44[]={"1.2E+1l",";"};
	const char* p45[]={"1.2E-1l",";"};
		//F
	const char* p46[]={".2F",";"};
	const char* p47[]={"1.F",";"};
	const char* p48[]={"1.2F",";"};
	const char* p49[]={"1.e1F",";"};
	const char* p50[]={"1.e+1F",";"};
	const char* p51[]={"1.e-1F",";"};
	const char* p52[]={"1.2e1F",";"};
	const char* p53[]={"1.2e+1F",";"};
	const char* p54[]={"1.2e-1F",";"};
	const char* p55[]={"1.E1F",";"};
	const char* p56[]={"1.E+1F",";"};
	const char* p57[]={"1.E-1F",";"};
	const char* p58[]={"1.2E1F",";"};
	const char* p59[]={"1.2E+1F",";"};
	const char* p60[]={"1.2E-1F",";"};
		//L
	const char* p61[]={".2L",";"};
	const char* p62[]={"1.L",";"};
	const char* p63[]={"1.2L",";"};
	const char* p64[]={"1.e1L",";"};
	const char* p65[]={"1.e+1L",";"};
	const char* p66[]={"1.e-1L",";"};
	const char* p67[]={"1.2e1L",";"};
	const char* p68[]={"1.2e+1L",";"};
	const char* p69[]={"1.2e-1L",";"};
	const char* p70[]={"1.E1L",";"};
	const char* p71[]={"1.E+1L",";"};
	const char* p72[]={"1.E-1L",";"};
	const char* p73[]={"1.2E1L",";"};
	const char* p74[]={"1.2E+1L",";"};
	const char* p75[]={"1.2E-1L",";"};
		///
	const char* p76[]={"1e1",";"};
	const char* p77[]={"1e+1",";"};
	const char* p78[]={"1e-1",";"};
	const char* p79[]={"1E1",";"};
	const char* p80[]={"1E+1",";"};
	const char* p81[]={"1E-1",";"};
		//f
	const char* p82[]={"1e1f",";"};
	const char* p83[]={"1e+1f",";"};
	const char* p84[]={"1e-1f",";"};
	const char* p85[]={"1E1f",";"};
	const char* p86[]={"1E+1f",";"};
	const char* p87[]={"1E-1f",";"};
		//l
	const char* p88[]={"1e1l",";"};
	const char* p89[]={"1e+1l",";"};
	const char* p90[]={"1e-1l",";"};
	const char* p91[]={"1E1l",";"};
	const char* p92[]={"1E+1l",";"};
	const char* p93[]={"1E-1l",";"};

		//F
	const char* p94[]={"1e1F",";"};
	const char* p95[]={"1e+1F",";"};
	const char* p96[]={"1e-1F",";"};
	const char* p97[]={"1E1F",";"};
	const char* p98[]={"1E+1F",";"};
	const char* p99[]={"1E-1F",";"};

		//L
	const char* p100[]={"1e1L",";"};
	const char* p101[]={"1e+1L",";"};
	const char* p102[]={"1e-1L",";"};
	const char* p103[]={"1E1L",";"};
	const char* p104[]={"1E+1L",";"};
	const char* p105[]={"1E-1L",";"};
	const char* p106[]={"1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111.e1",";"};

	const int a1[]={TA_FLOAT, TA_TERMINAL};


	AddAsProduction(ref, p1, a1, sizeof(p1)/sizeof(p1[0]));
	AddAsProduction(ref, p2, a1, sizeof(p2)/sizeof( p2[0]));
	AddAsProduction(ref, p3, a1, sizeof(p3)/sizeof( p3[0]));
	AddAsProduction(ref, p4, a1, sizeof(p4)/sizeof( p4[0]));
	AddAsProduction(ref, p5, a1, sizeof(p5)/sizeof( p5[0]));
	AddAsProduction(ref, p6, a1, sizeof(p6)/sizeof( p6 [0]));
	AddAsProduction(ref, p7, a1, sizeof(p7)/sizeof( p7[0]));
	AddAsProduction(ref, p8, a1, sizeof(p8)/sizeof( p8[0]));
	AddAsProduction(ref, p9, a1, sizeof(p9)/sizeof( p9[0]));
	AddAsProduction(ref, p10, a1, sizeof(p10)/sizeof( p10[0]));
	AddAsProduction(ref, p11, a1, sizeof(p11)/sizeof( p11[0]));
	AddAsProduction(ref, p12, a1, sizeof(p12)/sizeof( p12[0]));
	AddAsProduction(ref, p13, a1, sizeof(p13)/sizeof( p13[0]));
	AddAsProduction(ref, p14, a1, sizeof(p14)/sizeof(p14[0]));
	AddAsProduction(ref, p15, a1, sizeof(p15)/sizeof(p15[0]));
	AddAsProduction(ref, p16, a1, sizeof(p16)/sizeof(p16[0]));
	AddAsProduction(ref, p17, a1, sizeof(p17)/sizeof(p17[0]));
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
	AddAsProduction(ref, p54, a1, sizeof(p54)/sizeof(p54[0]));
	AddAsProduction(ref, p55, a1, sizeof(p55)/sizeof(p55[0]));
	AddAsProduction(ref, p56, a1, sizeof(p56)/sizeof(p56[0]));
	AddAsProduction(ref, p57, a1, sizeof(p57)/sizeof(p57[0]));
	AddAsProduction(ref, p58, a1, sizeof(p58)/sizeof(p58[0]));
	AddAsProduction(ref, p59, a1, sizeof(p59)/sizeof(p59[0]));
	AddAsProduction(ref, p60, a1, sizeof(p60)/sizeof(p60[0]));
	AddAsProduction(ref, p61, a1, sizeof(p61)/sizeof(p61[0]));
	AddAsProduction(ref, p62, a1, sizeof(p62)/sizeof(p62[0]));
	AddAsProduction(ref, p63, a1, sizeof(p63)/sizeof(p63[0]));
	AddAsProduction(ref, p64, a1, sizeof(p64)/sizeof(p64[0]));
	AddAsProduction(ref, p65, a1, sizeof(p65)/sizeof(p65[0]));
	AddAsProduction(ref, p66, a1, sizeof(p66)/sizeof(p66[0]));
	AddAsProduction(ref, p67, a1, sizeof(p67)/sizeof(p67[0]));
	AddAsProduction(ref, p68, a1, sizeof(p68)/sizeof(p68[0]));
	AddAsProduction(ref, p69, a1, sizeof(p69)/sizeof(p69[0]));
	AddAsProduction(ref, p70, a1, sizeof(p70)/sizeof(p70[0]));
	AddAsProduction(ref, p71, a1, sizeof(p71)/sizeof(p71[0]));
	AddAsProduction(ref, p72, a1, sizeof(p72)/sizeof(p72[0]));
	AddAsProduction(ref, p73, a1, sizeof(p73)/sizeof(p73[0]));
	AddAsProduction(ref, p74, a1, sizeof(p74)/sizeof(p74[0]));
	AddAsProduction(ref, p75, a1, sizeof(p75)/sizeof(p75[0]));
	AddAsProduction(ref, p76, a1, sizeof(p76)/sizeof(p76[0]));
	AddAsProduction(ref, p77, a1, sizeof(p77)/sizeof(p77[0]));
	AddAsProduction(ref, p78, a1, sizeof(p78)/sizeof(p78[0]));
	AddAsProduction(ref, p79, a1, sizeof(p79)/sizeof(p79[0]));
	AddAsProduction(ref, p80, a1, sizeof(p80)/sizeof(p80[0]));
	AddAsProduction(ref, p81, a1, sizeof(p81)/sizeof(p81[0]));
	AddAsProduction(ref, p82, a1, sizeof(p82)/sizeof(p82[0]));
	AddAsProduction(ref, p83, a1, sizeof(p83)/sizeof(p83[0]));
	AddAsProduction(ref, p84, a1, sizeof(p84)/sizeof(p84[0]));
	AddAsProduction(ref, p85, a1, sizeof(p85)/sizeof(p85[0]));
	AddAsProduction(ref, p86, a1, sizeof(p86)/sizeof(p86[0]));
	AddAsProduction(ref, p87, a1, sizeof(p87)/sizeof(p87[0]));
	AddAsProduction(ref, p88, a1, sizeof(p88)/sizeof(p88[0]));
	AddAsProduction(ref, p89, a1, sizeof(p89)/sizeof(p89[0]));
	AddAsProduction(ref, p90, a1, sizeof(p90)/sizeof(p90[0]));
	AddAsProduction(ref, p91, a1, sizeof(p91)/sizeof(p91[0]));
	AddAsProduction(ref, p92, a1, sizeof(p92)/sizeof(p92[0]));
	AddAsProduction(ref, p93, a1, sizeof(p93)/sizeof(p93[0]));
	AddAsProduction(ref, p94, a1, sizeof(p94)/sizeof(p94[0]));
	AddAsProduction(ref, p95, a1, sizeof(p95)/sizeof(p95[0]));
	AddAsProduction(ref, p96, a1, sizeof(p96)/sizeof(p96[0]));
	AddAsProduction(ref, p97, a1, sizeof(p97)/sizeof(p97[0]));
	AddAsProduction(ref, p98, a1, sizeof(p98)/sizeof(p98[0]));
	AddAsProduction(ref, p99, a1, sizeof(p99)/sizeof(p99[0]));
	AddAsProduction(ref, p100, a1, sizeof(p100)/sizeof(p100[0]));
	AddAsProduction(ref, p101, a1, sizeof(p101)/sizeof(p101[0]));
	AddAsProduction(ref, p102, a1, sizeof(p102)/sizeof(p102[0]));
	AddAsProduction(ref, p103, a1, sizeof(p103)/sizeof(p103[0]));
	AddAsProduction(ref, p104, a1, sizeof(p104)/sizeof(p104[0]));
	AddAsProduction(ref, p105, a1, sizeof(p105)/sizeof(p105[0]));
	AddAsProduction(ref, p106, a1, sizeof(p106)/sizeof(p106[0]));

};



void test_14882_2003_2_13_3::SetReports(lex::Base::Reports& /*rep*/)
{

};



void test_14882_2003_2_13_3::AddAsProduction(lex::Base::Syntax& ref, const char* p[], const int a[], int lim)
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




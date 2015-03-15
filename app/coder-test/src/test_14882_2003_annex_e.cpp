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


#include "test_14882_2003_annex_e.hpp"
#include "strconv.hpp"


void test_14882_2003_annex_e::run(const char* test)
{
	test_14882_2003_annex_e obj;
	obj.test_gen::run(test);
};


static misc::string s_txt=misc::string("");

char* test_14882_2003_annex_e::GetText()
{		
	misc::ofstream ofile("test_14882_2003_annex_e", std::ios_base::trunc);
	if( !ofile.is_open() ) 
	{
		s_txt = "\0";
		return (char*) s_txt.c_str();
	}

	misc::string v_txt;
	misc::string term("	;\n");
	//Latin
	//00c0–00d6, 00d8–00f6, 00f8–01f5, 01fa–0217, 0250–02a8, 1e00–1e9a, 1ea0–1ef9	
	v_txt +=  "Latin ;\n";
	v_txt += ToHex(0x00c0, 0x00d6, term);
	v_txt += ToHex(0x00d8, 0x00f6, term);
	v_txt += ToHex(0x00f8, 0x01f5, term);
	v_txt += ToHex(0x01fa, 0x0217, term);
	v_txt += ToHex(0x0250, 0x02a8, term);
	v_txt += ToHex(0x1e00, 0x1e9a, term);
	v_txt += ToHex(0x1ea0, 0x1ef9, term);
	
	HexWrite(v_txt, ofile);
	v_txt.clear();
	//---


	/*
	Greek: 0384, 0388–038a, 038c, 038e–03a1, 03a3–03ce, 03d0–03d6, 03da, 03dc, 03de, 03e0, 03e2–03f3,
	1f00–1f15, 1f18–1f1d, 1f20–1f45, 1f48–1f4d, 1f50–1f57, 1f59, 1f5b, 1f5d, 1f5f–1f7d, 1f80–1fb4,
	1fb6–1fbc, 1fc2–1fc4, 1fc6–1fcc, 1fd0–1fd3, 1fd6–1fdb, 1fe0–1fec, 1ff2–1ff4, 1ff6–1ffc
	*/
	v_txt += "Greek ;\n";
	v_txt += ToHex(0x0384, 0x0384, term);
	v_txt += ToHex(0x0388, 0x038a, term);
	v_txt += ToHex(0x038c, 0x038c, term);
	v_txt += ToHex(0x038e, 0x03a1, term);
	v_txt += ToHex(0x03a3, 0x03ce, term);
	v_txt += ToHex(0x03d0, 0x03d6, term);
	v_txt += ToHex(0x03da, 0x03da, term);
	v_txt += ToHex(0x03dc, 0x03dc, term);
	v_txt += ToHex(0x03de, 0x03de, term);
	v_txt += ToHex(0x03e0, 0x03e0, term);
	v_txt += ToHex(0x03e2, 0x03f3, term);
	v_txt += ToHex(0x1f00, 0x1f15, term);
	v_txt += ToHex(0x1f18, 0x1f1d, term);
	v_txt += ToHex(0x1f20, 0x1f45, term);
	v_txt += ToHex(0x1f48, 0x1f4d, term);
	v_txt += ToHex(0x1f50, 0x1f57, term);
	v_txt += ToHex(0x1f59, 0x1f59, term);
	v_txt += ToHex(0x1f5b, 0x1f5b, term);
	v_txt += ToHex(0x1f5d, 0x1f5d, term);
	v_txt += ToHex(0x1f5f, 0x1f7d, term);
	v_txt += ToHex(0x1f80, 0x1fb4, term);
	v_txt += ToHex(0x1fb6, 0x1fbc, term);
	v_txt += ToHex(0x1fc2, 0x1fc4, term);
	v_txt += ToHex(0x1fc6, 0x1fcc, term);
	v_txt += ToHex(0x1fd0, 0x1fd3, term);
	v_txt += ToHex(0x1fd6, 0x1fdb, term);
	v_txt += ToHex(0x1fe0, 0x1fec, term);
	v_txt += ToHex(0x1ff2, 0x1ff4, term);
	v_txt += ToHex(0x1ff6, 0x1ffc, term);

	HexWrite(v_txt, ofile);
	v_txt.clear();


	/*
	Cyrillic: 0401–040d, 040f–044f, 0451–045c, 045e–0481, 0490–04c4, 04c7–04c8, 04cb–04cc, 04d0–04eb,
			  04ee–04f5, 04f8–04f9
	*/
	v_txt += "Cyrillic ;\n";
	v_txt += ToHex(0x0401, 0x040d, term);
	v_txt += ToHex(0x040f, 0x044f, term);
	v_txt += ToHex(0x0451, 0x045c, term);
	v_txt += ToHex(0x045e, 0x0481, term);
	v_txt += ToHex(0x0490, 0x04c4, term);
	v_txt += ToHex(0x04c7, 0x04c8, term);
	v_txt += ToHex(0x04cb, 0x04cc, term);
	v_txt += ToHex(0x04d0, 0x04eb, term);
	v_txt += ToHex(0x04ee, 0x04f5, term);
	v_txt += ToHex(0x04f8, 0x04f9, term);

	HexWrite(v_txt, ofile);
	v_txt.clear();


	//Armenian: 0531–0556, 0561–0587
	v_txt += "Armenian ;\n";
	v_txt += ToHex(0x0531, 0x0556, term);
	v_txt += ToHex(0x0561, 0x0587, term);

	HexWrite(v_txt, ofile);
	v_txt.clear();


	//Hebrew: 05d0–05ea, 05f0–05f4
	v_txt += "Hebrew ;\n";
	v_txt += ToHex(0x05d0, 0x05ea, term);
	v_txt += ToHex(0x05f0, 0x05f4, term);

	HexWrite(v_txt, ofile);
	v_txt.clear();


	//Arabic: 0621–063a, 0640–0652, 0670–06b7, 06ba–06be, 06c0–06ce, 06e5–06e7
	v_txt += "Arabic ;\n";
	v_txt += ToHex(0x0621, 0x063a, term);
	v_txt += ToHex(0x0640, 0x0652, term);
	v_txt += ToHex(0x0670, 0x06b7, term);
	v_txt += ToHex(0x06ba, 0x06be, term);
	v_txt += ToHex(0x06c0, 0x06ce, term);
	v_txt += ToHex(0x06e5, 0x06e7, term);

	HexWrite(v_txt, ofile);
	v_txt.clear();



	//Devanagari: 0905–0939, 0958–0962
	v_txt += "Devanagari ;\n";
	v_txt += ToHex(0x0905, 0x0939, term);
	v_txt += ToHex(0x0958, 0x0962, term);

	HexWrite(v_txt, ofile);
	v_txt.clear();


	/*
	Bengali: 0985–098c, 098f–0990, 0993–09a8, 09aa–09b0, 09b2, 09b6–09b9, 09dc–09dd, 09df–09e1,
			 09f0–09f1
	*/
	v_txt += "Bengali ;\n";
	v_txt += ToHex(0x0985, 0x098c, term);
	v_txt += ToHex(0x098f, 0x0990, term);
	v_txt += ToHex(0x0993, 0x09a8, term);
	v_txt += ToHex(0x09aa, 0x09b0, term);
	v_txt += ToHex(0x09b2, 0x09b2, term);
	v_txt += ToHex(0x09b6, 0x09b9, term);
	v_txt += ToHex(0x09dc, 0x09dd, term);
	v_txt += ToHex(0x09df, 0x09e1, term);
	v_txt += ToHex(0x09f0, 0x09f1, term);

	HexWrite(v_txt, ofile);
	v_txt.clear();



	/*
	Gurmukhi: 0a05–0a0a, 0a0f–0a10, 0a13–0a28, 0a2a–0a30, 0a32–0a33, 0a35–0a36, 0a38–0a39,
			  0a59–0a5c, 0a5e
	*/
	v_txt += "Gurmukhi ;\n";
	v_txt += ToHex(0x0a05, 0x0a0a, term);
	v_txt += ToHex(0x0a0f, 0x0a10, term);
	v_txt += ToHex(0x0a13, 0x0a28, term);
	v_txt += ToHex(0x0a2a, 0x0a30, term);
	v_txt += ToHex(0x0a32, 0x0a33, term);
	v_txt += ToHex(0x0a35, 0x0a36, term);
	v_txt += ToHex(0x0a38, 0x0a39, term);
	v_txt += ToHex(0x0a59, 0x0a5c, term);
	v_txt += ToHex(0x0a5e, 0x0a5e, term);

	HexWrite(v_txt, ofile);
	v_txt.clear();


	//Gujarati: 0a85–0a8b, 0a8d, 0a8f–0a91, 0a93–0aa8, 0aaa–0ab0, 0ab2–0ab3, 0ab5–0ab9, 0ae0
	v_txt += "Gujarati ;\n";
	v_txt += ToHex(0x0a85, 0x0a8b, term);
	v_txt += ToHex(0x0a8d, 0x0a8d, term);
	v_txt += ToHex(0x0a8f, 0x0a91, term);
	v_txt += ToHex(0x0a93, 0x0aa8, term);
	v_txt += ToHex(0x0aaa, 0x0ab0, term);
	v_txt += ToHex(0x0ab2, 0x0ab3, term);
	v_txt += ToHex(0x0ab5, 0x0ab9, term);
	v_txt += ToHex(0x0ae0, 0x0ae0, term);

	HexWrite(v_txt, ofile);
	v_txt.clear();


	//Oriya: 0b05–0b0c, 0b0f–0b10, 0b13–0b28, 0b2a–0b30, 0b32–0b33, 0b36–0b39, 0b5c–0b5d, 0b5f–0b61
	v_txt += "Oriya ;\n";
	v_txt += ToHex(0x0b05, 0x0b0c, term);
	v_txt += ToHex(0x0b0f, 0x0b10, term);
	v_txt += ToHex(0x0b13, 0x0b28, term);
	v_txt += ToHex(0x0b2a, 0x0b30, term);
	v_txt += ToHex(0x0b32, 0x0b33, term);
	v_txt += ToHex(0x0b36, 0x0b39, term);
	v_txt += ToHex(0x0b5c, 0x0b5d, term);
	v_txt += ToHex(0x0b5f, 0x0b61, term);

	HexWrite(v_txt, ofile);
	v_txt.clear();



	/*
	Tamil: 0b85–0b8a, 0b8e–0b90, 0b92–0b95, 0b99–0b9a, 0b9c, 0b9e–0b9f, 0ba3–0ba4, 0ba8–0baa,
		   0bae–0bb5, 0bb7–0bb9
	*/
	v_txt += "Tamil ;\n";
	v_txt += ToHex(0x0b85, 0x0b8a, term);
	v_txt += ToHex(0x0b8e, 0x0b90, term);
	v_txt += ToHex(0x0b92, 0x0b95, term);
	v_txt += ToHex(0x0b99, 0x0b9a, term);
	v_txt += ToHex(0x0b9c, 0x0b9c, term);
	v_txt += ToHex(0x0b9e, 0x0b9f, term);
	v_txt += ToHex(0x0ba3, 0x0ba4, term);
	v_txt += ToHex(0x0ba8, 0x0baa, term);
	v_txt += ToHex(0x0bae, 0x0bb5, term);
	v_txt += ToHex(0x0bb7, 0x0bb9, term);

	HexWrite(v_txt, ofile);
	v_txt.clear();


	//Telugu: 0c05–0c0c, 0c0e–0c10, 0c12–0c28, 0c2a–0c33, 0c35–0c39, 0c60–0c61
	v_txt += "Telugu ;\n";
	v_txt += ToHex(0x0c05, 0x0c0c, term);
	v_txt += ToHex(0x0c0e, 0x0c10, term);
	v_txt += ToHex(0x0c12, 0x0c28, term);
	v_txt += ToHex(0x0c2a, 0x0c33, term);
	v_txt += ToHex(0x0c35, 0x0c39, term);
	v_txt += ToHex(0x0c60, 0x0c61, term);

	HexWrite(v_txt, ofile);
	v_txt.clear();


	//Kannada: 0c85–0c8c, 0c8e–0c90, 0c92–0ca8, 0caa–0cb3, 0cb5–0cb9, 0ce0–0ce1
	v_txt += "Kannada ;\n";
	v_txt += ToHex(0x0c85, 0x0c8c, term);
	v_txt += ToHex(0x0c8e, 0x0c90, term);
	v_txt += ToHex(0x0c92, 0x0ca8, term);
	v_txt += ToHex(0x0caa, 0x0cb3, term);
	v_txt += ToHex(0x0cb5, 0x0cb9, term);
	v_txt += ToHex(0x0ce0, 0x0ce1, term);

	HexWrite(v_txt, ofile);
	v_txt.clear();


	//Malayalam: 0d05–0d0c, 0d0e–0d10, 0d12–0d28, 0d2a–0d39, 0d60–0d61
	v_txt += "Malayalam ;\n";
	v_txt += ToHex(0x0d05, 0x0d0c, term);
	v_txt += ToHex(0x0d0e, 0x0d10, term);
	v_txt += ToHex(0x0d12, 0x0d28, term);
	v_txt += ToHex(0x0d2a, 0x0d39, term);
	v_txt += ToHex(0x0d60, 0x0d61, term);

	HexWrite(v_txt, ofile);
	v_txt.clear();



	//Thai: 0e01–0e30, 0e32–0e33, 0e40–0e46, 0e4f–0e5b
	v_txt += "Thai ;\n";
	v_txt += ToHex(0x0e01, 0x0e30, term);
	v_txt += ToHex(0x0e32, 0x0e33, term);
	v_txt += ToHex(0x0e40, 0x0e46, term);
	v_txt += ToHex(0x0e4f, 0x0e5b, term);

	HexWrite(v_txt, ofile);
	v_txt.clear();





	/*
	Lao: 0e81–0e82, 0e84, 0e87, 0e88, 0e8a, 0e8d, 0e94–0e97, 0e99–0e9f, 0ea1–0ea3, 0ea5, 0ea7, 0eaa, 0eab,
		 0ead–0eb0, 0eb2, 0eb3, 0ebd, 0ec0–0ec4, 0ec6
	*/
	v_txt += "Lao ;\n";
	v_txt += ToHex(0x0e81, 0x0e82, term);
	v_txt += ToHex(0x0e84, 0x0e84, term);
	v_txt += ToHex(0x0e87, 0x0e87, term);
	v_txt += ToHex(0x0e88, 0x0e88, term);
	v_txt += ToHex(0x0e8a, 0x0e8a, term);
	v_txt += ToHex(0x0e8d, 0x0e8d, term);
	v_txt += ToHex(0x0e94, 0x0e97, term);
	v_txt += ToHex(0x0e99, 0x0e9f, term);
	v_txt += ToHex(0x0ea1, 0x0ea3, term);
	v_txt += ToHex(0x0ea5, 0x0ea5, term);
	v_txt += ToHex(0x0ea7, 0x0ea7, term);
	v_txt += ToHex(0x0eaa, 0x0eaa, term);
	v_txt += ToHex(0x0eab, 0x0eab, term);
	v_txt += ToHex(0x0ead, 0x0eb0, term);
	v_txt += ToHex(0x0eb2, 0x0eb2, term);
	v_txt += ToHex(0x0eb3, 0x0eb3, term);
	v_txt += ToHex(0x0ebd, 0x0ebd, term);
	v_txt += ToHex(0x0ec0, 0x0ec4, term);
	v_txt += ToHex(0x0ec6, 0x0ec6, term);

	HexWrite(v_txt, ofile);
	v_txt.clear();


	//Georgian: 10a0–10c5, 10d0–10f6
	v_txt += "Georgian ;\n";
	v_txt += ToHex(0x10a0, 0x10c5, term);
	v_txt += ToHex(0x10d0, 0x10f6, term);

	HexWrite(v_txt, ofile);
	v_txt.clear();


	//Hiragana: 3041–3094, 309b–309e
	v_txt += "Hiragana ;\n";
	v_txt += ToHex(0x3041, 0x3094, term);
	v_txt += ToHex(0x309b, 0x309e, term);

	HexWrite(v_txt, ofile);
	v_txt.clear();


	//Katakana: 30a1–30fe
	v_txt += "Katakana ;\n";
	v_txt += ToHex(0x30a1, 0x30fe, term);

	HexWrite(v_txt, ofile);
	v_txt.clear();


	//Bopmofo: 3105–312c
	v_txt += "Bopmofo ;\n";
	v_txt += ToHex(0x3105, 0x312c, term);

	HexWrite(v_txt, ofile);
	v_txt.clear();


	//Hangul: 1100–1159, 1161–11a2, 11a8–11f9
	v_txt += "Hangul ;\n";
	v_txt += ToHex(0x1100, 0x1159, term);
	v_txt += ToHex(0x1161, 0x11a2, term);
	v_txt += ToHex(0x11a8, 0x11f9, term);

	HexWrite(v_txt, ofile);
	v_txt.clear();


	/*
	CJK Unified Ideographs: f900–fa2d, fb1f–fb36, fb38–fb3c, fb3e, fb40–fb41, fb42–fb44, fb46–fbb1,
	fbd3–fd3f, fd50–fd8f, fd92–fdc7, fdf0–fdfb, fe70–fe72, fe74, fe76–fefc, ff21–ff3a, ff41–ff5a, ff66–ffbe,
	ffc2–ffc7, ffca–ffcf, ffd2–ffd7, ffda–ffdc, 4e00–9fa5
	*/
	v_txt += "CJK Unified Ideographs ;\n";
	v_txt += ToHex(0xf900, 0xfa2d, term);
	v_txt += ToHex(0xfb1f, 0xfb36, term);
	v_txt += ToHex(0xfb38, 0xfb3c, term);
	v_txt += ToHex(0xfb3e, 0xfb3e, term);
	v_txt += ToHex(0xfb40, 0xfb41, term);
	v_txt += ToHex(0xfb42, 0xfb44, term);
	v_txt += ToHex(0xfb46, 0xfbb1, term);
	v_txt += ToHex(0xfbd3, 0xfd3f, term);
	v_txt += ToHex(0xfd50, 0xfd8f, term);
	v_txt += ToHex(0xfd92, 0xfdc7, term);
	v_txt += ToHex(0xfdf0, 0xfdfb, term);
	v_txt += ToHex(0xfe70, 0xfe72, term);
	v_txt += ToHex(0xfe74, 0xfe74, term);
	v_txt += ToHex(0xfe76, 0xfefc, term);
	v_txt += ToHex(0xff21, 0xff3a, term);
	v_txt += ToHex(0xff41, 0xff5a, term);
	v_txt += ToHex(0xff66, 0xffbe, term);
	v_txt += ToHex(0xffc2, 0xffc7, term);
	v_txt += ToHex(0xffca, 0xffcf, term);
	v_txt += ToHex(0xffd2, 0xffd7, term);
	v_txt += ToHex(0xffda, 0xffdc, term);
	v_txt += ToHex(0x4e00, 0x9fa5, term);

	HexWrite(v_txt, ofile);
	v_txt.clear();

	//---
	s_txt = "\0";
	return (char*) s_txt.c_str();	
};


void test_14882_2003_annex_e::SetGrammar(ebnf::DefaultGrammar::Ptr& grammar)
{
	grammar->SetTerm("endl");
	ebnf::Grammar::Map& m = grammar->GetMap();


	//grammar
	//[extendid] - Annex E (normative) Universal-character-names

	//Latin: 00c0–00d6, 00d8–00f6, 00f8–01f5, 01fa–0217, 0250–02a8, 1e00–1e9a, 1ea0–1ef9
	m["00c0-00d6"] = new lex::Range(0x00c0, 0x00d6);
	m["00d8–00f6"] = new lex::Range(0x00d8, 0x00f6);
	m["00f8–01f5"] = new lex::Range(0x00f8, 0x01f5);
	m["01fa–0217"] = new lex::Range(0x01fa, 0x0217);
	m["0250–02a8"] = new lex::Range(0x0250, 0x02a8);
	m["1e00–1e9a"] = new lex::Range(0x1e00, 0x1e9a);
	m["1ea0–1ef9"] = new lex::Range(0x1ea0, 0x1ef9);

	m["Latin"] = 
			m["00c0-00d6"]
		|	m["00d8–00f6"] 
		|	m["00f8–01f5"] 
		|	m["01fa–0217"] 
		|	m["0250–02a8"] 
		|	m["1e00–1e9a"] 
		|	m["1ea0–1ef9"]
		;


	/*
	Greek: 0384, 0388–038a, 038c, 038e–03a1, 03a3–03ce, 03d0–03d6, 03da, 03dc, 03de, 03e0, 03e2–03f3,
	1f00–1f15, 1f18–1f1d, 1f20–1f45, 1f48–1f4d, 1f50–1f57, 1f59, 1f5b, 1f5d, 1f5f–1f7d, 1f80–1fb4,
	1fb6–1fbc, 1fc2–1fc4, 1fc6–1fcc, 1fd0–1fd3, 1fd6–1fdb, 1fe0–1fec, 1ff2–1ff4, 1ff6–1ffc
	*/
	m["0384"] = new lex::Integer(0x0384);
	m["0388–038a"] = new lex::Range(0x0388, 0x038a);
	m["038c"] = new lex::Integer(0x038c);
	m["038e–03a1"] = new lex::Range(0x038e, 0x03a1);
	m["03a3–03ce"] = new lex::Range(0x03a3, 0x03ce);
	m["03d0–03d6"] = new lex::Range(0x03d0, 0x03d6);
	m["03da"] = new lex::Integer(0x03da);
	m["03dc"] = new lex::Integer(0x03dc);
	m["03de"] = new lex::Integer(0x03de);
	m["03e0"] = new lex::Integer(0x03e0);
	m["03e2–03f3"] = new lex::Range(0x03e2, 0x03f3);
	m["1f00–1f15"] = new lex::Range(0x1f00, 0x1f15);
	m["1f18–1f1d"] = new lex::Range(0x1f18, 0x1f1d);
	m["1f20–1f45"] = new lex::Range(0x1f20, 0x1f45);
	m["1f48–1f4d"] = new lex::Range(0x1f48, 0x1f4d);
	m["1f50–1f57"] = new lex::Range(0x1f50, 0x1f57);
	m["1f59"] = new lex::Integer(0x1f59);
	m["1f5b"] = new lex::Integer(0x1f5b);
	m["1f5d"] = new lex::Integer(0x1f5d);
	m["1f5f–1f7d"] = new lex::Range(0x1f5f, 0x1f7d);
	m["1f80–1fb4"] = new lex::Range(0x1f80, 0x1fb4);
	m["1fb6–1fbc"] = new lex::Range(0x1fb6, 0x1fbc);
	m["1fc2–1fc4"] = new lex::Range(0x1fc2, 0x1fc4);
	m["1fc6–1fcc"] = new lex::Range(0x1fc6, 0x1fcc);
	m["1fd0–1fd3"] = new lex::Range(0x1fd0, 0x1fd3);
	m["1fd6–1fdb"] = new lex::Range(0x1fd6, 0x1fdb);
	m["1fe0–1fec"] = new lex::Range(0x1fe0, 0x1fec);
	m["1ff2–1ff4"] = new lex::Range(0x1ff2, 0x1ff4);
	m["1ff6–1ffc"] = new lex::Range(0x1ff6, 0x1ffc);
	
	m["Greek"] = 
			m["0384"] 
		|	m["0388–038a"] 
		|	m["038c"] 
		|	m["038e–03a1"] 
		|	m["03a3–03ce"] 
		|	m["03d0–03d6"] 
		|	m["03da"] 
		|	m["03dc"] 
		|	m["03de"] 
		|	m["03e0"] 
		|	m["03e2–03f3"] 
		|	m["1f00–1f15"] 
		|	m["1f18–1f1d"] 
		|	m["1f20–1f45"] 
		|	m["1f48–1f4d"] 
		|	m["1f50–1f57"] 
		|	m["1f59"] 
		|	m["1f5b"] 
		|	m["1f5d"] 
		|	m["1f5f–1f7d"] 
		|	m["1f80–1fb4"] 
		|	m["1fb6–1fbc"] 
		|	m["1fc2–1fc4"] 
		|	m["1fc6–1fcc"] 
		|	m["1fd0–1fd3"] 
		|	m["1fd6–1fdb"] 
		|	m["1fe0–1fec"] 
		|	m["1ff2–1ff4"] 
		|	m["1ff6–1ffc"]
		;


	/*
	Cyrillic: 0401–040d, 040f–044f, 0451–045c, 045e–0481, 0490–04c4, 04c7–04c8, 04cb–04cc, 04d0–04eb,
			  04ee–04f5, 04f8–04f9
	*/
	m["0401–040d"] = new lex::Range(0x0401, 0x040d);
	m["040f–044f"] = new lex::Range(0x040f, 0x044f);
	m["0451–045c"] = new lex::Range(0x0451, 0x045c);
	m["045e–0481"] = new lex::Range(0x045e, 0x0481);
	m["0490–04c4"] = new lex::Range(0x0490, 0x04c4);
	m["04c7–04c8"] = new lex::Range(0x04c7, 0x04c8);
	m["04cb–04cc"] = new lex::Range(0x04cb, 0x04cc);
	m["04d0–04eb"] = new lex::Range(0x04d0, 0x04eb);
	m["04ee–04f5"] = new lex::Range(0x04ee, 0x04f5);
	m["04f8–04f9"] = new lex::Range(0x04f8, 0x04f9);

	m["Cyrillic"] = 
			m["0401–040d"] 
		|	m["040f–044f"] 
		|	m["0451–045c"] 
		|	m["045e–0481"] 
		|	m["0490–04c4"]
		|	m["04c7–04c8"] 
		|	m["04cb–04cc"] 
		|	m["04d0–04eb"] 
		|	m["04ee–04f5"] 
		|	m["04f8–04f9"]
		;

	
	//Armenian: 0531–0556, 0561–0587
	m["0531–0556"] = new lex::Range(0x0531, 0x0556);
	m["0561–0587"] = new lex::Range(0x0561, 0x0587);

	m["Armenian"] = 
			m["0531–0556"]
		|	m["0561–0587"]
		;

	//Hebrew: 05d0–05ea, 05f0–05f4
	m["05d0–05ea"] = new lex::Range(0x05d0, 0x05ea);
	m["05f0–05f4"] = new lex::Range(0x05f0, 0x05f4);

	m["Hebrew"] =
			m["05d0–05ea"]
		|	m["05f0–05f4"]
		;
	

	
	//Arabic: 0621–063a, 0640–0652, 0670–06b7, 06ba–06be, 06c0–06ce, 06e5–06e7
	m["0621–063a"] = new lex::Range(0x0621, 0x063a);
	m["0640–0652"] = new lex::Range(0x0640, 0x0652);
	m["0670–06b7"] = new lex::Range(0x0670, 0x06b7);
	m["06ba–06be"] = new lex::Range(0x06ba, 0x06be);
	m["06c0–06ce"] = new lex::Range(0x06c0, 0x06ce);
	m["06e5–06e7"] = new lex::Range(0x06e5, 0x06e7);

	m["Arabic"] =
			m["0621–063a"] 
		|	m["0640–0652"] 
		|	m["0670–06b7"] 
		|	m["06ba–06be"] 
		|	m["06c0–06ce"] 
		|	m["06e5–06e7"]
		;
	

	//Devanagari: 0905–0939, 0958–0962
	m["0905–0939"] = new lex::Range(0x0905, 0x0939);
	m["0958–0962"] = new lex::Range(0x0958, 0x0962);


	m["Devanagari"] = 
			m["0905–0939"]
		|	m["0958–0962"]
		;


	
	/*
	Bengali: 0985–098c, 098f–0990, 0993–09a8, 09aa–09b0, 09b2, 09b6–09b9, 09dc–09dd, 09df–09e1,
			 09f0–09f1
	*/
	m["0985–098c"] = new lex::Range(0x0985, 0x098c);
	m["098f–0990"] = new lex::Range(0x098f, 0x0990);
	m["0993–09a8"] = new lex::Range(0x0993, 0x09a8);
	m["09aa–09b0"] = new lex::Range(0x09aa, 0x09b0);
	m["09b2"] = new lex::Integer(0x09b2);
	m["09b6–09b9"] = new lex::Range(0x09b6, 0x09b9);
	m["09dc–09dd"] = new lex::Range(0x09dc, 0x09dd);
	m["09df–09e1"] = new lex::Range(0x09df, 0x09e1);
	m["09f0–09f1"] = new lex::Range(0x09f0, 0x09f1);

	m["Bengali"] = 
			m["0985–098c"] 
		|	m["098f–0990"] 
		|	m["0993–09a8"] 
		|	m["09aa–09b0"] 
		|	m["09b2"] 
		|	m["09b6–09b9"] 
		|	m["09dc–09dd"] 
		|	m["09df–09e1"] 
		|	m["09f0–09f1"]
		;



	/*
	Gurmukhi: 0a05–0a0a, 0a0f–0a10, 0a13–0a28, 0a2a–0a30, 0a32–0a33, 0a35–0a36, 0a38–0a39,
			  0a59–0a5c, 0a5e
	*/
	m["0a05–0a0a"] = new lex::Range(0x0a05, 0x0a0a);
	m["0a0f–0a10"] = new lex::Range(0x0a0f, 0x0a10);
	m["0a13–0a28"] = new lex::Range(0x0a13, 0x0a28);
	m["0a2a–0a30"] = new lex::Range(0x0a2a, 0x0a30);
	m["0a32–0a33"] = new lex::Range(0x0a32, 0x0a33);
	m["0a35–0a36"] = new lex::Range(0x0a35, 0x0a36);
	m["0a38–0a39"] = new lex::Range(0x0a38, 0x0a39);
	m["0a59–0a5c"] = new lex::Range(0x0a59, 0x0a5c);
	m["0a5e"] = new lex::Integer(0x0a5e);


	m["Gurmukhi"] =
			m["0a05–0a0a"] 
		|	m["0a0f–0a10"] 
		|	m["0a13–0a28"] 
		|	m["0a2a–0a30"] 
		|	m["0a32–0a33"] 
		|	m["0a35–0a36"] 
		|	m["0a38–0a39"] 
		|	m["0a59–0a5c"] 
		|	m["0a5e"]
		;



	//Gujarati: 0a85–0a8b, 0a8d, 0a8f–0a91, 0a93–0aa8, 0aaa–0ab0, 0ab2–0ab3, 0ab5–0ab9, 0ae0
	m["0a85–0a8b"] = new lex::Range(0x0a85, 0x0a8b);
	m["0a8d"] = new lex::Integer(0x0a8d);
	m["0a8f–0a91"] = new lex::Range(0x0a8f, 0x0a91);
	m["0a93–0aa8"] = new lex::Range(0x0a93, 0x0aa8);
	m["0aaa–0ab0"] = new lex::Range(0x0aaa, 0x0ab0);
	m["0ab2–0ab3"] = new lex::Range(0x0ab2, 0x0ab3);
	m["0ab5–0ab9"] = new lex::Range(0x0ab5, 0x0ab9);
	m["0ae0"] = new lex::Integer(0x0ae0);


	m["Gujarati"] =
			m["0a85–0a8b"] 
		|	m["0a8d"]
		|	m["0a8f–0a91"] 
		|	m["0a93–0aa8"] 
		|	m["0aaa–0ab0"] 
		|	m["0ab2–0ab3"] 
		|	m["0ab5–0ab9"]
		|	m["0ae0"]
		;



	//Oriya: 0b05–0b0c, 0b0f–0b10, 0b13–0b28, 0b2a–0b30, 0b32–0b33, 0b36–0b39, 0b5c–0b5d, 0b5f–0b61
	m["0b05–0b0c"] = new lex::Range(0x0b05, 0x0b0c);
	m["0b0f–0b10"] = new lex::Range(0x0b0f, 0x0b10);
	m["0b13–0b28"] = new lex::Range(0x0b13, 0x0b28);
	m["0b2a–0b30"] = new lex::Range(0x0b2a, 0x0b30);
	m["0b32–0b33"] = new lex::Range(0x0b32, 0x0b33);
	m["0b36–0b39"] = new lex::Range(0x0b36, 0x0b39);
	m["0b5c–0b5d"] = new lex::Range(0x0b5c, 0x0b5d);
	m["0b5f–0b61"] = new lex::Range(0x0b5f, 0x0b61);

	m["Oriya"] =
			m["0b05–0b0c"] 
		|	m["0b0f–0b10"] 
		|	m["0b13–0b28"] 
		|	m["0b2a–0b30"] 
		|	m["0b32–0b33"] 
		|	m["0b36–0b39"] 
		|	m["0b5c–0b5d"] 
		|	m["0b5f–0b61"]
		;
	
	/*
	Tamil: 0b85–0b8a, 0b8e–0b90, 0b92–0b95, 0b99–0b9a, 0b9c, 0b9e–0b9f, 0ba3–0ba4, 0ba8–0baa,
		   0bae–0bb5, 0bb7–0bb9
	*/
	m["0b85–0b8a"] = new lex::Range(0x0b85, 0x0b8a);
	m["0b8e–0b90"] = new lex::Range(0x0b8e, 0x0b90);
	m["0b92–0b95"] = new lex::Range(0x0b92, 0x0b95);
	m["0b99–0b9a"] = new lex::Range(0x0b99, 0x0b9a);
	m["0b9c"] = new lex::Integer(0x0b9c);
	m["0b9e–0b9f"] = new lex::Range(0x0b9e, 0x0b9f);
	m["0ba3–0ba4"] = new lex::Range(0x0ba3, 0x0ba4);
	m["0ba8–0baa"] = new lex::Range(0x0ba8, 0x0baa);
	m["0bae–0bb5"] = new lex::Range(0x0bae, 0x0bb5);
	m["0bb7–0bb9"] = new lex::Range(0x0bb7, 0x0bb9);

	m["Tamil"] =
			m["0b85–0b8a"] 
		|	m["0b8e–0b90"] 
		|	m["0b92–0b95"] 
		|	m["0b99–0b9a"] 
		|	m["0b9c"]
		|	m["0b9e–0b9f"] 
		|	m["0ba3–0ba4"] 
		|	m["0ba8–0baa"] 
		|	m["0bae–0bb5"] 
		|	m["0bb7–0bb9"]
		;


	
	//Telugu: 0c05–0c0c, 0c0e–0c10, 0c12–0c28, 0c2a–0c33, 0c35–0c39, 0c60–0c61
	m["0c05–0c0c"] = new lex::Range(0x0c05, 0x0c0c);
	m["0c0e–0c10"] = new lex::Range(0x0c0e, 0x0c10);
	m["0c12–0c28"] = new lex::Range(0x0c12, 0x0c28);
	m["0c2a–0c33"] = new lex::Range(0x0c2a, 0x0c33);
	m["0c35–0c39"] = new lex::Range(0x0c35, 0x0c39);
	m["0c60–0c61"] = new lex::Range(0x0c60, 0x0c61);

	m["Telugu"] =
			m["0c05–0c0c"] 
		|	m["0c0e–0c10"] 
		|	m["0c12–0c28"] 
		|	m["0c2a–0c33"] 
		|	m["0c35–0c39"] 
		|	m["0c60–0c61"]
		;


	//Kannada: 0c85–0c8c, 0c8e–0c90, 0c92–0ca8, 0caa–0cb3, 0cb5–0cb9, 0ce0–0ce1
	m["0c85–0c8c"] = new lex::Range(0x0c85, 0x0c8c);
	m["0c8e–0c90"] = new lex::Range(0x0c8e, 0x0c90);
	m["0c92–0ca8"] = new lex::Range(0x0c92, 0x0ca8);
	m["0caa–0cb3"] = new lex::Range(0x0caa, 0x0cb3);
	m["0cb5–0cb9"] = new lex::Range(0x0cb5, 0x0cb9);
	m["0ce0–0ce1"] = new lex::Range(0x0ce0, 0x0ce1);


	m["Kannada"] = 
			m["0c85–0c8c"] 
		|	m["0c8e–0c90"] 
		|	m["0c92–0ca8"] 
		|	m["0caa–0cb3"] 
		|	m["0cb5–0cb9"] 
		|	m["0ce0–0ce1"]
		;


	//Malayalam: 0d05–0d0c, 0d0e–0d10, 0d12–0d28, 0d2a–0d39, 0d60–0d61
	m["0d05–0d0c"] = new lex::Range(0x0d05, 0x0d0c);
	m["0d0e–0d10"] = new lex::Range(0x0d0e, 0x0d10);
	m["0d12–0d28"] = new lex::Range(0x0d12, 0x0d28);
	m["0d2a–0d39"] = new lex::Range(0x0d2a, 0x0d39);
	m["0d60–0d61"] = new lex::Range(0x0d60, 0x0d61);

	m["Malayalam"] =
			m["0d05–0d0c"] 
		|	m["0d0e–0d10"] 
		|	m["0d12–0d28"] 
		|	m["0d2a–0d39"] 
		|	m["0d60–0d61"]
		;
					

	//Thai: 0e01–0e30, 0e32–0e33, 0e40–0e46, 0e4f–0e5b
	m["0e01–0e30"] = new lex::Range(0x0e01, 0x0e30);
	m["0e32–0e33"] = new lex::Range(0x0e32, 0x0e33);
	m["0e40–0e46"] = new lex::Range(0x0e40, 0x0e46);
	m["0e4f–0e5b"] = new lex::Range(0x0e4f, 0x0e5b);

	m["Thai"] =
			m["0e01–0e30"] 
		|	m["0e32–0e33"] 
		|	m["0e40–0e46"] 
		|	m["0e4f–0e5b"]
		;

	
	/*
	Lao: 0e81–0e82, 0e84, 0e87, 0e88, 0e8a, 0e8d, 0e94–0e97, 0e99–0e9f, 0ea1–0ea3, 0ea5, 0ea7, 0eaa, 0eab,
		 0ead–0eb0, 0eb2, 0eb3, 0ebd, 0ec0–0ec4, 0ec6
	*/
	m["0e81–0e82"] = new lex::Range(0x0e81, 0x0e82);
	m["0e84"] = new lex::Integer(0x0e84);
	m["0e87"] = new lex::Integer(0x0e87);
	m["0e88"] = new lex::Integer(0x0e88);
	m["0e8a"] = new lex::Integer(0x0e8a);
	m["0e8d"] = new lex::Integer(0x0e8d);
	m["0e94–0e97"] = new lex::Range(0x0e94, 0x0e97);
	m["0e99–0e9f"] = new lex::Range(0x0e99, 0x0e9f);
	m["0ea1–0ea3"] = new lex::Range(0x0ea1, 0x0ea3);
	m["0ea5"] = new lex::Integer(0x0ea5);
	m["0ea7"] = new lex::Integer(0x0ea7);
	m["0eaa"] = new lex::Integer(0x0eaa);
	m["0eab"] = new lex::Integer(0x0eab);
	m["0ead–0eb0"] = new lex::Range(0x0ead, 0x0eb0);
	m["0eb2"] = new lex::Integer(0x0eb2);
	m["0eb3"] = new lex::Integer(0x0eb3);
	m["0ebd"] = new lex::Integer(0x0ebd);
	m["0ec0–0ec4"] = new lex::Range(0x0ec0, 0x0ec4);
	m["0ec6"] = new lex::Integer(0x0ec6);


	m["Lao"] =
			m["0e81–0e82"] 
		|	m["0e84"] 
		|	m["0e87"] 
		|	m["0e88"] 
		|	m["0e8a"] 
		|	m["0e8d"] 
		|	m["0e94–0e97"] 
		|	m["0e99–0e9f"] 
		|	m["0ea1–0ea3"] 
		|	m["0ea5"] 
		|	m["0ea7"] 
		|	m["0eaa"] 
		|	m["0eab"] 
		|	m["0ead–0eb0"] 
		|	m["0eb2"] 
		|	m["0eb3"] 
		|	m["0ebd"] 
		|	m["0ec0–0ec4"] 
		|	m["0ec6"]
		;


	//Georgian: 10a0–10c5, 10d0–10f6
	m["10a0–10c5"] = new lex::Range(0x10a0, 0x10c5);
	m["10d0–10f6"] = new lex::Range(0x10d0, 0x10f6);

	m["Georgian"] = 
			m["10a0–10c5"]
		|	m["10d0–10f6"]
		;



	//Hiragana: 3041–3094, 309b–309e
	m["3041–3094"] = new lex::Range(0x3041, 0x3094);
	m["309b–309e"] = new lex::Range(0x309b, 0x309e);

	m["Hiragana"] =
			m["3041–3094"]
		|	m["309b–309e"]
		;

	//Katakana: 30a1–30fe
	m["30a1–30fe"] = new lex::Range(0x30a1, 0x30fe);
	m["Katakana"] = m["30a1–30fe"];



	//Bopmofo: 3105–312c
	m["3105–312c"] = new lex::Range(0x3105, 0x312c);
	m["Bopmofo"] = m["3105–312c"];



	//Hangul: 1100–1159, 1161–11a2, 11a8–11f9
	m["1100–1159"] = new lex::Range(0x1100, 0x1159);
	m["1161–11a2"] = new lex::Range(0x1161, 0x11a2);
	m["11a8–11f9"] = new lex::Range(0x11a8, 0x11f9);

	m["Hangul"] =
			m["1100–1159"]
		|	m["1161–11a2"]
		|	m["11a8–11f9"]
		;


	
	/*
	CJK Unified Ideographs: f900–fa2d, fb1f–fb36, fb38–fb3c, fb3e, fb40–fb41, fb42–fb44, fb46–fbb1,
	fbd3–fd3f, fd50–fd8f, fd92–fdc7, fdf0–fdfb, fe70–fe72, fe74, fe76–fefc, ff21–ff3a, ff41–ff5a, ff66–ffbe,
	ffc2–ffc7, ffca–ffcf, ffd2–ffd7, ffda–ffdc, 4e00–9fa5
	*/
	m["f900–fa2d"] = new lex::Range(0xf900, 0xfa2d);
	m["fb1f–fb36"] = new lex::Range(0xfb1f, 0xfb36);
	m["fb38–fb3c"] = new lex::Range(0xfb38, 0xfb3c);
	m["fb3e"] = new lex::Integer(0xfb3e);
	m["fb40–fb41"] = new lex::Range(0xfb40, 0xfb41);
	m["fb42–fb44"] = new lex::Range(0xfb42, 0xfb44);
	m["fb46–fbb1"] = new lex::Range(0xfb46, 0xfbb1);
	m["fbd3–fd3f"] = new lex::Range(0xfbd3, 0xfd3f);
	m["fd50–fd8f"] = new lex::Range(0xfd50, 0xfd8f);
	m["fd92–fdc7"] = new lex::Range(0xfd92, 0xfdc7);
	m["fdf0–fdfb"] = new lex::Range(0xfdf0, 0xfdfb);
	m["fe70–fe72"] = new lex::Range(0xfe70, 0xfe72);
	m["fe74"] = new lex::Integer(0xfe74);
	m["fe76–fefc"] = new lex::Range(0xfe76, 0xfefc);
	m["ff21–ff3a"] = new lex::Range(0xff21, 0xff3a);
	m["ff41–ff5a"] = new lex::Range(0xff41, 0xff5a);
	m["ff66–ffbe"] = new lex::Range(0xff66, 0xffbe);
	m["ffc2–ffc7"] = new lex::Range(0xffc2, 0xffc7);
	m["ffca–ffcf"] = new lex::Range(0xffca, 0xffcf);
	m["ffd2–ffd7"] = new lex::Range(0xffd2, 0xffd7);
	m["ffda–ffdc"] = new lex::Range(0xffda, 0xffdc);
	m["4e00–9fa5"] = new lex::Range(0x4e00, 0x9fa5);

	m["CJK Unified Ideographs"] =
			m["f900–fa2d"]
		|	m["fb1f–fb36"] 
		|	m["fb38–fb3c"] 
		|	m["fb3e"] 
		|	m["fb40–fb41"] 
		|	m["fb42–fb44"] 
		|	m["fb46–fbb1"] 
		|	m["fbd3–fd3f"] 
		|	m["fd50–fd8f"] 
		|	m["fd92–fdc7"] 
		|	m["fdf0–fdfb"]
		|	m["fe70–fe72"] 
		|	m["fe74"] 
		|	m["fe76–fefc"]
		|	m["ff21–ff3a"] 
		|	m["ff41–ff5a"] 
		|	m["ff66–ffbe"] 
		|	m["ffc2–ffc7"] 
		|	m["ffca–ffcf"] 
		|	m["ffd2–ffd7"] 
		|	m["ffda–ffdc"]
		|	m["4e00–9fa5"]
		;


	m["universal-character-name"] =
			m["Latin"]
		|	m["Greek"]
		|	m["Cyrillic"]
		|	m["Armenian"]
		|	m["Hebrew"]
		|	m["Arabic"]
		|	m["Devanagari"]
		|	m["Bengali"]
		|	m["Gurmukhi"]
		|	m["Gujarati"]
		|	m["Oriya"]
		|	m["Tamil"]
		|	m["Telugu"]
		|	m["Kannada"]
		|	m["Malayalam"]
		|	m["Thai"]
		|	m["Lao"]
		|	m["Georgian"]
		|	m["Hiragana"]
		|	m["Katakana"]
		|	m["Bopmofo"]
		|	m["Hangul"]
		|	m["CJK Unified Ideographs"]
		;


	m["start"] = 
			~m["gaps"]
		&&	RR(1, 100, m["universal-character-name"])
		&&	m[";"]
		&&	~m["gaps"]
		;


};


void test_14882_2003_annex_e::SetSyntax(lex::Base::Syntax& /*ref*/)
{	

	////decimal
	//const char* p1[]={"0",";"};
	//const int a1[]={TA_TERMINAL, TA_TERMINAL};

	////decimal
	//AddAsProduction(ref, p1, a1, sizeof(p1)/sizeof(p1[0]));
	//

};



void test_14882_2003_annex_e::SetReports(lex::Base::Reports& /*reps*/)
{

};




void test_14882_2003_annex_e::AddAsProduction(lex::Base::Syntax& ref, const char* p[], const int a[], int lim)
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



misc::string test_14882_2003_annex_e::ToHex(int beg, int end, const misc::string& term)const
{	
	misc::string hex_s;
	for(int i=beg; i<=end; ++i)
	{				
		hex_s += (misc::string::value_type)i;
	}
	hex_s += term;
	return hex_s;
};


void test_14882_2003_annex_e::HexWrite(const misc::string& txtdata, misc::ofstream& ofile)
{
	ofile << txtdata.c_str();
};






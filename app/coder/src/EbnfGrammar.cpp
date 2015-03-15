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


#include "EbnfGrammar.hpp"

//parsers
#include "Alias.hpp"
#include "IsNotEq.hpp"
#include "IsEq.hpp"
#include "HasNot.hpp"
#include "Has.hpp"
#include "Group.hpp"
#include "Integer.hpp"
#include "False.hpp"
#include "Optional.hpp"
#include "Quote.hpp"
#include "Range.hpp"
#include "Repeat.hpp"
#include "Repetition.hpp"
#include "Delay.hpp"
#include "Null.hpp"


namespace ebnf
{
	
	EbnfGrammar::EbnfGrammar()
	{

		Null();
		Letter();
		Digit();
		Defgraph();
		Defnongraph();
		Gap();
		All();
		Comment();
		Terminal();
		Quote1();
		Quote2();
		Range();
		Identifier();
		Operations();
		Production();	

		//last row
		Syntax();

		m_map["start"] = m_map["syntax"];

		m_iniParams.SetGLR(false);
		m_iniParams.SetError(false);

	};

	const lex::IniParams& EbnfGrammar::GetIniParams()const
	{
		return m_iniParams;
	};

	lex::Base::Ptr EbnfGrammar::GetStart()
	{
		return m_map["start"];
	};


	lex::Base::Ptr EbnfGrammar::GetTerm()
	{
		return m_map[";"];
	};


	//private
	void EbnfGrammar::Null()
	{
		Map& m=m_map;
		m["null"] = new lex::Null();
	};

	void EbnfGrammar::Letter()
	{
		/*letter*/
		Map& m = m_map;//short form 'm'
		m["a_z"] = new lex::Range((int)'a', (int)'z');
		m["A_Z"] = new lex::Range((int)'A', (int)'Z');
		m["a_zA_Z"] = m["a_z"] | m["A_Z"];
	};

	void EbnfGrammar::Digit()
	{
		/*decimal digit*/
		Map& m = m_map;//short form 'm'
		m["0_9"] = new lex::Range((int)'0', (int)'9');
	};


	void EbnfGrammar::Defgraph()
	{
		/*defining graphic characters in ASCII range less digits and letters*/
		Map& m = m_map;		
		m["!"] = new lex::Integer((int)'!');
		m["\""] = new lex::Integer((int)'"');
		m["#"] = new lex::Integer((int)'#');
		m["$"] = new lex::Integer((int)'$');
		m["%"] = new lex::Integer((int)'%');
		m["&"] = new lex::Integer((int)'&');
		m["'"] = new lex::Integer((int)'\'');
		m["("] = new lex::Integer((int)'(');
		m[")"] = new lex::Integer((int)')');
		m["*"] = new lex::Integer((int)'*');
		m["+"] = new lex::Integer((int)'+');
		m[","] = new lex::Integer((int)',');
		m["-"] = new lex::Integer((int)'-');
		m["."] = new lex::Integer((int)'.');
		m["/"] = new lex::Integer((int)'/');
		m[":"] = new lex::Integer((int)':');
		m[";"] = new lex::Integer((int)';');
		m["<"] = new lex::Integer((int)'<');
		m["="] = new lex::Integer((int)'=');
		m[">"] = new lex::Integer((int)'>');
		m["?"] = new lex::Integer((int)'?');
		m["@"] = new lex::Integer((int)'@');
		m["["] = new lex::Integer((int)'[');
		m["\\"] = new lex::Integer((int)'\\');
		m["]"] = new lex::Integer((int)']');
		m["^"] = new lex::Integer((int)'^');
		m["_"] = new lex::Integer((int)'_');
		m["`"] = new lex::Integer((int)'`');
		m["{"] = new lex::Integer((int)'{');
		m["|"] = new lex::Integer((int)'|');
		m["}"] = new lex::Integer((int)'}');
		m["~"] = new lex::Integer((int)'~');


		m["graphic"] = m["!"]
			|	m["\""]
			|	m["#"]
			|	m["$"]
			|	m["%"]
			|	m["&"]
			|	m["'"]
			|	m["("]
			|	m[")"]
			|	m["*"]
			|	m["+"]
			|	m[","]
			|	m["-"]
			|	m["."]
			|	m["/"]
			|	m[":"]
			|	m[";"]
			|	m["<"]
			|	m["="]
			|	m[">"]
			|	m["?"]
			|	m["@"]
			|	m["["]
			|	m["\\"]
			|	m["]"]
			|	m["^"]
			|	m["_"]
			|	m["`"]
			|	m["{"]
			|	m["|"]
			|	m["}"]
			|	m["~"];

	};


	void EbnfGrammar::Defnongraph()
	{
		Map& m = m_map;
		m["space"] = new lex::Integer((int)' ');
		m["tab"] = new lex::Integer((int)'\t');
		m["vtab"] = new lex::Integer((int)'\v');
		m["endl"] = new lex::Integer((int)'\n');


		/*subset*/
		m["non_graphic"] = 
			m["space"] 
			|	m["tab"]
			|	m["vtab"]
			|	m["endl"] ;
	};


	void EbnfGrammar::Gap()
	{
		Map& m=m_map;
		m["gap"] = m["non_graphic"] ;
		m["gaps"] = 0*m["gap"];
	};


	void EbnfGrammar::All()
	{
		Map& m = m_map;
		m["all"] = 
			m["a_zA_Z"] 
			|	m["0_9"]	
			|	m["graphic"]
			|	m["non_graphic"];

	};

	void EbnfGrammar::Comment()
	{
		Map& m = m_map;

		m["(*"] = m["("] & m["*"];
		m["*)"] = m["*"] & m[")"];

		m["d_pass1"] = new lex::Delay(m, "pass1", 250);		

		m["**"] = m["*"] & m["*"];		
		m["t1"] = (2*m["all"] != m["*)"]) ;		

		m["pass1"] =
			0*(10*m["all"] - m["*"]) &
			0*(   m["all"] - m["*"]) &			
			(								
				(!m["t1"] & m["null"]) |
				(m["all"] & m["d_pass1"])
			)
			;
		
		//d_pass1 and pass1 should not have F_BRKSTR flag, otherwise exception is thrown in Delay::select
		m["comment_string"] = new lex::Group( m["pass1"] );		
		m["comment"] = m["(*"] && m["comment_string"] && m["*)"];

		m["extra"] = 0*(m["gaps"] && 0*m["comment"] && m["gaps"]);
	};

	void EbnfGrammar::Terminal()
	{
		Map& m=m_map;
		m["term"] = ( m["a_zA_Z"] | m["_"] ) & 0*( m["a_zA_Z"] | m["0_9"] | m["_"] );
		m["term"]->Set(lex::Base::F_BRKSTR);
	};


	void EbnfGrammar::Quote1()
	{
		Map& m=m_map;
		m["quote1"] = m["'"] & (m["all"] - m["'"]) & m["'"];
		m["quote1"]->Set(lex::Base::F_BRKSTR);
	};

	void EbnfGrammar::Quote2()
	{
		Map& m=m_map;
		m["quote2"] = m["\""] & 0*(m["all"] - m["\""]) & m["\""];
		m["quote2"]->Set(lex::Base::F_BRKSTR);
	};

	
	void EbnfGrammar::Range()
	{
		Map& m=m_map;
		//rule with no gaps
		m["range"] = m["quote1"] && m[":"] && m["quote1"];
	};


	void EbnfGrammar::Identifier()
	{
		Map& m=m_map;
		m["identifier"] = 
			m["range"] || m["quote1"] || m["quote2"] || m["term"];
	};


	void EbnfGrammar::Operations()
	{
		Map& m=m_map;
		m["d_t_ooop"] = new lex::Delay(m, "t_ooop", 250);//order of operations
		

		m["&&"] = m["&"] & m["&"];
		m["||"] = m["|"] & m["|"];
		m["=="] = m["="] & m["="];
		m["!="] = m["!"] & m["="];


		//operator at right side of quote1
		m["q1_lop"] = 
			m["extra"] &&
			m["quote1"] && 
			m["extra"] &&
			(m["&&"] || m["||"] || m["&"] || m["|"]);

		//operator at right side of quote2
		m["q2_lop"] =
			m["extra"] &&
			m["quote2"] &&
			m["extra"] &&
			(m["&&"] || m["||"] || m["=="] || m["!="] || m["&"] || m["|"] || m["+"] || m["-"]);

		//operator at right side of term
		m["term_lop"] =
			m["extra"] &&
			m["term"] &&
			m["extra"] &&
			(m["&&"] || m["||"] || m["=="] || m["!="] || m["&"] || m["|"] || m["+"] || m["-"]);

		//operator at right side of range
		m["range_lop"] =
			m["extra"] &&
			m["range"] &&
			m["extra"] &&
			(m["&&"] || m["||"] || m["&"] || m["|"]);

		m["repeat_lop"] = 
			m["extra"] &&
			(m["0_9"] & 0*m["0_9"]) &&
			m["gaps"] &&
			m["*"] ;

		//unary operator
		m["negation_lop"] =
			m["extra"] &&
			m["!"] ;

		//operators allowed by left operand
		m["t_lop"] =
			m["q1_lop"] || m["q2_lop"] || m["term_lop"] || m["range_lop"] || m["repeat_lop"] || m["negation_lop"] ;

		m["t_rop"] =
			m["extra"] &&
			(m["&&"] || m["||"] || m["!="] || m["=="] || m["&"] || m["|"] || m["+"] || m["-"]) &&
			m["extra"] &&
			m["d_t_ooop"];

		//precedence operators
		m["t_pop"] =
			m["extra"] &&
			(m["("] && m["d_t_ooop"] && m["extra"]	&& m[")"]) ||
			(m["["] && m["d_t_ooop"] && m["extra"]	&& m["]"]) ||
			(m["{"] && m["d_t_ooop"] && m["extra"]	&& m["}"]) ;
			

		m["t_ooop"] =
			m["extra"] &&
			(0*m["t_lop"]	&& m["extra"] && m["identifier"]	&& m["extra"] && 0*m["t_rop"] ) ||
			(0*m["t_lop"]	&& m["extra"] && m["t_pop"]		&& m["extra"] && 0*m["t_rop"] );


		m["Operations"] = m["t_ooop"] && m["extra"] && m[";"] ;
	};

	
	void EbnfGrammar::Production()
	{
		Map& m=m_map;

		m["Production"] = 	
			m["extra"] && 
			m["term"] && 
			m["extra"] && 
			m["="] &&
			m["extra"] &&
			m["Operations"]			
		;
	};

	//last row
	void EbnfGrammar::Syntax()
	{
		Map& m = m_map;		
		m["syntax"] = m["Production"] || m["extra"] ;
		m["syntax"]->Set(lex::Base::F_BRKSTR);

	};



};//namespace
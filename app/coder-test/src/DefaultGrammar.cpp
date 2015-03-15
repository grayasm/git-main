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



#include "DefaultGrammar.hpp"



namespace ebnf
{


	DefaultGrammar::DefaultGrammar()
	{		
		letter();
		digit();
		other();	
		gaps();
		nogap();		

		m_iniParams.SetGLR(false);
		m_iniParams.SetError(false);
	};

	const lex::IniParams& DefaultGrammar::GetIniParams()const
	{
		return m_iniParams;
	};

	lex::Base::Ptr DefaultGrammar::GetStart()
	{
		Map& m = m_map;
		m["start"]->Set(lex::Base::F_BRKSTR);
		return m_map["start"];
	};


	lex::Base::Ptr DefaultGrammar::GetTerm()
	{
		return m_map[m_term];
	};

	void DefaultGrammar::SetTerm(const std::string& term)
	{
		m_term = term;
	};

	DefaultGrammar::Map& DefaultGrammar::GetMap()
	{
		return m_map;
	};


	void DefaultGrammar::letter()
	{
		Map& m = m_map;

		m["a_z"] = new lex::Range((int)'a', (int)'z');
		m["A_Z"] = new lex::Range((int)'A', (int)'Z');
		m["a_zA_Z"] = m["a_z"] | m["A_Z"];		
	};

	void DefaultGrammar::digit()
	{
		Map& m = m_map;
		m["0_9"] = new lex::Range((int)'0', (int)'9');
	}

	void DefaultGrammar::other()
	{
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
		m["space"] = new lex::Integer((int)' ');
		m["tab"] = new lex::Integer((int)'\t');
		m["endl"] = new lex::Integer((int)'\n');
		m["vtab"] = new lex::Integer((int)'\v');
		m["feed"] = new lex::Integer((int)'\f');
		m["ret"] = new lex::Integer((int)'\r');

		m["other"] =
			m["!"] 
			| m["\""] 
			| m["#"] 
			| m["$"] 
			| m["%"] 
			| m["&"] 
			| m["'"] 
			| m["("] 
			| m[")"] 
			| m["*"] 
			| m["+"]
			| m[","] 
			| m["-"]
			| m["."] 
			| m["/"] 
			| m[":"]
			| m[";"]
			| m["<"]
			| m["="]
			| m[">"]
			| m["?"] 
			| m["@"]
			| m["["] 
			| m["\\"]
			| m["]"] 
			| m["^"]
			| m["_"] 
			| m["`"]
			| m["{"]
			| m["|"] 
			| m["}"] 
			| m["~"] 
			| m["space"]
			| m["tab"] 
			| m["endl"] 
			| m["vtab"]
			| m["feed"]
			| m["ret"] ;
	
	};

	void DefaultGrammar::gaps()
	{
		Map& m = m_map;
		m["gap"] = m["space"] | m["endl"] | m["tab"] | m["vtab"] | m["ret"];
		m["gaps"] = 0 * m["gap"];
	};

	void DefaultGrammar::nogap()
	{
		Map& m = m_map;
		m["nogap"] = m["a_zA_Z"] | m["0_9"] | (m["other"] - m["gap"]);
	};	

};//namespace

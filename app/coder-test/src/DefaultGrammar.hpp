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


#ifndef __TestGrammar_hpp__
#define __TestGrammar_hpp__


#include "Grammar.hpp"
#include "lexer_inc.hpp"


namespace ebnf
{
		
	//Describes a grammar that is generic enough to be extended by any test as appropriate. 
	class DefaultGrammar : public Grammar
	{
	public:
		typedef misc::autoptr<DefaultGrammar> Ptr;
	
	public:
		DefaultGrammar();	
		//virtual
		const lex::IniParams& GetIniParams()const;
		lex::Base::Ptr GetStart();
		lex::Base::Ptr GetTerm();

		//custom
		void SetTerm(const std::string& term);
		Map& GetMap();

	private:	
		void letter();
		void digit();
		void other();
		void gaps();
		void nogap();

	private:
		Map m_map;		
		//custom rule terminal (error recovery)
		std::string		m_term;
		lex::IniParams m_iniParams;

	};

};//namespace




#endif//__TestGrammar_hpp__




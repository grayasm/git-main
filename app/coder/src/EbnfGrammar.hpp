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


#ifndef __EbnfGrammar_hpp__
#define __EbnfGrammar_hpp__


#include "Grammar.hpp"


namespace ebnf
{

	class EbnfGrammar : public Grammar
	{
	public:
		typedef misc::autoptr<EbnfGrammar> Ptr;


	public:		
		EbnfGrammar();	
		const lex::IniParams& GetIniParams()const;
		lex::Base::Ptr GetStart();
		lex::Base::Ptr GetTerm();

	private:
		void Null();
		void Letter();
		void Digit();
		void Defgraph();
		void Defnongraph();
		void Gap();
		void All();
		void Comment();
		void Terminal();		
		void Quote1();
		void Quote2();
		void Range();
		void Identifier();
		void Operations();
		void Production();
		

		//last row
		void Syntax();
		
	private:
		Map m_map;
		lex::IniParams m_iniParams;
	};

}





#endif//__EbnfGrammar_hpp__



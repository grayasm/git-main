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


#ifndef __LexerInput_hpp__
#define __LexerInput_hpp__


#include "Base.hpp"
#include "Grammar.hpp"


namespace lex
{
	class LexerInput
	{
	public:
		LexerInput(const std::string& fileName, const ebnf::Grammar::Ptr& grammar);
		~LexerInput();

		void operator >> (lex::Base::Syntax& syntax);


		const lex::Base::Reports& GetReports()const;
		void ClearReports();

	private:
		std::string				m_fileName;
		lex::InputFile::Ptr		m_inputFile;
		ebnf::Grammar::Ptr		m_grammar;
		lex::Base::Reports		m_reports;

	};//class


};//namespace


#endif//__LexerInput_hpp__


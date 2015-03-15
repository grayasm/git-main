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


#include "LexerInput.hpp"
#include "Lexer.hpp"


namespace lex
{

	LexerInput::LexerInput(const std::string& fileName, const ebnf::Grammar::Ptr& grammar)
	{
		m_fileName = fileName;
		m_inputFile = new lex::InputFile(m_fileName.c_str(), 4);
		m_grammar = grammar;


		lex::Lexer::Inst().Initialize(m_grammar->GetStart(), m_grammar->GetTerm(), m_grammar->GetIniParams());
	};

	LexerInput::~LexerInput()
	{
		lex::Lexer::Destroy();
	};

	void LexerInput::operator >> (lex::Base::Syntax& syntax)
	{
		lex::InputFile& in = *m_inputFile;
		lex::Lexer::Inst().CheckFile(in, syntax, m_reports);		
	};


	const lex::Base::Reports& LexerInput::GetReports()const
	{
		return m_reports;
	};

	void LexerInput::ClearReports()
	{
		m_reports.clear();
	};

}
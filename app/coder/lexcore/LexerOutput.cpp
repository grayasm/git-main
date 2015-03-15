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




#include "LexerOutput.hpp"


namespace lex
{

	LexerOutput::LexerOutput(const std::string& fileName)
	{		
		m_fileName = fileName;
		m_ostream .open(m_fileName.c_str(), std::ios_base::out | std::ios_base::trunc);
	};

	LexerOutput::~LexerOutput()
	{
		if(m_ostream.is_open())
			m_ostream.close();
		
	};

	LexerOutput& LexerOutput::operator << (const lex::Base::Syntax& grammar)
	{
		for(lex::Base::Syntax::const_iterator beg = grammar.begin(); beg != grammar.end(); ++beg)
		{
			const lex::Base::Production& prod = (*beg);
			*this << prod;
			m_ostream << "\n";
		}//for
		return *this;
	};

	LexerOutput& LexerOutput::operator << (const lex::Base::Reports& reports)
	{		
		for(lex::Base::Reports::const_iterator repb = reports.begin(); repb != reports.end(); ++repb)
		{
			const lex::Report& report = *repb;
			*this << report;
			m_ostream << "\n";
		}//for
		return *this;
	};


	LexerOutput& LexerOutput::operator << (const lex::Base::Production& production)
	{
		for(lex::Base::Production::const_iterator beg = production.begin(); beg != production.end(); ++beg)
		{
			const lex::Token& str = *beg;
			m_ostream << str.GetToken().c_str() << "{" << str.GetAttr() << "}";
		}//for
		return *this;
	};

	LexerOutput& LexerOutput::operator << (const lex::Report& rep)
	{
		m_ostream << "{fp= " << rep.GetFilePos() << " ln=" << rep.GetRow() << " col= " << rep.GetCol() << "} " ;
		const lex::Report::ErrorList& errors = rep.GetErrorList();
		for(lex::Report::ErrorList::const_iterator errb = errors.begin(); errb != errors.end(); ++errb)
		{
			const lex::Error& err = *errb;
			m_ostream << err.GetMsg().c_str() << " {" << err.GetLevel() << "} ";
		}//for
		return *this;
	};
};//namespace



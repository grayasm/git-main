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



#include "Report.hpp"

//lib
#include "exception.hpp"



namespace lex
{
	Report::Report()
	{
		Init();
	};

	Report::~Report()
	{
	};

	Report::Report(const Report& tc)
	{
		Init();
		*this=tc;
	};


	Report& Report::operator = (const Report& tc)
	{
		if(this != &tc)
		{			
			m_errorList = tc.m_errorList;
			m_fpos = tc.m_fpos;
			m_row = tc.m_row;
			m_col = tc.m_col;
		}
		return *this;
	};


	bool Report::report(const lex::Error& error, size_t pos, size_t row, size_t col)
	{
		//valid error ?
		if(error.GetMsg().empty() || error.GetLevel() == 0) 
			return false;

		//depth of new first error ?
		if(m_fpos < pos || (m_fpos == 0 && pos == 0))
		{
			m_errorList.clear();
			m_errorList.push_back(error);
			m_fpos = pos;
			m_row = row;
			m_col = col;
			return true;
		}//if
		
		if(m_errorList.empty())
			throw misc::exception("size_t pos == 0 or is negative. throw for testing");

		//include this error in list if depth allows
		const lex::Error& lastErr = *m_errorList.begin();
		if(lastErr.GetLevel() - (int)m_errorList.size() > 0)
		{
			m_errorList.push_back(error);
			return true;
		}//if

		return false;
	};


	const Report::ErrorList& Report::GetErrorList()const
	{
		return m_errorList;
	};

	size_t Report::GetFilePos()const
	{
		return m_fpos;
	};

	size_t Report::GetRow()const
	{
		return m_row;
	};

	size_t Report::GetCol()const
	{
		return m_col;
	};
	
	void Report::Init()
	{
		m_errorList.clear();
		m_fpos=0;
		m_row=0;
		m_col=0;
	};

};//namespace




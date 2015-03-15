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

#include "Error.hpp"

namespace lex
{
	Error::~Error()
	{
	};


	Error::Error()
	{
		Init();
	};

	Error::Error(const misc::string& msg, int level)
	{
		Init();
		
		m_message = msg;
		m_level = level;
	};

	Error::Error(const Error& tc)
	{
		Init();
		*this=tc;
	};

	Error& Error::operator=(const Error& tc)
	{
		if(this!=&tc)
		{
			m_message = tc.m_message;
			m_level = tc.m_level;
		}
		return *this;
	};

	void Error::SetMsg(const misc::string& msg)
	{
		m_message = msg;
	};

	const misc::string& Error::GetMsg()const
	{
		return m_message;
	};

	void Error::SetLevel(int level)
	{
		m_level = level;
	};

	int Error::GetLevel()const
	{
		return m_level;
	};

	void Error::Init()
	{
		m_level = 0;
		m_message = "";		
	};

};


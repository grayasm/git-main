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



#include "Token.hpp"


namespace lex
{
	Token::~Token()
	{
	};

	Token::Token()
	{
		Init();
	};

	Token::Token(const Token& tc)
	{
		Init();
		*this=tc;
	};

	Token& Token::operator=(const Token& tc)
	{
		if(this!=&tc)
		{
			m_attribute = tc.m_attribute;
			m_token = tc.m_token;			
		}
		return *this;
	};

	void Token::SetAttr(int attribute)
	{
		m_attribute = attribute;
	};

	int Token::GetAttr()const
	{
		return m_attribute;
	};

	void Token::SetToken(const String& token)
	{
		m_token = token;
	};

	const Token::String& Token::GetToken()const
	{
		return m_token;
	};

	void Token::Clear()
	{
		m_attribute = 0;
		m_token.clear();
	};

	void Token::Init()
	{
		m_attribute = 0;
		m_token = (unsigned int) 0;
	};


};//namespace


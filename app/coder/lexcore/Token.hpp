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


#ifndef __Token_hpp__
#define __Token_hpp__


#include "autoptr.hpp"
#include "string.hpp"




namespace lex
{
	class Token
	{
	public:
		typedef misc::autoptr<Token> Ptr;
		//typedef std::basic_string<unsigned int> String;
		typedef std::basic_string<char> String;


		~Token();
		Token();
		Token(const Token& tc);
		Token& operator=(const Token& tc);


		void SetAttr(int attribute);
		int GetAttr()const;

		void SetToken(const String& token);
		const String& GetToken()const;

		void Clear();

	private:
		void Init();


	private:
		int				m_attribute;
		String			m_token;
		
	};
}

#endif//__Token_hpp__



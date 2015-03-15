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



#include "Integer.hpp"


namespace lex
{
	Integer::~Integer()
	{
	};

	Integer::Integer(int integer)
		: Base()
	{
		Init();

		m_integer = integer;
	};

	Integer::Integer(const Integer& tc)
		: Base()
	{
		Init();

		*this=tc;
	};

	Integer& Integer::operator=(const Integer& tc)
	{
		if(this!=&tc)
		{
			m_integer = tc.m_integer;
			m_flags = tc.m_flags;
			m_error = tc.m_error;
			m_attribute = tc.m_attribute;
		}
		return *this;
	};



	bool Integer::check( lex::InputFile& in, unsigned int c, Productions& prods, Token& token, lex::Report& rep )
	{
		bool res = (m_integer == (int)c);
		bool brep = false;

		if(res)
		{
			select(prods, token, c);
		}
		else
		{
			brep = rep.report(m_error , in.tellg(), in.row(), in.col());
		}
		
		//temporary
#ifdef D_LEX_PARSE
		misc::string CLSNAME("Integer");
		CLSNAME += " [" ;
		CLSNAME += (char)m_integer;
		CLSNAME += "]";
		LF_DUMP(CLSNAME.c_str(), res, c, in, brep, m_error, token, *prods.begin());
#endif


		return res;
	};

	void Integer::Set(unsigned long flags)
	{
		m_flags = flags;
	};


	unsigned long Integer::Get()const
	{
		return m_flags;
	};

	Base::Ptr Integer::Clone()const
	{
		Integer::Ptr copy = new Integer(NULL);
		*copy = *this;
		
		return copy;
	};

	void Integer::SetError(const lex::Error& er)
	{
		m_error = er;
	};

	void Integer::SetAttr(int attribute)
	{
		m_attribute = attribute;
	};


	void Integer::Init()
	{
		m_integer = 0;
		m_flags = Base::F_NOBIT;
		//m_error;
		m_attribute = 0;
	};



	void Integer::select(Productions& prods, Token& token, unsigned int c)
	{
		if(m_flags & Base::F_BRKSTR)
		{
			Token::String& str = const_cast<Token::String&>(token.GetToken());
			str += c;

			token.SetAttr(m_attribute);
			(*prods.begin()).push_back(token);

			token.Clear();

		}
		else
		{
			Token::String& str = const_cast<Token::String&>(token.GetToken());
			str += c;
			//token += c;

			//ambiguous attribute for this composed rule (e.g. r1 & r2 & r3)
			//it may not be relevant to set attribute here, but at higher level
		}
	};

};//namespace lex
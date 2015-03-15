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



#include "Range.hpp"



namespace lex
{

	Range::~Range()
	{
	};

	Range::Range(int min, int max)
		: Base()
	{
		Init();

		m_min = min;
		m_max = max;
	};

	Range::Range(const Range& tc)
		: Base()
	{
		Init();

		*this=tc;
	};

	Range& Range::operator=(const Range& tc)
	{
		if(this!=&tc)
		{
			m_min = tc.m_min;
			m_max = tc.m_max;
			m_flags = tc.m_flags;
			m_error = tc.m_error;
			m_attribute = tc.m_attribute;
		}
		return *this;
	};


	bool Range::check(lex::InputFile& in, unsigned int c, Productions& prods, Token& token, lex::Report& rep)
	{
		bool brep = false;
		bool res = ((int) c >= m_min && (int) c <= m_max);

		if(res)
		{
			select(prods, token, c);
		}
		else
		{
			brep = rep.report(m_error, in.tellg(), in.row(), in.col());
		}

		misc::string CLSNAME("Range");
		CLSNAME += " [";
		CLSNAME += (char)m_min;
		CLSNAME += ",";
		CLSNAME += (char)m_max;
		CLSNAME += "]";
		
		LF_DUMP(CLSNAME.c_str(), res, c, in, brep, m_error, token, *prods.begin());
		
		return res;
	};


	void Range::Set(unsigned long flags)
	{
		m_flags = flags;
	};


	unsigned long Range::Get()const
	{
		return m_flags;
	};

	Base::Ptr Range::Clone()const
	{
		Range::Ptr copy = new Range(NULL, NULL);
		*copy = *this;

		return copy;
	};


	void Range::SetError(const lex::Error& er)
	{
		m_error = er;
	};

	void Range::SetAttr(int attribute)
	{
		m_attribute = attribute;
	};

	void Range::Init()
	{
		m_min = 0;
		m_max = 0;
		m_flags = Base::F_NOBIT;
		//m_error;
		m_attribute = 0;
	};



	void Range::select(Productions& prods, Token& token, unsigned int c)
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
			//token += c;
			Token::String& str = const_cast<Token::String&>(token.GetToken());
			str += c;

			// [a_zA_Z] & [0 : 9] = ambiguous attribute, cannot set more than 1 attribute (not set in this case)

		}
	};

};//namespace lex



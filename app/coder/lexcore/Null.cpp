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


#include "Null.hpp"





namespace lex
{

	Null::~Null()
	{
	};

	Null::Null()
		: Base()
	{
		Init();
	};

	Null::Null(const Null& tc)
		: Base()
	{
		Init();

		*this=tc;
	};

	Null& Null::operator=(const Null& tc)
	{
		if(this!=&tc)
		{
			m_flags = tc.m_flags;
		}
		return *this;
	};


	bool Null::check(lex::InputFile& in, unsigned int c, Productions& prods, Token& token, lex::Report& /*rep*/)
	{
		
		/*
			rule: 3*(m["long"] & Null()) -> token contains "long"
		*/


		//returns true but should not consume 'c'
		if(in.tellg() > 0)
			in << 1;


		LF_DUMP("Null", true, c, in, false, lex::Error(), token, *prods.begin());

		return true;
	};//rule


	void Null::Set(unsigned long flags)
	{
		m_flags = flags;
	};


	unsigned long Null::Get()const
	{
		return m_flags;
	};


	Base::Ptr Null::Clone()const
	{
		Null::Ptr copy = new Null();
		*copy = *this;

		return copy;
	};


	void Null::SetError(const lex::Error& /*er*/)
	{
		//no Report, no Error; (at the moment)
	};

	void Null::SetAttr(int /*attribute*/)
	{
		//no Token/Production back, no attribute;
	};


	void Null::Init()
	{
		m_flags = Base::F_NOBIT;
	};

};//namespace lex




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


#include "Discard.hpp"





namespace lex
{
	Discard::~Discard()
	{
	};

	Discard::Discard(const Base::Ptr& rule)
		: Base()		
	{
		Init();

		m_rule = rule;
	};

	Discard::Discard(const Discard& tc)
		: Base()
	{
		Init();

		*this=tc;
	};

	Discard& Discard::operator=(const Discard& tc)
	{
		if(this!=&tc)
		{
			m_rule = tc.m_rule;
			m_flags = tc.m_flags;
			m_error = tc.m_error;
			m_attribute = tc.m_attribute;
		}
		return *this;
	};


	bool Discard::check( lex::InputFile& in, unsigned int c, Productions& prods, Token& /*token*/, lex::Report& rep )
	{
		Productions p2_loc;
		p2_loc.push_back(Production());
		Token t_loc;
		bool brep=false;
		FPOS_DECL(in);

		//m_rule is executed but the production/token returned is discarded.
		//however the return value is not changed
		bool res = m_rule->check(in, c, p2_loc, t_loc, rep);

		if( !res )
		{			
			brep = rep.report(m_error, in.tellg(), in.row(), in.col());
			FPOS_CMP(in);
		}


		/*
			rule: 3*(m["long"] & ~m["space"]) -> token contains only "long" and word "space" is discarded.
		*/

		LF_DUMP("Discard", res, c, in, brep, m_error, t_loc, *prods.begin());

		return res;
	};//rule


	void Discard::Set(unsigned long flags)
	{
		m_flags = flags;
	};


	unsigned long Discard::Get()const
	{
		return m_flags;
	};


	Base::Ptr Discard::Clone()const
	{
		Discard::Ptr copy = new Discard(NULL);
		*copy = *this;
		
		return copy;
	};

	void Discard::SetError(const lex::Error& er)
	{
		m_error = er;
	};

	void Discard::SetAttr(int attribute)
	{
		m_attribute = attribute;
	};


	void Discard::Init()
	{
		m_rule = NULL;
		m_flags = Base::F_NOBIT;
		//m_error;
		m_attribute = 0;
	};

};//namespace lex



lex::Base::Ptr operator ~(lex::Base::Ptr rRule)
{
	lex::Base::Ptr rule = rRule->Clone();
	lex::Base::Ptr discard = new lex::Discard(rule);
	//Discard rule allows F_BRKSTR or F_NOBIT flag
	discard->Set(rule->Get());

	return discard;
};

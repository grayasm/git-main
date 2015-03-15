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


#include "False.hpp"





namespace lex
{

	False::~False()
	{
	};


	False::False(const Base::Ptr& rule)
		: Base()
	{
		Init();

		m_rule = rule;
	};


	False::False(const False& tc)
		: Base()
	{
		Init();

		*this=tc;
	};

	False& False::operator =(const False& tc)
	{
		if(this != &tc)
		{
			m_rule = tc.m_rule;
			m_flags = tc.m_flags;
			m_error = tc.m_error;
			m_attribute = tc.m_attribute;
		}
		return *this;
	};


	bool False::check( lex::InputFile& in, unsigned int c, Productions& prods, Token& /*token*/, lex::Report& rep )
	{
		Productions p2_loc;
		p2_loc.push_back(Production());
		Token t_loc;
		Report r_loc;
		bool brep=false;
		lex::InputFile tmp(in);
		FPOS_DECL(in);


		bool res = !m_rule->check(tmp, c, p2_loc, t_loc, r_loc);


		//if m_rule is false tmp is not advanced, this False (e.g. negation) returns true but 'c' param has to be pushed back into the stream;
		//if m_rule is true tmp is advanced, this False (e.g. negation) returns false, but there is no reason to return and advanced stream,
		//at least not at this moment. In both cases 'c' has to be pushed back into the stream;

		//check for some weird cases (eof is allowed for now)
		if(in.tellg() == 0)// || in.eof())
			throw misc::exception("not expected");


		/*
			rule: 3*(m["long"] & False(m["space"])) -> token contains "long"
		*/

		
		in << 1;		

		if( !res )
		{
			brep = rep.report(m_error, tmp.tellg(), tmp.row(), tmp.col());						
		}
		else
		{
			FPOS_CMP(tmp);
		}


		LF_DUMP("False", res, c, in, brep, m_error, t_loc, *prods.begin());

		return res;
	};//rule


	void False::Set(unsigned long flags)
	{
		m_flags = flags;
	};


	unsigned long False::Get()const
	{
		return m_flags;
	};


	Base::Ptr False::Clone()const
	{
		False::Ptr copy = new False(NULL);
		*copy = *this;
		
		return copy;
	};

	void False::SetError(const lex::Error& er)
	{
		m_error = er;
	};

	void False::SetAttr(int attribute)
	{
		m_attribute = attribute;
	};

	void False::Init()
	{
		m_rule = NULL;
		m_flags = Base::F_NOBIT;
		//m_error;
		m_attribute = 0;
	};
};//namespace lex




lex::Base::Ptr operator ! (lex::Base::Ptr rRule)
{
	lex::Base::Ptr rule = rRule->Clone();
	//False cannot accumulate tokens from the stream.
	if(rule->Get() & lex::Base::F_BRKSTR)
		throw misc::exception("not expected");//due to splitting rule
	
	lex::Base::Ptr negation = new lex::False(rule);
	negation->Set(rule->Get());

	return negation;
};

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


#include "True.hpp"





namespace lex
{
	True::~True()
	{
	};

	True::True(const Base::Ptr& rule)
		: Base()
	{
		Init();

		m_rule = rule;
	};

	True::True(const True& tc)
		: Base()
	{
		Init();

		*this=tc;
	};

	True& True::operator=(const True& tc)
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




	bool True::check(lex::InputFile& in, unsigned int c, Productions& prods, Token& /*token*/, lex::Report& rep)
	{
		Productions p2_loc;
		p2_loc.push_back(Production());
		Token t_loc;
		bool brep = false;
		lex::InputFile tmp(in);
		FPOS_DECL(in);

		bool res = m_rule->check(tmp, c, p2_loc, t_loc, rep);


		//if m_rule is true tmp is advanced, this True returns true, BUT there is no reason to return and advanced stream,
		//at least not at this moment. 
		//if m_rule is false tmp is not advanced, True returns false and the token has to be pushed back into the stream;
		//In both cases 'c' has to be pushed back into the stream;


		//check for some weird cases (eof is allowed for now)
		if(in.tellg() == 0)// || in.eof())
			throw misc::exception("not expected");

		
		/*
			rule: 3*(m["long"] & True(m["space"])) -> token contains "long"
		*/


		
		in << 1;		

		if( !res )
		{			
			brep = rep.report(m_error, tmp.tellg(), tmp.row(), tmp.col());
			FPOS_CMP(tmp);
		}

		LF_DUMP("True", res, c, in, brep, m_error, t_loc, *prods.begin());

		return res;
	};//rule


	void True::Set(unsigned long flags)
	{
		m_flags = flags;
	};


	unsigned long True::Get()const
	{
		return m_flags;
	};


	Base::Ptr True::Clone()const
	{
		True::Ptr copy = new True(NULL);
		*copy = *this;

		return copy;
	};


	void True::SetError(const lex::Error& er)
	{
		m_error = er;
	};

	void True::SetAttr(int attribute)
	{
		m_attribute = attribute;
	};


	void True::Init()
	{
		m_rule = NULL;
		m_flags = Base::F_NOBIT;
		//m_error;
		m_attribute = 0;
	};


};//namespace lex



/*
lex::Base::Ptr operator (bool) (lex::Base::Ptr rRule)
{
	lex::Base::Ptr rule = rRule->Clone();
	//True cannot accumulate tokens from the stream.
	if(rule->Get() & lex::Base::F_BRKSTR)
		throw misc::exception("not expected");//due to splitting rule
	
	lex::Base::Ptr negation = new lex::True(rule);
	negation->Set(rule->Get());

	return negation;
};
*/


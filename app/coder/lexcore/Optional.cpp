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



#include "Optional.hpp"




namespace lex
{

	Optional::~Optional()
	{
	};

	Optional::Optional(const Base::Ptr& rule)
		: Base()
	{
		Init();

		m_rule = rule;
	};

	Optional::Optional(const Optional& tc)
		: Base()
	{
		Init();

		*this=tc;
	};

	Optional& Optional::operator=(const Optional& tc)
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


	
	bool Optional::check(lex::InputFile& in, unsigned int c, Productions& prods, Token& token, lex::Report& /*rep*/)
	{
		Productions p2_loc;
		p2_loc.push_back(Production());

		lex::Report l_rep;//optional, always returns true, spits no error
		Token t_loc = token;		
		FPOS_DECL(in);


		bool res = m_rule->check(in, c, p2_loc, t_loc, l_rep);

		if(res)
		{
			select(prods, token, p2_loc, t_loc);			
		}
		else
		{
			//issue no error from Optional
			//rep.report(m_error, in.tellg(), in.row(), in.col());
			FPOS_CMP(in);
		}

	
		//In case m_rule returns false we have to push back c to be validated by next rule;
		if(!res)
			in << 1;		

		LF_DUMP("Optional", true, c, in, false, lex::Error(), t_loc, *prods.begin());

		//optional is not a must!
		return true;
	};//check


	void Optional::Set(unsigned long flags)
	{
		m_flags = flags;
	};


	unsigned long Optional::Get()const
	{
		return m_flags;
	};

	Base::Ptr Optional::Clone()const
	{
		Optional::Ptr copy = new Optional(NULL);
		*copy = *this;
		
		return copy;
	};

	void Optional::SetError(const lex::Error& er)
	{
		m_error = er;
	};

	void Optional::SetAttr(int attribute)
	{
		m_attribute = attribute;
	};



	void Optional::Init()
	{
		m_rule = NULL;
		m_flags = Base::F_NOBIT;
		//m_error;
		m_attribute = 0;
	};
	
	void Optional::select(Productions& prods, Token& token, Productions& p2_loc, Token& t_loc)
	{
		if(m_flags & Base::F_BRKSTR)
		{
			//t_loc initially takes token value;			
			if(!t_loc.GetToken().empty())
			{
				//optional always carry another rule, but it can be an in-place composition with many rules: [r1 & r2 & r3] -> set attribute
				t_loc.SetAttr(m_attribute);
				(*p2_loc.begin()).push_back(t_loc);
			}
			
			token.Clear();

			Production& p0_loc = *p2_loc.begin();
			Production& prod = *prods.begin();
			std::copy(p0_loc.begin(), p0_loc.end(), std::back_inserter(prod));

		}
		else
		{
			// 'a' & [ '1' && '2' && '9' ] = ambiguous
			if(!(*p2_loc.begin()).empty())
				throw misc::exception("not expected");

			// rule1 & [ rule2 ] = ambiguous attribute, cannot set more than 1 attribute (not set in this case)

			token = t_loc;
		}
	};


};//namespace lex




lex::Base::Ptr OP(lex::Base::Ptr rRule)
{
	lex::Base::Ptr rule = rRule->Clone();
	lex::Base::Ptr optional = new lex::Optional(rule);
	optional->Set(rule->Get());
	return optional;
};

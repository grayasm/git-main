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


#include "Group.hpp"


namespace lex
{

	Group::~Group()
	{
	};

	Group::Group(const Base::Ptr& rule)
		: Base()
	{
		Init();

		m_rule = rule;
	};	

	Group::Group(const Group& tc)
		: Base()
	{
		Init();

		*this=tc;
	};

	Group& Group::operator=(const Group& tc)
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


	
	bool Group::check( lex::InputFile& in, unsigned int c, Productions& prods, Token& token, lex::Report& rep )
	{
		Productions p2_loc;
		p2_loc.push_back(Production());
		Token t_loc = token;
		bool brep=false;
		FPOS_DECL(in);


		bool res = m_rule->check(in, c, p2_loc, t_loc, rep);

		/*
		'a' & ('1' && '2') = ambiguous, can be written: ('a' & '1') && ('a' & '2');
		*/
		if(res)
		{
			select(prods, token, p2_loc, t_loc);			
		}
		else
		{
			brep = rep.report(m_error, in.tellg(), in.row(), in.col());			
			FPOS_CMP(in);
		}
		
		
		LF_DUMP("Group", res, c, in, brep, m_error, t_loc, *prods.begin());

		return res;
	};//check



	void Group::Set(unsigned long flags)
	{
		m_flags = flags;
	};


	unsigned long Group::Get()const
	{
		return m_flags;
	};

	Base::Ptr Group::Clone()const
	{
		Group::Ptr copy = new Group(NULL);
		*copy = *this;
		
		return copy;
	};

	void Group::SetError(const lex::Error& er)
	{
		m_error = er;
	};

	void Group::SetAttr(int attribute)
	{
		m_attribute = attribute;
	};

	void Group::Init()
	{
		m_rule = NULL;
		m_flags = Base::F_NOBIT;
		//m_error;
		m_attribute = 0;
	};



	void Group::select(Productions& prods, Token& token, Productions& p2_loc, Token& t_loc)
	{
		if(m_flags & Base::F_BRKSTR)
		{
			//t_loc contains alread token;			
			if(!t_loc.GetToken().empty())
			{
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
			//ambiguous
			if( !(*p2_loc.begin()).empty() )
				throw misc::exception("not expected.");

			token = t_loc;

			//ambiguous attribute for this composed rule: e.g. r1 & (r2 & r3)
			//it may not be relevant to set attribute here, but at higher level

		}
	};



};//namespace lex
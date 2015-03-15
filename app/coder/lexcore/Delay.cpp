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


#include "Delay.hpp"


namespace lex
{	

	Delay::~Delay()
	{
	};


	Delay::Delay(Map& map, const misc::string& rule, size_t maxcall)
		: Base()
		, m_map(map)
	{
		Init();

		m_rule = rule;
		m_maxcall = maxcall;
	};


	Delay::Delay(const Delay& tc)
		: Base()
		, m_map(tc.m_map)
	{
		Init();

		*this=tc;
	};

	Delay& Delay::operator =(const Delay& tc)
	{
		if(this!=&tc)
		{
			m_map = tc.m_map;
			m_rule = tc.m_rule;	
			m_flags = tc.m_flags;
			m_currcall = tc.m_currcall;
			m_maxcall = tc.m_maxcall;
			m_pos = tc.m_pos;
			m_error = tc.m_error;
			m_attribute = tc.m_attribute;
		}
		return *this;
	};




	bool Delay::check( lex::InputFile& in, unsigned int c, Productions& prods, Token& token, lex::Report& rep )
	{
		if(in.eos())
			throw misc::exception("not tested");

		//infinite recursive calls
		if(m_pos == in.tellg()) 
		{
			throw misc::exception("infinite recursive calls");
			//return false;
		}
		else
		{
			m_pos = in.tellg();
		}
		
		
		//test recursive call limit
		if(m_currcall==m_maxcall)
		{	
			LF_MSG("Delay", in.tellg(), in.row(), in.col(), "@@recursive call maxim limit; return false;");
			return false;
		}
		else
		{
			m_currcall++;
		}


		Productions p2_loc;
		p2_loc.push_back(Production());
		Token t_loc = token;
		bool brep=false;
		FPOS_DECL(in);

		
		lex::Base::Ptr& type = m_map[m_rule];
		bool res = type->check(in, c, p2_loc, t_loc, rep);
		
		if(res)
		{
			select(prods, token, p2_loc, t_loc);			
		}
		else
		{			
			brep = rep.report(m_error, in.tellg(), in.row(), in.col());
			FPOS_CMP(in);
		}
		
		
		//recursive call counter
		m_currcall--;


		LF_DUMP("Delay", res, c, in, brep, m_error, t_loc, *prods.begin());

		return res;
	};

	void Delay::Set(unsigned long /*flags*/)
	{
		throw misc::exception("this needs a fix!");
		//m_flags = flags;
	};

	unsigned long Delay::Get()const
	{
		throw misc::exception("this needs a fix!");
		//return m_flags;
	};

	Base::Ptr Delay::Clone()const
	{
		Delay::Ptr copy = new Delay(m_map, "", 0);
		*copy = *this;		

		if(m_pos != 0 || m_currcall != 0)
			throw misc::exception("not expected");

		return copy;
	};

	void Delay::SetError(const lex::Error& er)
	{
		m_error = er;
	};

	void Delay::SetAttr(int attribute)
	{		
		m_attribute = attribute;
	};



	void Delay::Init()
	{
		//m_map;
		m_rule = "";
		m_flags = Base::F_NOBIT;
		m_currcall = 0;
		m_maxcall = 0;
		m_pos = 0 ;
		//m_error;
		m_attribute = 0;
	};


	void Delay::select(Productions& prods, Token& token, Productions& p2_loc, Token& t_loc)
	{
		if(m_flags & Base::F_BRKSTR)
		{			
			//t_loc contains token;
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
			if( !(*p2_loc.begin()).empty() )
				throw misc::exception("not expected.");

			token = t_loc;
		}
	};


};//namespace lex
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



#include "IsEq.hpp"




namespace lex
{

	IsEq::~IsEq()
	{
	};

	IsEq::IsEq(const Base::Ptr& left, const Base::Ptr& right)
		: Base()				
	{
		Init();

		m_left = left;
		m_right = right;
	};

	IsEq::IsEq(const IsEq& tc)
		: Base()
	{
		Init();

		*this=tc;
	};


	IsEq& IsEq::operator=(const IsEq& tc)
	{
		if(this!=&tc)
		{
			m_left = tc.m_left;
			m_right = tc.m_right;
			m_flags = tc.m_flags;
			m_error = tc.m_error;
			m_attribute = tc.m_attribute;
		}
		return *this;
	};




	/*
	class_  - class = true
	_class - class = true
	switch - switch = false
	*/

	bool IsEq::check( lex::InputFile& in, unsigned int c, Productions& prods, Token& token, lex::Report& rep )
	{
		
		Productions p2_left, p2_right, p2_res;
		p2_left.push_back(Production());
		p2_right.push_back(Production());
		p2_res.push_back(Production());


		Token t_left = token, t_right = token, t_res = token;
		bool brep = false;
		FPOS_DECL(in);

		//parse with left prods (must be true)
		lex::InputFile inf1(in);
		bool b1res = m_left->check(inf1, c, p2_left, t_left, rep);
		if( !b1res )
		{			
			brep = rep.report(m_error, inf1.tellg(), inf1.row(), inf1.col());
			FPOS_CMP(inf1);
			LF_DUMP("IsEq", false, c, inf1, brep, m_error, t_left, *prods.begin());
			return false;
		}

	
		//parse with right prods (must be true)
		lex::InputFile inf2(in);
		bool b2res = m_right->check(inf2, c, p2_right, t_right, rep);
		if( !b2res )
		{						
			brep = rep.report(m_error, inf2.tellg(), inf2.row(), inf2.col());
			FPOS_CMP(inf2);
			LF_DUMP("IsEq", false, c, inf2, brep, m_error, t_right, *prods.begin());
			return false;
		}
		else

		

		//both equal
		if(inf1 == inf2)
		{
			in = inf1;
			in.set_eos((size_t) -1);
			select(prods, token, p2_left, t_left);
			LF_DUMP("IsEq", b1res, c, in, brep, m_error, t_left, *prods.begin());
			return b1res;//true
		}


		rep.report(m_error, in.tellg(), in.row(), in.col());

		LF_DUMP("IsEq", false, c, in, brep, m_error, token, *prods.begin());
		return false;

	};


	void IsEq::Set(unsigned long flags)
	{
		m_flags = flags;
	};


	unsigned long IsEq::Get()const
	{
		return m_flags;
	};


	Base::Ptr IsEq::Clone()const
	{
		IsEq::Ptr copy = new IsEq(NULL, NULL);
		*copy = *this;

		return copy;
	};
	

	void IsEq::SetError(const lex::Error& er)
	{
		m_error = er;
	};

	void IsEq::SetAttr(int attribute)
	{		
		m_attribute = attribute;
	};


	void IsEq::Init()
	{
		m_left = NULL;
		m_right = NULL;	
		m_flags = Base::F_NOBIT;
		//m_error;
		m_attribute = 0;
	};


	
	void IsEq::select(Productions& prods, Token& token, Productions& p2_loc, Token& t_loc)
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
			/*
				('a' & 'b' & 'c' & 'd') + ('a' && 'b')
			*/
			if( !(*p2_loc.begin()).empty() )
				throw misc::exception("not expected.");			

			token = t_loc;
		}
	};


};//namespace lex




	
	/*
	class_  - class = true
	_class - class = true
	switch - switch = false
	*/


lex::Base::Ptr operator == (lex::Base::Ptr rLeft, lex::Base::Ptr rRight)
{
	lex::Base::Ptr left = rLeft->Clone();
	lex::Base::Ptr right = rRight->Clone();
		
	unsigned long l_flags = left->Get();
	unsigned long r_flags = right->Get();
	bool l_brk = ((l_flags & lex::Base::F_BRKSTR) == 0 ? false : true);
	bool r_brk = ((r_flags & lex::Base::F_BRKSTR) == 0 ? false : true);
	if( l_brk != r_brk)
	{
		l_flags |= lex::Base::F_BRKSTR;
	}
	

	lex::Base::Ptr except = new lex::IsEq(left, right);
	except->Set(l_flags);
	
	return except;
};



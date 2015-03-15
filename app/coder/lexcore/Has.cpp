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



#include "Has.hpp"



namespace lex
{

	Has::~Has()
	{
	};


	Has::Has(const Base::Ptr& left, const Base::Ptr& right)
		: Base()		
	{
		Init();

		m_left = left;
		m_right = right;
	};

	Has::Has(const Has& tc)
		: Base()
	{
		Init();

		*this=tc;
	};

	Has& Has::operator=(const Has& tc)
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


	
	/* consider the rules:

		m["complex"] + m["auto"] = it should contain

	*/

	bool Has::check( lex::InputFile& in, unsigned int c, Productions& prods, Token& token, lex::Report& rep )
	{
		Productions p2_left, p2_right, p2_res;
		p2_left.push_back(Production());
		p2_right.push_back(Production());
		p2_res.push_back(Production());

		Token t_left = token, t_right = token, t_res = token;
		bool brep = false;
		FPOS_DECL(in);

		unsigned int tc = c;		

		//parse with left prods (must be true)
		lex::InputFile inf1(in);
		bool b1res = m_left->check(inf1, tc, p2_left, t_left, rep);
		if( !b1res ) 
		{
			brep = rep.report(m_error, inf1.tellg(), inf1.row(), inf1.col());
			FPOS_CMP(inf1);			
			LF_DUMP("Has", false, tc, inf1, brep, m_error, t_left, *prods.begin());
			return false;
		}
		

		//only if m_left advances with inf1, inf1+1 position is required to test m_right;	
		if(inf1.tellg() > in.tellg() && !inf1.eos())
		{
			inf1 >> tc;
			tc = c;
		}


		//parse with right prods (must be true)
		lex::InputFile inf2(in);		
		inf2.set_eos(inf1.tellg());
		bool b2res = m_right->check(inf2, tc, p2_right, t_right, rep);


		//m_left contains invalid m_right at the beginning
		if(!b2res) 
		{						
			brep = rep.report(m_error, inf2.tellg(), inf2.row(), inf2.col());
			FPOS_CMP(inf2);
			LF_DUMP("Has", false, tc, inf2, brep, m_error, t_right, *prods.begin());
			return false;
		}



		//right has found valid identifier in left parsed stream,
		//reparse with left the shortest stream to revalidate it;
		//eof must allow last valid character
		if(!inf2.eos())
		{
			inf2 >> tc;
			tc = c;
		}


		lex::InputFile inf3(in);
		inf3.set_eos(inf2.tellg());
		tc = c;
		bool b3res = m_left->check(inf3, tc, p2_res, t_res, rep);

		if(!b3res) 
		{			
			brep = rep.report(m_error, inf3.tellg(), inf3.row(), inf3.col());
			FPOS_CMP(inf3);
			LF_DUMP("Has", false, tc, inf3, brep, m_error, t_res, *prods.begin());
			return false;
		}



		//stream: "auto91v", rule:  m["varname"] + m["auto"], inf3 sets eof on auto[9]1v
		//m_left consumes eof [9] but does not check for it, simply returns true for "varname"
		//[9] must be pushed back into the stream or else next parse will start with [1]
		//if inf3 did not advance then nothing should be pushed back
		if(inf3 != in)
		{
			inf3 << 1;
		}


		in = inf3;
		in.set_eos((size_t)-1);
		select(prods, token, p2_res, t_res);
		LF_DUMP("Has", b3res, tc, in, brep, m_error, t_res, *prods.begin());
		return b3res;
		
	};

	void Has::Set(unsigned long flags)
	{
		m_flags = flags;
	};


	unsigned long Has::Get()const
	{
		return m_flags;
	};

	Base::Ptr Has::Clone()const
	{
		Has::Ptr copy = new Has(NULL, NULL);
		*copy = *this;		

		return copy;
	};

	void Has::SetError(const lex::Error& er)
	{
		m_error = er;
	};
		
	void Has::SetAttr(int attribute)
	{
		m_attribute = attribute;
	};


	void Has::Init()
	{
		m_left = NULL;
		m_right = NULL;
		m_flags = Base::F_NOBIT;
		//m_error;
		m_attribute = 0;
	};



	void Has::select(Productions& prods, Token& token, Productions& p2_loc, Token& t_loc)
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





lex::Base::Ptr operator + (lex::Base::Ptr rLeft, lex::Base::Ptr rRight)
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
	

	lex::Base::Ptr except = new lex::Has(left, right);
	except->Set(l_flags);
	
	return except;
};




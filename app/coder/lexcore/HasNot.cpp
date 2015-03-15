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



#include "HasNot.hpp"




namespace lex
{

	HasNot::~HasNot()
	{
	};

	HasNot::HasNot(const Base::Ptr& left, const Base::Ptr& right)
		: Base()
	{
		Init();

		m_left = left;
		m_right = right;
	};

	HasNot::HasNot(const HasNot& tc)
		: Base()
	{
		Init();

		*this=tc;
	};

	HasNot& HasNot::operator=(const HasNot& tc)
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

		'(*' && 'comment comment' && '*)' = HasNot should identify the largest left valid that has not any right valid part;

	*/

	bool HasNot::check( lex::InputFile& in, unsigned int c, Productions& prods, Token& token, lex::Report& rep )
	{		

		Productions p2_left, p2_right, p2_res;
		p2_left.push_back(Production());
		p2_right.push_back(Production());
		p2_res.push_back(Production());

		Token t_left = token, t_right = token, t_res = token;
		Report r_right = rep;
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
			LF_DUMP("HasNot", false, tc, inf1, brep, m_error, t_left, *prods.begin());
			return false;
		}

		

		//only if m_left advances with inf1, inf1+1 position is required to test m_right;		
		if(inf1.tellg() > in.tellg() && !inf1.eos())
		{
			inf1 >> tc;
			tc = c;
		}
		

		//parse with right prods (must be false)
		lex::InputFile inf2(in);
		lex::InputFile tmp(in);
		tc = c;

		inf2.set_eos(inf1.tellg());
		bool b2res = m_right->check(inf2, tc, p2_right, t_right, r_right);

		//m_left contains m_right valid at the beginning => m_left cannot be resized;
		if(b2res) 
		{						
			brep = rep.report(m_error, inf2.tellg(), inf2.row(), inf2.col());			
			//FPOS_CMP - inf2 has already changed.
			LF_DUMP("HasNot", false, tc, inf2, brep, m_error, t_right, *prods.begin());
			return false;
		}


		
		while(inf2 < inf1 && !b2res)
		{
			//p2_right.clear();//optimized
			//t_right.clear();

			tmp = inf2;
			inf2 >> tc;
			b2res = m_right->check(inf2, tc, p2_right, t_right, r_right);
			//if(b2res) inf2 << 1;//optimized
		}
		

		
		//if right has found valid identifier in left parsed stream,
		//reparse with left the shortest stream to revalidate it;
		if(b2res)
		{			
			//eof must allow last valid character
			if(!tmp.eos())
			{
				tmp >> tc;
				tc = c;
			}

			lex::InputFile inf3(in);
			inf3.set_eos(tmp.tellg());
			tc = c;
			bool b3res = m_left->check(inf3, tc, p2_res, t_res, rep);
			
			if(!b3res)
			{								
				brep = rep.report(m_error, inf3.tellg(), inf3.row(), inf3.col());
				FPOS_CMP(inf3);
				LF_DUMP("HasNot", false, tc, inf3, brep, m_error, t_res, *prods.begin());
				return false;
			}


			//stream: "v01auto", rule:  m["varname"] - m["auto"], inf3 sets eof on v01[a]uto
			//m_left consumes eof [a] but does not check for it, simply returns true for "varname"
			//[a] must be pushed back into the stream or else next parse will start with [u]
			//in other cases (e.g. "a[a]utom3@;") m_left validates only current position without advancing inf3 stream;
			//in this case nothing should be pushed back
			if(inf3 != in && inf3.tellg() == tmp.tellg()) 
			{
				inf3 << 1;
			}
						
			in = inf3;
			in.set_eos((size_t)-1);
			select(prods, token, p2_res, t_res);

			LF_DUMP("HasNot", b3res, tc, in, brep, m_error, t_res, *prods.begin());
			return b3res;
		}


		//right has not found anything in left parsed stream;
		if(!b2res)
		{

			//stream: "int_0x ;"  rule: m["varname"] - m["auto"], inf2 eof is "int_0x[ ];" (the space)
			//m_right parsed entire inf1 including eof although it did not verified any rule with it.
			//[ ] must be pushed back into the stream or else next parse will start with [;]
			if(inf1.tellg() > in.tellg())
				inf1 << 1;

			in = inf1;
			in.set_eos((size_t)-1);	
			select(prods, token, p2_left, t_left);			
		}

		LF_DUMP("HasNot", !b2res, tc, in, brep, m_error, t_left, *prods.begin());

		return !b2res;
	};


	void HasNot::Set(unsigned long flags)
	{
		m_flags = flags;
	};


	unsigned long HasNot::Get()const
	{
		return m_flags;
	};

	Base::Ptr HasNot::Clone()const
	{
		HasNot::Ptr copy = new HasNot(NULL, NULL);
		*copy = *this;

		return copy;
	};
		

	void HasNot::SetError(const lex::Error& er)
	{
		m_error = er;
	};

	void HasNot::SetAttr(int attribute)
	{		
		m_attribute = attribute;
	};


	void HasNot::Init()
	{
		m_left = NULL;
		m_right = NULL;	
		m_flags = Base::F_NOBIT;
		//m_error;
		m_attribute = 0;
	};




	void HasNot::select(Productions& prods, Token& token, Productions& p2_loc, Token& t_loc)
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
				('a' & 'b' & 'c' & 'd') - ('a' && 'b')
			*/
			if( !(*p2_loc.begin()).empty() )
				throw misc::exception("not expected.");

			token = t_loc;
		}
	};


};//namespace lex




/*
	m["complex"] - m["auto"] = rule must return 'complex' validated rule without containing token 'auto'	
*/


lex::Base::Ptr operator - (lex::Base::Ptr rLeft, lex::Base::Ptr rRight)
{
	lex::Base::Ptr left = rLeft->Clone();
	lex::Base::Ptr right = rRight->Clone();


	/*
	('1' & '2' & '3' & 'A' & 'b') - ('2' & 'A')
	*/

	unsigned long l_flags = left->Get();
	unsigned long r_flags = right->Get();

	//left operand may do splitting, but right operand cannot do splitting;
	//right operand may be involved earlier into a composition where it gets F_BRKSTR
	//and it cannot have F_NOBIT here
	//if(r_flags & lex::Base::F_BRKSTR)
	//	throw misc::exception("not supported.");


	//this F_BRKSTR flag
	bool l_brk = ((l_flags & lex::Base::F_BRKSTR) == 0 ? false : true);
	bool r_brk = ((r_flags & lex::Base::F_BRKSTR) == 0 ? false : true);
	if( l_brk != r_brk)
	{
		l_flags |= lex::Base::F_BRKSTR;
	}
	

	lex::Base::Ptr except = new lex::HasNot(left, right);
	except->Set(l_flags);
	
	return except;
};




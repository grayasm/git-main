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




#include "RepeatRange.hpp"




namespace lex
{

	RepeatRange::~RepeatRange()
	{
	};

	RepeatRange::RepeatRange(size_t min, size_t max, const Base::Ptr& rule)
		: Base()
	{		
		if(min >= max)
			throw misc::exception("not allowed");

		Init();

		m_inc = 0;
		m_min = min;
		m_max = max;
		m_rule = rule;
	};

	RepeatRange::RepeatRange(const RepeatRange& tc)
		: Base()
	{
		Init();

		*this=tc;
	};

	RepeatRange& RepeatRange::operator=(const RepeatRange& tc)
	{
		if(this!=&tc)
		{
			m_inc = tc.m_inc;
			m_min = tc.m_min;
			m_max = tc.m_max;
			m_rule = tc.m_rule;
			m_flags = tc.m_flags;
			m_error = tc.m_error;
			m_attribute = tc.m_attribute;
		}
		return *this;
	};



	
	bool RepeatRange::check(lex::InputFile& in, unsigned int c, Productions& prods, Token& token, lex::Report& rep)
	{
		Productions p2_loc;
		p2_loc.push_back(Production());

		lex::Report l_rep;
		bool brep = false;
		Token t_loc = token;
		FPOS_DECL(in);

		m_inc = 0;

		
		//necessary to rewind the stream
		size_t pos = in.tellg();
		size_t row = in.row();
		size_t col = in.col();
		



		// {3,5} * 'a' ;   means  "aaa" or "aaaa" or "aaaaa", between 3 and 5 repetitions inclusive. No less, no more.
		while( !in.eos() )
		{
			if(m_inc < m_max)
			{
				if(m_rule->check(in, c, p2_loc, t_loc, l_rep))
				{					
					if(m_inc+1 == m_max)
					{
						select(prods, token, p2_loc, t_loc);
						LF_DUMP("RepeatRange", true, c, in, false, lex::Error(), t_loc, *prods.begin());
						return true;
					}


					++m_inc;
					in >> c;

					continue;
				}
				else
				{
					if(m_inc >= m_min)
					{
						//in case of error push back last >> c because it returns true now.
						if(m_inc)
							in << 1;

						select(prods, token, p2_loc, t_loc);
						LF_DUMP("RepeatRange", true, c, in, false, lex::Error(), t_loc, *prods.begin());
						return true;
					}

					//update with m_rule parse errors
					repcpy(rep, l_rep);

					//report exact position
					brep = rep.report(m_error, in.tellg(), in.row(), in.col());

					in << m_inc;//test << operator (alternative in.seekg)
										
					FPOS_CMP(in);

					LF_DUMP("RepeatRange", false, c, in, brep, m_error, t_loc, *prods.begin());

					return false;
				}//else
			}

			throw misc::exception("not expected.");
		}//while


		
		if(m_inc >= m_min && m_inc <= m_max)
		{
			//eos needs to be pushed back, for the next rule. 
			//Think of Has, IsEq, etc which works on stream constraint.
			if(m_inc)
				in << 1;

			select(prods, token, p2_loc, t_loc);
			LF_DUMP("RepeatRange", true, c, in, false, lex::Error(), t_loc, *prods.begin());
			return true;
		}


		//update with m_rule parse errors
		repcpy(rep, l_rep);

		//report exact position
		brep = rep.report(m_error, in.tellg(), in.row(), in.col());


		//if during parsing rule hits EOF, and conditions are not met then:
		if(in.eos() && m_inc > 0)
		{		
			in.seekg(pos, row, col);
		}//if


		FPOS_CMP(in);
		LF_DUMP("RepeatRange", false, c, in, brep, m_error, t_loc, *prods.begin());
		return false;
	};//check



	void RepeatRange::Set(unsigned long flags)
	{
		m_flags = flags;
	};


	unsigned long RepeatRange::Get()const
	{
		return m_flags;
	};


	Base::Ptr RepeatRange::Clone()const
	{
		RepeatRange::Ptr copy = new RepeatRange(0, 1, NULL);
		*copy = *this;		

		if(m_inc != 0)
			throw misc::exception("not expected");

		return copy;
	};


	void RepeatRange::SetError(const lex::Error& er)
	{
		m_error = er;
	};

	void RepeatRange::SetAttr(int attribute)
	{
		m_attribute = attribute;
	};


	void RepeatRange::Init()
	{
		m_inc = 0;
		m_min = 0;
		m_max = 0;
		m_rule = NULL;
		m_flags = Base::F_NOBIT;
		//m_error;
		m_attribute = 0;
	};




	/*Note on select function. Considering following rules and parsing results.
	&		to concatenate strings
	&&		to concatenate rules

	{2,4} * 'a' = 'aaaaa'  -> 1 token = 'aaaa' (5th 'a' not parsed)
	{1,3} * ('a' & 'b') = 'ababc'  -> 1 token = 'abab'  (5th letter 'c' not parsed)
	{2,4} * ('a' & ' ' & 'b') = 'a ba ba b'	-> 1 token = 'a ba ba b' 
	'c' & {2,5} * 'a' = 'caaaaaaaaaa' -> 1 token = 'caaaaa' (last 'aaaaa' not parsed)
	c & {1,3} * ('a' & 'b') = 'cababababab' -> 1 token = 'cababab' (last 'abab' not parsed)
	c & {1,2} * ('a' & ' ' & 'b') = 'ca ba ba b' -> 1 token = 'ca ba b'	
	{1,2} * ('a' & 'b') & 'c' = 'ababc' -> 1 token = 'ababc'
	{1,2} * ('a' & ' ' & 'b') & 'c' = 'a ba bc' -> 1 token = 'a ba bc'
	c && {1,2} * ('a' & 'b') = 'cabab' -> 2 tokens = 'c' 'abab'
	{1,2} * ('a' & 'b') && 'c' = 'ababc' -> 2 tokens = 'abab' 'c'
	{1,2} * ('a' & ' ' & 'b') && 'c' = 'a ba bc' -> 2 tokens = 'a ba b' 'c'

	c & {1,2} * ('a' && 'b') = -> umbigous
	{1,2} * ('a' && 'b') & 'c' = -> ambigous

	'c' && {1,2} * 'a' = 'caa' -> 2 tokens = 'c' 'aa'
	{1,2} * ('a' && 'b') = 'abab'	-> 4 tokens = 'a' 'b' 'a' 'b'
	{1,2} * ('a' && ' ' && 'b') = 'a ba b'	-> 6 tokens = 'a' ' ' 'b' 'a' ' ' 'b'
	c && {1,2} * ('a' && 'b') = 'cabab' -> 5 tokens = 'c' 'a' 'b' 'a' 'b'
	c && {1,2} * ('a' && ' ' && 'b') = 'ca ba b' -> 7 tokens = 'c' 'a' ' ' 'b' 'a' ' ' 'b'
	{1,2} * ('a' && 'b') && 'c' = 'ababc' -> 5 tokens = 'a' 'b' 'a' 'b' 'c'
	*/

	void RepeatRange::select(Productions& prods, Token& token, Productions& p2_loc, Token& t_loc)
	{		
		if(m_flags & Base::F_BRKSTR)
		{	
			token.Clear();

			if(!t_loc.GetToken().empty())
			{
				t_loc.SetAttr(m_attribute);
				(*p2_loc.begin()).push_back(t_loc);
			}

			Production& p0_loc = *p2_loc.begin();
			Production& prod = *prods.begin();
			std::copy(p0_loc.begin(), p0_loc.end(), std::back_inserter(prod));

		}
		else
		{
			if(!(*p2_loc.begin()).empty())
			{
				//ambiguous
				throw misc::exception("not expected!");
			}

			//ambiguous attribute for this composed rule (e.g. r1 & {1,3}*r2)
			//it may not be relevant to set attribute here, but at higher level

			token = t_loc;
		}
	};


	void RepeatRange::repcpy(lex::Report& rep, const lex::Report& l_rep)
	{
		for(lex::Report::ErrorList::const_iterator erb = l_rep.GetErrorList().begin(); 
			erb != l_rep.GetErrorList().end(); ++erb)
		{
			const lex::Error& error = *erb;
			rep.report(error, l_rep.GetFilePos(), l_rep.GetRow(), l_rep.GetCol());
		}//for
	};

};//namespace lex



lex::Base::Ptr RR(size_t min, size_t max, lex::Base::Ptr rRight)
{
	lex::Base::Ptr right = rRight->Clone();

	if(min>=max)
		throw misc::exception("not allowed");

	lex::Base::Ptr repeat = new lex::RepeatRange(min, max, right);

	/*
	2 * ('a' && 'b') -> F_BRKSTR
	2 * ('a' & 'b') -> F_NOBIT
	*/
	unsigned long flags = right->Get();
	repeat->Set(flags);

	return repeat;
};


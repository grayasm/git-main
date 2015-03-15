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




#include "Repetition.hpp"




namespace lex
{

	Repetition::~Repetition()
	{
	};

	Repetition::Repetition(size_t repeat, const Base::Ptr& rule)
		: Base()
	{
		Init();

		m_inc = 0;
		m_repeat = repeat;
		m_rule = rule;
	};

	Repetition::Repetition(const Repetition& tc)
		: Base()
	{
		Init();

		*this=tc;
	};

	Repetition& Repetition::operator=(const Repetition& tc)
	{
		if(this!=&tc)
		{
			m_inc = tc.m_inc;
			m_repeat = tc.m_repeat;
			m_rule = tc.m_rule;
			m_flags = tc.m_flags;
			m_error = tc.m_error;
			m_attribute = tc.m_attribute;
		}
		return *this;
	};


	
	bool Repetition::check(lex::InputFile& in, unsigned int c, Productions& prods, Token& token, lex::Report& rep)
	{
		Productions p2_loc;
		p2_loc.push_back(Production());

		Token t_loc = token;
		bool brep = false;
		FPOS_DECL(in);

		m_inc = 0;

		
		//necessary to rewind the stream
		size_t pos = in.tellg();
		size_t row = in.row();
		size_t col = in.col();
		



		// 5 * 'a' ;   means  "aaaaa" no more, no less;
		while( !in.eos() )
		{
			if(m_inc < m_repeat)
			{
				if(m_rule->check(in, c, p2_loc, t_loc, rep))
				{				
					if(m_inc+1 == m_repeat)
					{						
						select(prods, token, p2_loc, t_loc);
						LF_DUMP("Repetition", true, c, in, false, lex::Error(), t_loc, *prods.begin());
						return true;
					}


					++m_inc;
					in >> c;

					continue;
				}
				else
				{
					//report exact stream position
					brep = rep.report(m_error, in.tellg(), in.row(), in.col());
										
					if(m_inc > 0)
						//in << m_inc;
						in.seekg(pos, row, col);
					
					FPOS_CMP(in);
					
					LF_DUMP("Repetition", false, c, in, brep, m_error, t_loc, *prods.begin());

					return false;
				}//else
			}

			throw misc::exception("not expected.");
		}//while


		//report exact stream position
		rep.report(m_error, in.tellg(), in.row(), in.col());

		//if during consuming from stream hits EOF, Repetition behave restrictive and returns false;
		if(in.eos() && m_inc > 0)
		{
			//in << m_inc ;//test for << m_inc operator
			in.seekg(pos, row, col);
		}//if
		
		FPOS_CMP(in);

		return false;

	};//check



	void Repetition::Set(unsigned long flags)
	{
		m_flags = flags;
	};


	unsigned long Repetition::Get()const
	{
		return m_flags;
	};


	Base::Ptr Repetition::Clone()const
	{
		Repetition::Ptr copy = new Repetition(0, NULL);
		*copy = *this;

		if(m_inc != 0)
			throw misc::exception("not expected");

		return copy;
	};


	void Repetition::SetError(const lex::Error& er)
	{
		m_error = er;
	};

	void Repetition::SetAttr(int attribute)
	{
		m_attribute = attribute;
	};


	void Repetition::Init()
	{
		m_inc = 0;
		m_repeat = 0;
		m_rule = NULL;
		m_flags = Base::F_NOBIT;
		//m_error;
		m_attribute = 0;
	};




	/*Note on select function. Considering following rules and parsing results.
	&		to concatenate strings
	&&		to concatenate rules

	2 * 'a' = 'aa'  -> 1 token = 'aa'
	2 * ('a' & 'b') = 'abab'  -> 1 token = 'abab'
	2 * ('a' & ' ' & 'b') = 'a ba b'	-> 1 token = 'a ba b'
	'c' & 2 * 'a' = 'caa' -> 1 token = 'caa'
	c & 2 * ('a' & 'b') = 'cabab' -> 1 token = 'cabab'
	c & 2 * ('a' & ' ' & 'b') = 'ca ba b' -> 1 token = 'ca ba b'	
	2 * ('a' & 'b') & 'c' = 'ababc' -> 1 token = 'ababc'
	2 * ('a' & ' ' & 'b') & 'c' = 'a ba bc' -> 1 token = 'a ba bc'
	c && 2 * ('a' & 'b') = 'cabab' -> 2 tokens = 'c' 'abab'
	2 * ('a' & 'b') && 'c' = 'ababc' -> 2 tokens = 'abab' 'c'
	2 * ('a' & ' ' & 'b') && 'c' = 'a ba bc' -> 2 tokens = 'a ba b' 'c'

	c & 2 * ('a' && 'b') = -> umbigous
	2 * ('a' && 'b') & 'c' = -> ambigous

	'c' && 2 * 'a' = 'caa' -> 2 tokens = 'c' 'aa'
	2 * ('a' && 'b') = 'abab'	-> 4 tokens = 'a' 'b' 'a' 'b'
	2 * ('a' && ' ' && 'b') = 'a ba b'	-> 6 tokens = 'a' ' ' 'b' 'a' ' ' 'b'
	c && 2 * ('a' && 'b') = 'cabab' -> 5 tokens = 'c' 'a' 'b' 'a' 'b'
	c && 2 * ('a' && ' ' && 'b') = 'ca ba b' -> 7 tokens = 'c' 'a' ' ' 'b' 'a' ' ' 'b'
	2 * ('a' && 'b') && 'c' = 'ababc' -> 5 tokens = 'a' 'b' 'a' 'b' 'c'
	*/

	void Repetition::select(Productions& prods, Token& token, Productions& p2_loc, Token& t_loc)
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

			//ambiguous attribute for this composed rule (e.g. r1 & 0*r2 & 2*r3)
			//it may not be relevant to set attribute here, but at higher level

			token = t_loc;
		}
	};


};//namespace lex




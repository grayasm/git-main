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



#include "Repeat.hpp"


namespace lex
{

	Repeat::~Repeat()
	{
	};

	Repeat::Repeat(const Base::Ptr& rule)			
		: Base()			
	{
		Init();

		m_rule = rule;
	};

	Repeat::Repeat(const Repeat& tc)
		: Base()
	{
		Init();

		*this=tc;
	};

	Repeat& Repeat::operator=(const Repeat& tc)
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




	/*
	Note on select function. Considering following rules and parsing results.
	&		to concatenate strings
	&&		to concatenate rules
	0 * () : repeats 0 or more times
	2 * () : repeats 2 times

	'1' & 0 * ('a' & 'b') = '1' -> 1 token: '1'
	'1' & 2 * ('x' & ' ') = '1x x ' -> 1 token: '1x x '
	'1' & 2 * ('x' & ' ' & 'y') & '3' = '1x yx y3' -> 1 token: '1x yx y3'

	'1' & 2 * ('x' && 'y') = ambiguous
	2 * ('x' && 'y') & '3' = ambiguous

	'1' && 2 * ('x' & ' ') = '1x x ' -> 2 tokens: '1' 'x x '
	'1' && 2 * ('x' && ' ') = '1x x ' -> 5 tokens: '1' 'x' ' ' 'x' ' '
	
	*/	

	bool Repeat::check(lex::InputFile& in, unsigned int c, Productions& prods, Token& token, lex::Report& /*rep*/)
	{		
		Productions p2_loc;
		p2_loc.push_back(Production());
		lex::Report l_rep;//always true, never issues an error
		Token t_loc = token;		
		FPOS_DECL(in);

		//stream: 'auto'  , rule: 0*{0*{'\n'}} -> inifinite loop! keep col,row to detect and avoid it.		
		size_t pos = in.tellg();


		//standard:
		//it should not check a rule with eof (both restricted stream or real file EOF)
		//or else will double add last token if rule passes ok (optional rule / too permissive)

		// { 'x' } ;   means 0 or more times 'x'
		bool res = false;
		bool rrw = false;
		while( !in.eos() )
		{				
			res = m_rule->check(in, c, p2_loc, t_loc, l_rep);

			//infinite loop detection: stream 'auto', rule: 0*{0*{'\n'}}
			//0*{'\n'} is false for 'a' , puts 'a' back, and returns true.
			//outer repeat 0*{ ... } takes again 'a' !!! and tries to parse with 0*{'\n'}
			if(res && pos > in.tellg())
			{		
				LF_MSG("Repeat", in.tellg(), in.row(), in.col(), "infinite loop condition; break (a while);");
				break;
			}


			if(res)
			{
				//set before >> c (1 position) which is reverted with in << 1;
				FPOS_SET(in);

				in >> c;
				rrw = true;

				//current stream position
				pos = in.tellg();

				continue;
			}


			/*
						Repeat		   Quote
			m["prods"] = m["gaps"] && m["auto"];
			1. Repeat does not validate [a]uto but returns true therefore needs to put back [a], to be consumed by next prods;
			2. Repeat does not validate the latest 'c' that it took from 'in', therefore it needs to put back 'c' to be consumed by next prods;
			*/
			
#if defined _DEBUG || defined DEBUG
			//if m_rule->check returns false the stream should not advance - to be confirmed.
			if(pos != in.tellg())
			{
				throw misc::exception("not expected - tested.");
			}
#endif

			//0*'a' -> Repeat returns ONLY true; repeat for zero or more times.
			//When m_rule is false, here we are. Default assumption is that only 1 token needs to be pushed back (to be checked).
			//For check see FPOS_SET,CMP macros
			in << 1;
			
			break;
		}//while


		if(rrw)
		{
			select(prods, token, p2_loc, t_loc);

			if(in.eos()) FPOS_INC(1);
			FPOS_CMP(in);			
		}
		else
		{
			//rep = r_loc;
			//rep.report(m_error, in.tellg(), in.row(), in.col());

			if(in.eos()) FPOS_CMP(in);
			else 
			{
				FPOS_DEC(1);
				FPOS_CMP(in);				
			}
		}


		//if during consuming (empty spaces) from stream  hists eof?
		//0 or more times 'x'

		LF_DUMP("Repeat", true, c, in, false, lex::Error(), t_loc, *prods.begin());

		return true;
	};//check



	void Repeat::Set(unsigned long flags)
	{
		m_flags = flags;
	};


	unsigned long Repeat::Get()const
	{
		return m_flags;
	};

	Base::Ptr Repeat::Clone()const
	{
		Repeat::Ptr copy = new Repeat(NULL);
		*copy = *this;
		
		return copy;
	};


	void Repeat::SetError(const lex::Error& er)
	{
		m_error = er;
	};

	void Repeat::SetAttr(int attribute)
	{
		m_attribute = attribute;
	};


	void Repeat::Init()
	{
		m_rule = NULL;
		m_flags = Base::F_NOBIT;
		//m_error;
		m_attribute = 0;
	};


	void Repeat::select(Productions& prods, Token& token, Productions& p2_loc, Token& t_loc)
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
				/*
					ambiguous parsing prods
				*/
				throw misc::exception("not expected!");
			}

			//ambiguous attribute for this composed rule (e.g. r1 & 2*r2 & 3*r3)
			//it may not be relevant to set attribute here, but at higher level

			token = t_loc;
		}
	};


};//namespace lex






lex::Base::Ptr operator * (int inc, lex::Base::Ptr rRight)
{
	lex::Base::Ptr right = rRight->Clone();


	lex::Base::Ptr repeat = 0;

	if(inc == 0)
		repeat = new lex::Repeat(right);
	else if(inc > 0)
		repeat = new lex::Repetition(inc, right);
	else 
		throw misc::exception("positive only");

	/*
	2 * ('a' && 'b') -> F_BRKSTR
	2 * ('a' & 'b') -> F_NOBIT
	*/
	unsigned long flags = right->Get();
	repeat->Set(flags);

	return repeat;
};
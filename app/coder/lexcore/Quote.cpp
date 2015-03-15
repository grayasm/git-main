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



#include "Quote.hpp"


namespace lex
{

	Quote::~Quote()
	{
	};

	Quote::Quote(const Token::String& str)
		: Base()
	{
		Init();

		m_str = str;
		m_step = 0;
	};

	Quote::Quote(const Quote& tc)
		: Base()
	{
		Init();

		*this=tc;
	};

	Quote& Quote::operator=(const Quote& tc)
	{
		if(this!=&tc)
		{
			m_str = tc.m_str;
			m_step = tc.m_step;
			m_flags = tc.m_flags;
			m_error = tc.m_error;
			m_attribute = tc.m_attribute;
		}
		return *this;
	};




	bool Quote::check(lex::InputFile& in, unsigned int c, Productions& prods, Token& token, lex::Report& rep)
	{
		if(m_str.empty())
		{
			//return false;
			throw misc::exception("empty quote not allowed");
		}

		Token t_loc = token ;
		bool brep = false;
		m_step = 0;
		size_t sz=m_str.size();
		FPOS_DECL(in);

		//necessary to rewind the stream
		size_t row = in.row();
		size_t col = in.col();
		size_t pos = in.tellg();


#ifdef D_LEX_PARSE
		Token::String CLSNAME("Quote");
		CLSNAME += " [";
		CLSNAME += m_str;
		CLSNAME += "]";
#else
		Token::String CLSNAME;
#endif
				
		//standard: 
		//it should not check a rule with eof (both restricted stream or real file EOF)
		//or else will double add last token if rule passes ok (optional rule / too permissive)

		while( !in.eos() )
		{
			if(m_step<sz)
			{
				if(c == m_str[m_step])
				{					
					Token::String& t_loc_s = const_cast<Token::String&>(t_loc.GetToken());
					t_loc_s += c;

					if(m_step+1==sz)
					{
						select(prods, token, t_loc);
						LF_DUMP(CLSNAME, true, c, in, false, lex::Error(), t_loc, *prods.begin());
						return true;
					}

					++m_step;
					in >> c;
					continue;
				}
				else
				{
					//report exact position
					brep = rep.report(m_error, in.tellg(), in.row(), in.col());

					if(m_step)
					{
						in << m_step;
						m_step = 0;
					}

					FPOS_CMP(in);
					LF_DUMP(CLSNAME, false, c, in, brep, m_error, t_loc, *prods.begin());
					return false;
				}//else
			}			

			throw misc::exception("not expected.");
		}//while

		//report exact position
		brep = rep.report(m_error, in.tellg(), in.row(), in.col());

		//if during consuming from stream hits EOF, revert all and return;
		if(in.eos() && m_step > 0)
		{
			//in << m_step ;
			//m_step = 0;
			in.seekg(pos, row, col);
		}//if
		
		FPOS_CMP(in);
		LF_DUMP(CLSNAME, false, c, in, brep, m_error, t_loc, *prods.begin());
		return false;
	};


	void Quote::Set(unsigned long flags)
	{
		m_flags = flags;
	};


	unsigned long Quote::Get()const
	{
		return m_flags;
	};

	Base::Ptr Quote::Clone()const
	{
		Quote::Ptr copy = new Quote(0);//""
		*copy = *this;
		
		if(m_step != 0)
			throw misc::exception("not expected");

		return copy;
	};

	void Quote::SetError(const lex::Error& er)
	{
		m_error = er;
	};

	void Quote::SetAttr(int attribute)
	{
		m_attribute = attribute;
	};

	void Quote::Init()
	{
		m_str = (unsigned int)0;//""
		m_step = 0;
		m_flags = Base::F_NOBIT;
		//m_error;
		m_attribute = 0;
	};




	void Quote::select(Productions& prods, Token& token, Token& t_loc)
	{
		if(m_flags & Base::F_BRKSTR)
		{			
			//t_loc contains token;
			if(!t_loc.GetToken().empty())
			{				
				//if carry F_BRKSTR it is a simple quotation (not composed) -> set attribute
				t_loc.SetAttr(m_attribute);
				(*prods.begin()).push_back(t_loc);
			}
			
			token.Clear();
		}
		else
		{
			// [a_zA_Z] & "auto" : ambiguous attribute, cannot set more than 1 attribute (not set in this case)

			//t_loc contains token + quote parsed stream
			token = t_loc;
		}
	};

	
};//namespace lex


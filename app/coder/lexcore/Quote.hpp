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



#ifndef __Quote_hpp__
#define __Quote_hpp__



#include "Base.hpp"


namespace lex
{

	//Quote: "template"
	class Quote : public Base
	{
	public:
		typedef misc::autoptr<Quote> Ptr;


		~Quote();
		Quote(const Token::String& str);
		Quote(const Quote& tc);
		Quote& operator=(const Quote& tc);



		//vtable
		bool check(lex::InputFile& in, unsigned int c, Productions& prods, Token& token, lex::Report& rep);
		void Set(unsigned long);
		unsigned long Get()const;
		Base::Ptr Clone()const;
		void SetError(const lex::Error& er);
		void SetAttr(int attribute);
		//end vtable


		
	private:
		void Init();
		void select(Productions& prods, Token& token, Token& t_loc);



	private:
		Token::String m_str;
		size_t m_step;
		unsigned long m_flags;
		lex::Error m_error;
		int m_attribute;
	};//class


};//namespace lex





#endif//__Quote_hpp__


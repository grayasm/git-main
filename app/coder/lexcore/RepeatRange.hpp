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



#ifndef __RepeatRange_hpp__
#define __RepeatRange_hpp__



#include "Base.hpp"



namespace lex
{

	//RepeatRange: {3,5} * letter;
	class RepeatRange : public Base
	{
	public:
		typedef misc::autoptr<RepeatRange> Ptr;


		~RepeatRange();
		RepeatRange(size_t min, size_t max, const Base::Ptr& rule);
		RepeatRange(const RepeatRange& tc);
		RepeatRange& operator=(const RepeatRange& tc);



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
		void select(Productions& prods, Token& token, Productions& p2_loc, Token& t_loc);
		void repcpy(lex::Report& rep, const lex::Report& l_rep);


	private:
		size_t m_inc;
		size_t m_min;
		size_t m_max;
		Base::Ptr m_rule;
		unsigned long m_flags;
		lex::Error m_error;
		int m_attribute;
	};//class

};//namespace lex


lex::Base::Ptr RR(size_t min, size_t max, lex::Base::Ptr right);





#endif//__RepeatRange_hpp__



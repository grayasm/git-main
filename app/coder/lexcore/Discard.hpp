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


#ifndef __Discard_hpp__
#define __Discard_hpp__


#include "Base.hpp"


namespace lex
{

	//Discard: discards the rule if true ;
	class Discard : public Base
	{
	public:
		typedef misc::autoptr<lex::Discard> Ptr;		


		~Discard();
		Discard(const Base::Ptr& rule);
		Discard(const Discard& tc);
		Discard& operator=(const Discard& tc);
		

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
		//void select(Productions& prods, Token& token, Productions& p2_loc, Token& t_loc, unsigned int c);




	private:
		Base::Ptr m_rule;
		unsigned long m_flags;		
		lex::Error m_error;
		int m_attribute;
	};

};//namespace lex



//Discard operator
lex::Base::Ptr operator ~(lex::Base::Ptr rule);




#endif//__Discard_hpp__



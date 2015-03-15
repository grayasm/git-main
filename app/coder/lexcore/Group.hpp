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


#ifndef __Group_hpp__
#define __Group_hpp__


#include "Base.hpp"

namespace lex
{

	//Group: ( letter )
	class Group : public Base
	{
	public:
		typedef misc::autoptr<Group> Ptr;
		


		~Group();
		Group(const Base::Ptr& rule);
		Group(const Group& tc);
		Group& operator=(const Group& tc);



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



	private:
		Base::Ptr m_rule;
		unsigned long m_flags;
		lex::Error m_error;
		int m_attribute;
	};

};//namespace lex




#endif//__Group_hpp__





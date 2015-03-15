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



#ifndef __Base_hpp__
#define __Base_hpp__


//c/c++
#include <list>
#include <map>

//other
#include "autoptr.hpp"
#include "InputFile.hpp"
#include "tree.hpp"
#include "Report.hpp"
#include "Token.hpp"
#include "Debug.hpp"



namespace lex
{
	
	//Base: 
	class Base
	{
	public:
		typedef misc::autoptr<Base>			Ptr;
		typedef std::list<Token>			Production;
		typedef std::list<Production>		Productions;		
		typedef std::list<Production>		Syntax;
		typedef std::list<Report>			Reports;
		typedef misc::tree<lex::Base::Ptr>	Tree;
		typedef std::map<misc::string, lex::Base::Ptr> Map;		
		

		enum Flags
		{
			F_NOBIT		= 1 << 0 ,		//default, no flag
			F_BRKSTR	= 1 << 1 ,		//break the stream, isolate the token and push it into production.
		};


		Base(){};
		//vtable
		virtual ~Base(){};
		virtual bool check(lex::InputFile& in, unsigned int c, Productions& prod, Token& token, lex::Report& rep)=0;
		virtual void Set(unsigned long)=0;
		virtual unsigned long Get()const=0;		
		virtual Base::Ptr Clone()const=0;
		virtual void SetError(const lex::Error& er)=0;
		virtual void SetAttr(int attribute)=0;		
		//end vtable

	};


};//namespace lex








#endif//__Base_hpp__


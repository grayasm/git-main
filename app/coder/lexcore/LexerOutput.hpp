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



#ifndef __LexerOutput_hpp__
#define __LexerOutput_hpp__


#include "Base.hpp"

//libk1
#include "stream.hpp"


namespace lex
{
	class LexerOutput
	{
	public:
		LexerOutput(const misc::string& fileName);
		~LexerOutput();

		LexerOutput& operator << (const lex::Base::Syntax& grammar);
		LexerOutput& operator << (const lex::Base::Reports& reports);


	private:
		LexerOutput& operator << (const lex::Base::Production& prod);
		LexerOutput& operator << (const lex::Report& rep);

	private:
		misc::string		m_fileName;
		misc::ofstream	m_ostream;
	};//class


};//namespace


#endif//__LexerOutput_hpp__



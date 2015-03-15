/*
  Copyright (C) 2013 Mihai Vasilian

  This program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License as published by the
  Free Software Foundation; either version 2 of the License, or (at your
  option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU General Public License for more details.

  You should have received a copy of the GNU General Public License along
  with this program. If not, see http://www.gnu.org/licenses/.

  contact: grayasm@gmail.com
*/


#ifndef __strtok_hpp__
#define __strtok_hpp__


#include "vector.hpp"
#include "string.hpp"



namespace misc
{
	class strtok
	{
	public:
		typedef misc::autoptr<strtok>		Ptr;
		typedef misc::vector<misc::string>	Tokens;

		strtok(const misc::string& text, const misc::char_t* delim=" ");
		~strtok();

		size_t count() const;
		Tokens::const_iterator begin() const;
		Tokens::const_iterator end() const;
		const Tokens& tokens() const;

	private:
		Tokens	m_tokens;
	};

}; // namespace



#endif // __strtok_hpp__
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


#include "strtok.hpp"




namespace misc
{
	strtok::strtok(const misc::string& text, const misc::char_t* delim)
	{		
		size_t prev_pos = 0;
		size_t curr_pos;
		do
		{
			curr_pos = text.find_first_of(delim, prev_pos);
			if(curr_pos == misc::string::npos)
				curr_pos = text.size();
			size_t count = curr_pos - prev_pos;
			misc::string tok = text.substr(prev_pos, count);
			m_tokens.push_back(tok);
			
			prev_pos = curr_pos + 1;
		}
		while(curr_pos != text.size());
	}

	strtok::~strtok()
	{
	}

	size_t strtok::count() const
	{
		return m_tokens.size();
	}

	strtok::Tokens::const_iterator strtok::begin() const
	{
		return m_tokens.begin();
	}

	strtok::Tokens::const_iterator strtok::end() const
	{
		return m_tokens.end();
	}

	const strtok::Tokens& strtok::tokens() const
	{
		return m_tokens;
	}
}; // namespace


/*
Copyright (C) 2013 Mihai Vasilian
*/


#include "strtok.hpp"




namespace misc
{
	strtok::strtok(const stl::string& text, const stl::char_t* delim)
	{		
		size_t prev_pos = 0;
		size_t curr_pos;
		do
		{
			curr_pos = text.find_first_of(delim, prev_pos);
			if(curr_pos == stl::string::npos)
				curr_pos = text.size();
			size_t count = curr_pos - prev_pos;
			stl::string tok = text.substr(prev_pos, count);
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
} // namespace


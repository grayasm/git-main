/*
Copyright (C) 2013 Mihai Vasilian
*/


#ifndef __strtok_hpp__
#define __strtok_hpp__

#include "autoptr.hpp"
#include "vector.hpp"
#include "string.hpp"



namespace misc
{
	class strtok
	{
	public:
		typedef stl::autoptr<strtok>		Ptr;
		typedef stl::vector<stl::string>	Tokens;

		strtok(const stl::string& text, const stl::char_t* delim=" ");
		~strtok();

		size_t count() const;
		Tokens::const_iterator begin() const;
		Tokens::const_iterator end() const;
		const Tokens& tokens() const;

	private:
		Tokens	m_tokens;
	};

} // namespace



#endif // __strtok_hpp__
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


#ifndef __Error_hpp__
#define __Error_hpp__


//lib
#include "string.hpp"



namespace lex
{
	class Error
	{
	public:		
		~Error();
		Error();
		Error(const misc::string& msg, int level);
		Error(const Error& tc);
		Error& operator=(const Error& tc);

		void SetMsg(const misc::string& msg);		
		const misc::string& GetMsg()const;


		void SetLevel(int level);
		int GetLevel()const;


	private:
		void Init();


	private:
		/*!
			This class member indicates, when its value is > 0, that this error should be reported.
			This is useful in backtracking code, to know which error should/shouldn't be reported.
		*/
		int m_level;
		
		misc::string m_message;
	};
};

#endif//__Error_hpp__

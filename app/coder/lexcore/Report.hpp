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


#ifndef __Report_hpp__
#define __Report_hpp__

#include <stdlib.h>
#include <list>


//local
#include "Error.hpp"


//lib
#include "autoptr.hpp"


namespace lex
{
	class Report
	{	
	public:
		typedef misc::autoptr<Report> Ptr;
		typedef std::list<lex::Error> ErrorList;
		
	public:
		Report();
		~Report();
		Report(const Report& tc);
		Report& operator = (const Report& tc);
		
		bool report(const lex::Error& rule, size_t pos, size_t row, size_t col);
		const ErrorList& GetErrorList()const;
		size_t GetFilePos()const;
		size_t GetRow()const;
		size_t GetCol()const;

	private:
		void Init();


	private:
		ErrorList m_errorList;				
		size_t	m_fpos;
		size_t	m_row;
		size_t	m_col;
	};//class


};//namespace

#endif//__Report_hpp__


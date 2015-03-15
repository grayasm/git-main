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

#ifndef __InputFile_hpp__
#define __InputFile_hpp__


#include <stdio.h>
#include <vector>
#include <assert.h>

#include "autoptr.hpp"
#include "string.hpp"
#include "exception.hpp"




namespace lex
{

	class InputFile
	{
		void Init();
	public:
		typedef misc::autoptr<InputFile> Ptr;

		enum Encode
		{
			ENCODE_ASCII=0,
			ENCODE_UTF8,
			ENCODE_UTF16,
			ENCODE_UCS2
		};



		~InputFile();
		InputFile(const char* filename, size_t tabn, Encode encode=ENCODE_ASCII);
		InputFile(const InputFile& tc);
		InputFile& operator=(const InputFile& tc);
		
		InputFile& operator >> (unsigned int& c);
		InputFile& operator << (size_t bkwd);
		bool operator ==(const InputFile& tc);
		bool operator !=(const InputFile& tc);
		bool operator <(const InputFile& tc);
		bool operator <=(const InputFile& tc);
		bool operator >(const InputFile& tc);
		bool operator >=(const InputFile& tc);


		bool eof()const;
		bool eos()const;

		void set_eos(size_t pos);
		
		size_t row()const;
		size_t col()const;

		void row(size_t row);
		void col(size_t col);

		size_t tellg()const;
		void seekg(size_t pos, size_t row, size_t col);

		//bool good()const;
		//bool bad()const;
		const misc::string& getfn()const;

		Encode get_encode()const;
	

	private:
		void TranslateBuffer();


	private:
		typedef std::vector<unsigned char> ChVec;
		typedef misc::autoptr<ChVec> ChVecPtr;

		ChVecPtr m_buffer;
		misc::string	m_fileName;
		//encoding
		Encode m_encode;
		size_t m_tabn;
		//file position
		size_t m_pos;
		size_t m_row;
		size_t m_col;
		//constrained stream position		
		size_t m_eos_pos;

	};//class

};//namespace



#endif//__InputFile_hpp__


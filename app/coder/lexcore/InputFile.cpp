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


#include "InputFile.hpp"


namespace lex
{

	void InputFile::Init()
	{
		m_buffer = new ChVec();
		m_fileName="";
		m_encode=ENCODE_ASCII;
		m_tabn=0;
		//file position
		m_pos=0;
		m_row=0;
		m_col=0;
		//constrained stream position		
		m_eos_pos=(size_t)(-1);
	};
	
	InputFile::~InputFile()
	{
	};

	InputFile::InputFile(const char* filename, size_t tabn, Encode encode)
	{
		Init();

		FILE* fp = fopen(filename, "rt");
		if(fp==0)return;
		
		if(fseek(fp, 0, SEEK_END) !=0)
		{
			fclose(fp);
			return;//cannot find end of file
		}

		long end = ftell(fp);//bytes
		if(end < 0)
		{
			fclose(fp);
			return;//error
		}

		try
		{
			m_buffer->resize(end);
		}
		catch(...)
		{
			fclose(fp);
			return;//not enough memory
		}

		if(fseek(fp, 0, SEEK_SET) != 0)
		{
			return ;//cannot find beginning of file
		}


		size_t items = fread(&(*m_buffer)[0], sizeof(unsigned char), m_buffer->size(), fp);
		m_buffer->resize(items);
		fclose(fp);

		m_fileName = filename;
		m_tabn = tabn;
		m_encode = encode;

		TranslateBuffer();	
	};

	InputFile::InputFile(const InputFile& tc)
	{
		*this=tc;
	};

	InputFile& InputFile::operator=(const InputFile& tc)
	{
		if(this != &tc)
		{
			m_buffer = tc.m_buffer;
			m_fileName = tc.m_fileName;
			m_encode = tc.m_encode;
			m_tabn = tc.m_tabn;
			//file position
			m_pos = tc.m_pos;
			m_row = tc.m_row;
			m_col = tc.m_col;
			//constrained stream position		
			m_eos_pos = tc.m_eos_pos;			
		}//if
		return *this;
	};

	InputFile& InputFile::operator >> (unsigned int& c)
	{
		/*
                
            0       1       2       3
            |   &   |   *   |  EOF  |
            +-------+-------+-------+
            |   0   |   1   |  EOF  |
            +-------+-------+-------+
                
		*/

		if(m_pos < m_buffer->size())
		{
			c = (unsigned int) (*m_buffer)[m_pos];
			++m_pos;

			switch(c)
			{
			case '\n':
				m_row++;
				m_col=0;
				break;
			case '\t':
				m_col += m_tabn;
				break;
			default:
				m_col++;
				break;
			}		
		}
		else if(m_pos == m_buffer->size())
		{
			m_pos++;//eof
			m_col++;
		}		

		return *this;
	};

	InputFile& InputFile::operator << (size_t bkwd)
	{
		if(m_pos < bkwd)
			throw misc::exception("bad buffer position");

		//walk entire length backwards and count new line symbols-> calculate row value
		size_t row_pos = m_row;
		size_t bkcnt = 1;
		while(bkcnt <= bkwd)
		{
			unsigned int c = 0;//'0'
			
			if((m_pos - bkcnt) < m_buffer->size())
			{
				c = (*m_buffer)[m_pos - bkcnt];
			}

			
			switch(c)
			{
			case '\n':
				m_row--;
				m_col=0;
				break;
			case '\t':
				if(m_col) m_col -= m_tabn;
				break;
			default:
				if(m_col) m_col--;
				break;
			}

			bkcnt++;
		}//while

		if(row_pos == m_row)
		{
			m_pos -= bkwd;
			//same line position
			return *this;
		}

		//if row modified calculate col value from the beginning of line
		assert(m_col==0);
		bool found = false;
		while( m_pos + 1 > bkcnt && !found)
		{
			unsigned int c = (*m_buffer)[m_pos - bkcnt];

			switch(c)
			{
			case '\n':
				found = true;
				break;

			case '\t':
				m_col += m_tabn;
				break;

			default:
				m_col++;
				break;				
			}

			bkcnt++;
		}
		
		m_pos -= bkwd;
		return *this;
	};

	bool InputFile::operator ==(const InputFile& tc)
	{
		return (m_fileName == tc.m_fileName &&	m_pos == tc.m_pos);		
	};

	bool InputFile::operator !=(const InputFile& tc)
	{
		return !(*this==tc);
	};


	bool InputFile::operator <(const InputFile& tc)
	{
		if(m_fileName != tc.m_fileName)
			throw misc::exception("files are different");

		return m_pos < tc.m_pos;
	};

	bool InputFile::operator <=(const InputFile& tc)
	{
		if(m_fileName != tc.m_fileName)
			throw misc::exception("files are different");

		return m_pos <= tc.m_pos;
	};

	bool InputFile::operator >(const InputFile& tc)
	{
		if(m_fileName != tc.m_fileName)
			throw misc::exception("files are different");

		return m_pos > tc.m_pos;
	};

	bool InputFile::operator >=(const InputFile& tc)
	{
		if(m_fileName != tc.m_fileName)
			throw misc::exception("files are different");

		return m_pos >= tc.m_pos;
	};

	bool InputFile::eof()const
	{
		/*
                
            0       1       2       3
            |   &   |   *   |  EOF  |
            +-------+-------+-------+
            |   0   |   1   |  EOF  |
            +-------+-------+-------+
                
		*/
		return m_pos > m_buffer->size();
	};

	bool InputFile::eos()const
	{
		if(m_pos >= m_eos_pos)
			return true;
		else
			return eof();
	};

	void InputFile::set_eos( size_t pos )
	{
		m_eos_pos = pos;		
	};

	size_t InputFile::row()const
	{
		return m_row;
	};

	size_t InputFile::col()const
	{
		return m_col;
	};

	void InputFile::row(size_t row)
	{
		m_row=row;
	};

	void InputFile::col(size_t col)
	{
		m_col=col;
	};

	size_t InputFile::tellg()const
	{
		return m_pos;
	};

	void InputFile::seekg(size_t pos, size_t row, size_t col)
	{
		m_pos = pos;
		m_row = row;
		m_col = col;
	};

	/*
	bool InputFile::good()const
	{
		/*
                
            0       1       2       3
            |   &   |   *   |  EOF  |
            +-------+-------+-------+
            |   0   |   1   |  EOF  |
            +-------+-------+-------+
                
		<<</
		return m_pos <= m_buffer->size();
	};
	*/

	/*
	bool InputFile::bad()const
	{
		return m_pos > m_buffer->size();
	};
	*/


	const misc::string& InputFile::getfn()const
	{
		return m_fileName;
	};


	InputFile::Encode InputFile::get_encode()const
	{
		return m_encode;
	};


	void InputFile::TranslateBuffer()
	{
		//take current buffer
		//decode from current encoding into internal buffer representation

	};
};//namespace
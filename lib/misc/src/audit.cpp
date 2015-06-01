/*
  Copyright (C) 2014 Mihai Vasilian

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



#include "audit.hpp"
#include "exception.hpp"
#include "stream.hpp"


namespace misc
{
	audit::audit()
	{
		reset();
	}

	audit::~audit()
	{
	}

	audit::audit(const misc::string& filepath, std::ios::openmode mode)
	{
		reset();
		m_filepath = filepath;
		misc::ofstream fout(filepath.c_str(), mode);
		if(!fout.is_open())
		{
			misc::cout << "\naudit cannot open file " << filepath.c_str() << std::endl;
			return;
		}
		
		fout.close();
	}

	audit::audit(const audit& tc)
	{
		reset();
		*this = tc;
	}

	audit& audit::operator=(const audit& tc)
	{
		if(this != &tc)
		{
			m_filepath = tc.m_filepath;
		}
		return *this;
	}

	void audit::log(time_t time, const char* file, size_t lineno, const char* fn, const char* msg) const
	{
		if(m_filepath.empty())
			return;
		
		char buff[20];		
		strftime(buff, 20, "%Y-%m-%d %H:%M:%S", localtime(&time));

		misc::ofstream fout(m_filepath.c_str(), std::ios::out | std::ios::app);
		if(!fout.is_open())
			throw misc::exception("Cannot open audit file for writing.");

		fout << "\nTIME: " << buff;
		fout << "\n\tFILE: " << file << ":" << lineno << " " << fn ;//<< " " << GetCurrentThreadId();
		fout << "\n\tMSG : " << msg << ";";
		fout.close();
	}

	void audit::log(const char* file, size_t lineno, const char* fn, const char* msg) const
	{
		if(m_filepath.empty())
			return;

		misc::ofstream fout(m_filepath.c_str(), std::ios::out | std::ios::app);
		if(!fout.is_open())
			throw misc::exception("Cannot open audit file for writing.");

		fout << "\n\tFILE: " << file << ":" << lineno << " " << fn ;//<< " " << GetCurrentThreadId();
		fout << "\n\tMSG : " << msg << ";";
		fout.close();
	}

	void audit::log(const char* msg) const
	{
		if(m_filepath.empty())
			return;

		misc::ofstream fout(m_filepath.c_str(), std::ios::out | std::ios::app);
		if(!fout.is_open())
			throw misc::exception("Cannot open audit file for writing.");

		fout << "\n\tMSG : " << msg << ";";
		fout.close();
	}

	void audit::reset()
	{
		m_filepath.clear();
	}
} // namespace
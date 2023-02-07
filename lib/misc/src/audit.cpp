/*
Copyright (C) 2014 Mihai Vasilian
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

	audit::audit(const stl::string& filepath, std::ios::openmode mode)
	{
		reset();
		m_filepath = filepath;
		stl::ofstream fout(filepath.c_str(), mode);
		if(!fout.is_open())
		{
			stl::cout << "\naudit cannot open file " << filepath.c_str() << std::endl;
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

		stl::ofstream fout(m_filepath.c_str(), std::ios::out | std::ios::app);
		if(!fout.is_open())
			throw stl::exception("Cannot open audit file for writing.");

		fout << "\nTIME: " << buff;
		fout << "\n\tFILE: " << file << ":" << lineno << " " << fn ;//<< " " << GetCurrentThreadId();
		fout << "\n\tMSG : " << msg << ";";
		fout.close();
	}

	void audit::log(const char* file, size_t lineno, const char* fn, const char* msg) const
	{
		if(m_filepath.empty())
			return;

		stl::ofstream fout(m_filepath.c_str(), std::ios::out | std::ios::app);
		if(!fout.is_open())
			throw stl::exception("Cannot open audit file for writing.");

		fout << "\n\tFILE: " << file << ":" << lineno << " " << fn ;//<< " " << GetCurrentThreadId();
		fout << "\n\tMSG : " << msg << ";";
		fout.close();
	}

	void audit::log(const char* msg) const
	{
		if(m_filepath.empty())
			return;

		stl::ofstream fout(m_filepath.c_str(), std::ios::out | std::ios::app);
		if(!fout.is_open())
			throw stl::exception("Cannot open audit file for writing.");

		fout << "\n\tMSG : " << msg << ";";
		fout.close();
	}

	void audit::reset()
	{
		m_filepath.clear();
	}
} // namespace
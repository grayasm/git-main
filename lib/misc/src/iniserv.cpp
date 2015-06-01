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

#include <fstream>
#include "iniserv.hpp"

#include "strconv.hpp"
#include "strtok.hpp"


namespace misc
{

	ini_section::ini_section()
	{
	}

	ini_section::~ini_section()
	{
	}

	ini_section::ini_section(const ini_section& tc)
	{
		*this = tc;
	}

	ini_section& ini_section::operator=(const ini_section& tc)
	{
		if(this != &tc)
		{
			m_values = tc.m_values;
		}
		return *this;
	}

	void ini_section::Set(const misc::string& key, const misc::string& val)
	{
		m_values[key] = val;
	}

	const misc::string& ini_section::Get(const misc::string& key) const
	{
		return m_values[key]; // needs mutable:(
	}

	bool ini_section::Has(const misc::string& key) const
	{
		std::map<misc::string, misc::string>::const_iterator it = m_values.find(key);
		return (it != m_values.end());
	}

	const ini_section::Map& ini_section::Get() const
	{
		return m_values;
	}


	//##########################################################################
	iniserv::iniserv()
	{
	}

	iniserv::iniserv(const misc::string& ini_file)
	{
		m_inifile = ini_file;

		std::fstream fin(ini_file.c_str(), std::ios_base::in);
		if(!fin.is_open())
			return;

		char cline[10001];
		misc::string sline;
		misc::string secname;
		while(!fin.eof())
		{
			fin.getline(cline, 10000);
			sline = cline;
			misc::trim(sline);
			if(sline.empty())
				continue;
			
			if(sline[0]=='[')
			{
				if(!get_section(sline, secname))
					continue;

				Sections::value_type pair(secname, ini_section());
				m_sections.insert(pair);
				continue;
			}
			
			misc::strtok tokenizer(sline, "=");
			if(tokenizer.count() < 2)
				continue;

			// if key's value has another = it must be preserved.
			misc::string key = tokenizer.tokens().front();
			misc::trim(key);

			misc::string val;
			for(size_t i = 1; i < tokenizer.tokens().size(); ++i)
				val += tokenizer.tokens()[i];
			misc::trim(val);

			m_sections[secname].Set(key, val);
		}

		fin.close();
	}

	iniserv::~iniserv()
	{
	}

	iniserv::iniserv(const iniserv& tc)
	{
		*this = tc;
	}

	iniserv& iniserv::operator=(const iniserv& tc)
	{
		if(this != &tc)
		{
			m_inifile = tc.m_inifile;
			m_sections = tc.m_sections;
		}
		return *this;
	}

	bool iniserv::get(
		const misc::string& section,
		const misc::string& parameter,
		bool defval) const
	{
		misc::string svalue = (defval == true ? "1" : "0");
		const misc::string& ret = get(section, parameter, svalue);
		int iret = 0;
		misc::to_value(ret, iret);
		return (iret == 1);
	}

	int iniserv::get(
		const misc::string& section,
		const misc::string& parameter,
		int defval) const
	{
		misc::string svalue = misc::from_value(defval);
		const misc::string& ret = get(section, parameter, svalue);
		misc::to_value(ret, defval);
		return defval;
	}

	double iniserv::get(
		const misc::string& section,
		const misc::string& parameter,
		double defval) const
	{
		misc::string svalue = misc::from_value(defval, 12);
		const misc::string& ret = get(section, parameter, svalue);
		misc::to_value(ret, defval);
		return defval;
	}

	const misc::string& iniserv::get(
		const misc::string& section,
		const misc::string& parameter,
		const misc::string& defval) const
	{
		Sections::const_iterator it = m_sections.find(section);
		if(it != m_sections.end())
		{
			const ini_section& inisec = (*it).second;
			if(inisec.Has(parameter))
			{				
				return inisec.Get(parameter);
			}
			
			m_sections[section].Set(parameter, defval);
			return inisec.Get(parameter);
		}

		m_sections[section] = ini_section();
		m_sections[section].Set(parameter, defval);

		return m_sections[section].Get(parameter);
	}

	void iniserv::set(
		const misc::string& section,
		const misc::string& parameter,
		bool value)
	{
		misc::string svalue = (value == true ? "1" : "0");
		set(section, parameter, svalue);
	}

	void iniserv::set(
		const misc::string& section,
		const misc::string& parameter,
		int value)
	{
		misc::string svalue = misc::from_value(value);
		set(section, parameter, svalue);
	}

	void iniserv::set(
		const misc::string& section,
		const misc::string& parameter,
		double value)
	{
		misc::string svalue = misc::from_value(value, 12);
		set(section, parameter, svalue);
	}

	void iniserv::set(
		const misc::string& section,
		const misc::string& parameter,
		const misc::string& value)
	{
		Sections::iterator it = m_sections.find(section);
		if(it != m_sections.end())
		{
			m_sections[section].Set(parameter, value);
			return;
		}

		m_sections[section] = ini_section();		
		m_sections[section].Set(parameter, value);
	}

	bool iniserv::write()
	{
		if(m_inifile.empty())
			return false;

		iniserv updated(m_inifile);
		// update sections
		for(Sections::iterator it = m_sections.begin(); it != m_sections.end(); ++it)
		{
			SecPair& secpair = *it;
			const misc::string& section = secpair.first;
			ini_section& inisec = secpair.second;
			const ini_section::Map& inimap = inisec.Get();
			for(ini_section::Map::const_iterator vb = inimap.begin(); vb != inimap.end(); ++vb)
			{
				const ini_section::Entry& entry = *vb;
				const ini_section::Key& key = entry.first;
				const ini_section::Val& val = entry.second;

				updated.set(section, key, val);
			}			
		}

		// write sections
		std::fstream out(m_inifile.c_str(), std::ios_base::out | std::ios_base::trunc);
		if(!out.is_open())
			return false;

		for(Sections::iterator it = updated.m_sections.begin(); it != updated.m_sections.end(); ++it)
		{
			SecPair& secpair = *it;
			const misc::string& section = secpair.first;
			out << "\n\n[" << section.c_str() << "]";

			ini_section& inisec = secpair.second;
			const ini_section::Map& inimap = inisec.Get();
			for(ini_section::Map::const_iterator vb = inimap.begin(); vb != inimap.end(); ++vb)
			{
				const ini_section::Entry& entry = *vb;
				const ini_section::Key& key = entry.first;
				const ini_section::Val& val = entry.second;

				out << "\n" << key.c_str() << "=" << val.c_str();
			}			
		}

		out << "\n";

		out.close();
		return true;
	}

	bool iniserv::get_section(const misc::string& line, misc::string& section) const
	{
		misc::string sline=line;
		if(*line.begin() == '[' && *--line.end() == ']')
		{
			misc::trim_left(sline, '[');
			misc::trim_right(sline, ']');
			section = sline;
			return true;
		}

		return false;
	}

} // namespace

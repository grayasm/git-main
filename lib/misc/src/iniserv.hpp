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


#ifndef __iniserv_hpp__
#define __iniserv_hpp__


#include <map>
#include "string.hpp"
#include "autoptr.hpp"


namespace misc
{
	class ini_section;

	//##########################################################################
	/*	Read a file, use accessors to get and set parameters
	 *	and write the content at the end.
	 */
	class iniserv
	{
	public:
		typedef misc::autoptr<iniserv> Ptr;

		iniserv();
		iniserv(const misc::string& inifile);
		~iniserv();
		iniserv(const iniserv& tc);
		iniserv& operator=(const iniserv& tc);
		
		bool get(
			const misc::string& section,
			const misc::string& parameter,
			bool defval) const;

		int get(
			const misc::string& section,
			const misc::string& parameter,
			int defval) const;

		double get(
			const misc::string& section,
			const misc::string& parameter,
			double defval) const;

		const misc::string& get(
			const misc::string& section,
			const misc::string& parameter,
			const misc::string& defval) const;

		void set(
			const misc::string& section,
			const misc::string& parameter,
			bool value);

		void set(
			const misc::string& section,
			const misc::string& parameter,
			int value);

		void set(
			const misc::string& section,
			const misc::string& parameter,
			double value);

		void set(
			const misc::string& section,
			const misc::string& parameter,
			const misc::string& value);

		bool write();

	private:
		bool get_section(const misc::string& line, misc::string& section) const;

		
		typedef std::map<misc::string, ini_section>	Sections;
		typedef Sections::value_type				SecPair;


		misc::string		m_inifile;
		mutable Sections	m_sections;
	};

	//##########################################################################
	/*	Store parameters values for a section.
	 */
	class ini_section
	{
	public:
		typedef misc::string Key;
		typedef misc::string Val;
		typedef std::pair<Key, Val> Entry;
		typedef std::map<Key, Val>	Map;


		ini_section();
		~ini_section();
		ini_section(const ini_section& tc);
		ini_section& operator=(const ini_section& tc);

		void Set(const misc::string& key, const misc::string& val);

		// cannot return non existing key's value
		const misc::string& Get(const misc::string& key) const;

		bool Has(const misc::string& key) const;

		// retrieves the entire map
		const Map& Get() const;

	private:
		mutable Map		m_values;
	};

}; // namespace



#endif // __iniserv_hpp__


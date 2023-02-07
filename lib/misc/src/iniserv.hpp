/*
Copyright (C) 2014 Mihai Vasilian
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
		typedef stl::autoptr<iniserv> Ptr;

		iniserv();
		iniserv(const stl::string& inifile);
		~iniserv();
		iniserv(const iniserv& tc);
		iniserv& operator=(const iniserv& tc);
		
		bool get(
			const stl::string& section,
			const stl::string& parameter,
			bool defval) const;

		int get(
			const stl::string& section,
			const stl::string& parameter,
			int defval) const;

		double get(
			const stl::string& section,
			const stl::string& parameter,
			double defval) const;

		const stl::string& get(
			const stl::string& section,
			const stl::string& parameter,
			const stl::string& defval) const;

		void set(
			const stl::string& section,
			const stl::string& parameter,
			bool value);

		void set(
			const stl::string& section,
			const stl::string& parameter,
			int value);

		void set(
			const stl::string& section,
			const stl::string& parameter,
			double value);

		void set(
			const stl::string& section,
			const stl::string& parameter,
			const stl::string& value);

		bool write();

	private:
		bool get_section(const stl::string& line, stl::string& section) const;

		
		typedef std::map<stl::string, ini_section>	Sections;
		typedef Sections::value_type				SecPair;


		stl::string		m_inifile;
		mutable Sections	m_sections;
	};

	//##########################################################################
	/*	Store parameters values for a section.
	 */
	class ini_section
	{
	public:
		typedef stl::string Key;
		typedef stl::string Val;
		typedef std::pair<Key, Val> Entry;
		typedef std::map<Key, Val>	Map;


		ini_section();
		~ini_section();
		ini_section(const ini_section& tc);
		ini_section& operator=(const ini_section& tc);

		void Set(const stl::string& key, const stl::string& val);

		// cannot return non existing key's value
		const stl::string& Get(const stl::string& key) const;

		bool Has(const stl::string& key) const;

		// retrieves the entire map
		const Map& Get() const;

	private:
		mutable Map		m_values;
	};

} // namespace



#endif // __iniserv_hpp__


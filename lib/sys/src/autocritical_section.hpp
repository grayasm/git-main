/*
Copyright (C) 2014 Mihai Vasilian
*/



#ifndef __autocritical_section_hpp__
#define __autocritical_section_hpp__

#include "autoptr.hpp"
#include "critical_section.hpp"

namespace sys
{
	class autocritical_section
	{
	public:
		typedef stl::autoptr<autocritical_section> Ptr;

	public:
		autocritical_section(critical_section& cs);
		~autocritical_section();

	private:
		//! non copy-able
		autocritical_section(const autocritical_section&);
		autocritical_section& operator=(const autocritical_section&);

	private:
		critical_section& m_critical_section;
	};
} // namespace


#endif // __autocritical_section_hpp__


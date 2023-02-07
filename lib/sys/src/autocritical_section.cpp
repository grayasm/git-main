/*
Copyright (C) 2014 Mihai Vasilian
*/



#include "autocritical_section.hpp"
#include "stream.hpp"

namespace sys
{
	autocritical_section::autocritical_section(critical_section& cs)
		: m_critical_section(cs)
	{
		m_critical_section.lock();
	}

	autocritical_section::~autocritical_section()
	{
		m_critical_section.unlock();
	}
} // namespace
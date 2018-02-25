/*
	Copyright (C) 2018 Mihai Vasilian

	This program is free software; you can redistribute it and/or
	modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation; either version 2
	of the License, or (at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program; if not, write to the Free Software Foundation, Inc.
	51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

	contact: grayasm@gmail.com
*/


#include "Range.hpp"
#include <float.h>

namespace fx
{
	Range::Range()
	{
		// m_min, m_max - default ctor
	}

	Range::Range(const fx::Price& min, const fx::Price& max)
	{
		m_min = min;
		m_max = max;
	}

	Range::Range(const Range& tc)
	{
		*this = tc;
	}

	Range& Range::operator=(const Range& tc)
	{
		if (this != &tc)
		{
			m_min = tc.m_min;
			m_max = tc.m_max;
		}
		return *this;
	}

	const fx::Price& Range::GetMin() const
	{
		return m_min;
	}

	void Range::SetMin(const fx::Price& min)
	{
		m_min = min;
	}

	const fx::Price& Range::GetMax() const
	{
		return m_max;
	}

	void Range::SetMax(const fx::Price& max)
	{
		m_max = max;
	}

	bool Range::IsMinValid() const
	{
		return (m_min.GetBuy() != FLT_MAX && m_min.GetSell() != FLT_MAX);
	}

	bool Range::IsMaxValid() const
	{
		return (m_max.GetBuy() != FLT_MAX && m_max.GetSell() != FLT_MAX);
	}
} // namespace


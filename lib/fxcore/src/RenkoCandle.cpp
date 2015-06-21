/*
  Copyright (C) 2015 Mihai Vasilian

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


#include "RenkoCandle.hpp"

namespace fx
{
	void RenkoCandle::Init()
	{
		m_high = fx::Price();
		m_low = fx::Price();
		m_open = fx::Price();
		m_close = fx::Price();
		m_begin = misc::time();
		m_end = misc::time();
	}

	RenkoCandle::RenkoCandle()
	{
		Init();
	}

	RenkoCandle::RenkoCandle(const fx::Price& high, const fx::Price& low,
		const fx::Price& open, const fx::Price& close,
		const misc::time& begin, const misc::time& end)
	{
		Init();
		m_high = high;
		m_low = low;
		m_open = open;
		m_close = close;
		m_begin = begin;
		m_end = end;
	}

	RenkoCandle::RenkoCandle(const RenkoCandle& tc)
	{
		Init();
		*this = tc;
	}

	RenkoCandle& RenkoCandle::operator=(const RenkoCandle& tc)
	{
		
		if (this != &tc)
		{
			m_high = tc.m_high;
			m_low = tc.m_low;
			m_open = tc.m_open;
			m_close = tc.m_close;
			m_begin = tc.m_begin;
			m_end = tc.m_end;
		}
		return *this;
	}

	RenkoCandle::~RenkoCandle()
	{
	}

	const fx::Price& RenkoCandle::GetHigh() const
	{
		return m_high;
	}

	const fx::Price& RenkoCandle::GetLow() const
	{
		return m_low;
	}

	const fx::Price& RenkoCandle::GetOpen() const
	{
		return m_open;
	}

	const fx::Price& RenkoCandle::GetClose() const
	{
		return m_close;
	}

	const misc::time& RenkoCandle::GetTimeBegin() const
	{
		return m_begin;
	}

	const misc::time& RenkoCandle::GetTimeEnd() const
	{
		return m_end;
	}
	
	void RenkoCandle::AcceptVisitor(CandleVisitor& visitor)
	{
		visitor.Visit(*this);
	}

} // namespace


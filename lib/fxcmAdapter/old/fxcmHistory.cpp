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


#include "fxcmHistory.hpp"


namespace fxcm
{
	void HistoryPrice::Init()
	{
		m_isBar = false;
		m_date = 0;
		// m_currPrice;
		// m_openPrice;
		// m_closePrice;
		// m_highPrice;
		// m_lowPrice;
		m_volume = 0;
	}

	HistoryPrice::HistoryPrice()
	{
		Init();
	}

	HistoryPrice::~HistoryPrice()
	{
	}

	HistoryPrice::HistoryPrice(const HistoryPrice& tc)
	{
		Init();
		*this = tc;
	}

	HistoryPrice& HistoryPrice::operator=(const HistoryPrice& tc)
	{
		if(this != &tc)
		{
			m_isBar = tc.m_isBar;
			m_date = tc.m_date;
			m_currPrice = tc.m_currPrice;
			m_openPrice = tc.m_openPrice;
			m_closePrice = tc.m_closePrice;
			m_highPrice = tc.m_highPrice;
			m_lowPrice = tc.m_lowPrice;
			m_volume = tc.m_volume;
		}
		return *this;
	}

	void HistoryPrice::EnableBar(bool isBar)
	{
		m_isBar = isBar;
	}

	bool HistoryPrice::IsBar() const
	{
		return m_isBar;
	}

	void HistoryPrice::SetDate(const misc::DATE& date)
	{
		m_date = date;
	}

	const misc::DATE& HistoryPrice::GetDate() const
	{
		return m_date;
	}

	void HistoryPrice::SetCurrPrice(const fx::Price& currPrice)
	{
		m_currPrice = currPrice;
	}

	const fx::Price& HistoryPrice::GetCurrPrice() const
	{
		return m_currPrice;
	}

	void HistoryPrice::SetOpenPrice(const fx::Price& openPrice)
	{
		m_openPrice = openPrice;
	}

	const fx::Price& HistoryPrice::GetOpenPrice() const
	{
		return m_openPrice;
	}

	void HistoryPrice::SetClosePrice(const fx::Price& closePrice)
	{
		m_closePrice = closePrice;
	}

	const fx::Price& HistoryPrice::GetClosePrice() const
	{
		return m_closePrice;
	}

	void HistoryPrice::SetHighPrice(const fx::Price& highPrice)
	{
		m_highPrice = highPrice;
	}

	const fx::Price& HistoryPrice::GetHighPrice() const
	{
		return m_highPrice;
	}

	void HistoryPrice::SetLowPrice(const fx::Price& lowPrice)
	{
		m_lowPrice = lowPrice;
	}

	const fx::Price& HistoryPrice::GetLowPrice() const
	{
		return m_lowPrice;
	}

	void HistoryPrice::SetVolume(int volume)
	{
		m_volume = volume;
	}

	int HistoryPrice::GetVolume() const
	{
		return m_volume;
	}
} // namespace
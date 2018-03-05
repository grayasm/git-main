/*
	Copyright (C) 2018 Mihai Vasilian

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

#include "StrategyCrossOver.hpp"


namespace fx
{
	StrategyCrossOver::StrategyCrossOver(
		fx::MarketPlugin* plugin,
		const misc::string& instrument)
	{
		m_plugin = plugin;
		m_instrument = instrument;
		// m_tr - clean;
		m_isCancelled = false;
		m_closedGPL = 0;
	}

	StrategyCrossOver::~StrategyCrossOver()
	{
	}
	
	void StrategyCrossOver::Update(const fx::Offer& offer)
	{
	}

	bool StrategyCrossOver::IsCancelled() const
	{
		return m_isCancelled;
	}

	double StrategyCrossOver::GetClosedGPL() const
	{
		return m_closedGPL;
	}

	void StrategyCrossOver::OpenPosition(const fx::Offer& offer, bool buy)
	{
		misc::vector<fx::Position> result;
		int ret = m_plugin->OpenPosition(offer, 1, buy, result);

		if (ret != 0)
		{
			m_isCancelled = true;
			return;
		}

		for (size_t i = 0; i < result.size(); ++i)
			m_tr.Add(result[i]);
	}

	void StrategyCrossOver::ClosePosition(const fx::Offer& offer)
	{
		misc::vector<fx::Position>& npos =
			const_cast<misc::vector<fx::Position>&>(m_tr.GetPositions());

		misc::vector<fx::Position>::iterator it = npos.begin();
		for (; it != npos.end(); /*erase*/)
		{
			const fx::Position& pos = *it;

			misc::vector<fx::Position> result;
			int ret = m_plugin->ClosePosition(offer, pos, result);

			if (ret != 0)
			{
				m_isCancelled = true;
				return;
			}

			misc::vector<fx::Position>::iterator tmp = npos.erase(it);
			it = tmp;
		}
	}

	void StrategyCrossOver::SetValidMarketTime(misc::time& tend, time_t& interval) const
	{

		/*	Avoid weekend time interval.
			FRI 16:55 EST -> SUN 17:15 EST		 converted to UTC:
			FRI 22:00 UTC -> SUN 22:15 UTC
			And also avoid legal holidays (at least for FXCM).
			25-DEC and 01-JAN
		*/

		while ((tend.wday() == misc::time::SAT) ||
			(tend.wday() == misc::time::FRI && tend.hour_() >= 22) ||
			(tend.wday() == misc::time::SUN && tend.hour_() < 22) ||
			(tend.mon_() == misc::time::Month::DEC && tend.mday_() == 25) ||
			(tend.mon_() == misc::time::Month::JAN && tend.mday_() == 1))
		{
			tend -= misc::time::hourSEC;
		}

		time_t adjustinterv = interval;
		misc::time tbeg = tend - adjustinterv;
		while ((tbeg.wday() == misc::time::SAT) ||
			(tbeg.wday() == misc::time::FRI && tbeg.hour_() >= 22) ||
			(tbeg.wday() == misc::time::SUN && tbeg.hour_() < 22) ||
			(tbeg.mon_() == misc::time::Month::DEC && tbeg.mday_() == 25) ||
			(tbeg.mon_() == misc::time::Month::JAN && tbeg.mday_() == 1))
		{
			adjustinterv += misc::time::hourSEC;
			tbeg = tend - adjustinterv;
		}

		if (adjustinterv != interval) // it was adjusted
		{
			interval += adjustinterv;
		}
	}

} // namespace

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

#include "StrategyRenkoAtr.hpp"


namespace fx
{
	StrategyRenkoAtr::StrategyRenkoAtr(
		fx::MarketPlugin* plugin,
		const misc::string& instrument,
		double renkoMinValue,
		int atrPeriod, time_t atrTimeframe,
		int smaPeriod, time_t smaTimeframe, fx::SMA::PriceOrigin po,
		int openHour, int closeHour)
	{
		m_plugin = plugin;
		m_instrument = instrument;
		m_renkoMinValue = renkoMinValue;
		m_atrPeriod = atrPeriod;
		m_atrTimeframe = atrTimeframe;
		m_smaPeriod = smaPeriod;
		m_smaTimeframe = smaTimeframe;
		m_smaPriceOrigin = po;
		m_openHour = openHour;
		m_closeHour = closeHour;
	}

	StrategyRenkoAtr::~StrategyRenkoAtr()
	{
	}
	
	void StrategyRenkoAtr::Update(const fx::Offer& offer)
	{

	}

	bool StrategyRenkoAtr::IsCanceled() const
	{

	}
} // namespace

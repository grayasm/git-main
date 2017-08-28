/*
Copyright (C) 2017 Mihai Vasilian

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

contact: grayasm@gmail.com
*/


#include "TradingSettings.hpp"


namespace fxcm
{
	void TradingSettings::Init()
	{
		m_instrument = "";
		m_condDistStopForTrade = 0;
		m_condDistLimitForTrade = 0;
		m_condDistEntryStop = 0;
		m_condDistEntryLimit = 0;
		m_minQuantity = 0;
		m_maxQuantity = 0;
		m_baseUnitSize = 0;
		m_marketStatus = MarketStatusClosed;
		m_minTrailingStep = 0;
		m_maxTrailingStep = 0;
		m_mmr = 0;
		m_mmr2 = 0;
		m_emr = 0;
		m_lmr = 0;
	}


	TradingSettings::TradingSettings()
	{
		Init();
	}
	
	TradingSettings::~TradingSettings()
	{
	}
	
	TradingSettings::TradingSettings(const TradingSettings& tc)
	{
		Init();
		*this = tc;
	}
	
	TradingSettings& TradingSettings::operator = (const TradingSettings& tc)
	{
		if (this != &tc)
		{
			m_instrument = tc.m_instrument;
			m_condDistStopForTrade = tc.m_condDistStopForTrade;
			m_condDistLimitForTrade = tc.m_condDistLimitForTrade;
			m_condDistEntryStop = tc.m_condDistEntryStop;
			m_condDistEntryLimit = tc.m_condDistEntryLimit;
			m_minQuantity = tc.m_minQuantity;
			m_maxQuantity = tc.m_maxQuantity;
			m_baseUnitSize = tc.m_baseUnitSize;
			m_marketStatus = tc.m_marketStatus;
			m_minTrailingStep = tc.m_minTrailingStep;
			m_maxTrailingStep = tc.m_maxTrailingStep;
			m_mmr = tc.m_mmr;
			m_mmr2 = tc.m_mmr2;
			m_emr = tc.m_emr;
			m_lmr = tc.m_lmr;
		}
		return *this;
	}

	bool TradingSettings::operator < (const TradingSettings& tc) const
	{
		return m_instrument < tc.m_instrument;
	}

	const misc::string& TradingSettings::GetInstrument() const
	{
		return m_instrument;
	}
	void TradingSettings::SetInstrument(const misc::string& instrument)
	{
		m_instrument = instrument;
	}

	int TradingSettings::GetCondDistStopForTrade() const
	{
		return m_condDistStopForTrade;
	}
	void TradingSettings::SetCondDistStopForTrade(int val)
	{
		m_condDistStopForTrade = val;
	}

	int TradingSettings::GetCondDistLimitForTrade() const
	{
		return m_condDistLimitForTrade;
	}
	void TradingSettings::SetCondDistLimitForTrade(int val)
	{
		m_condDistLimitForTrade = val;
	}

	int TradingSettings::GetCondDistEntryStop() const
	{
		return m_condDistEntryStop;
	}
	void TradingSettings::SetCondDistEntryStop(int val)
	{
		m_condDistEntryStop = val;
	}

	int TradingSettings::GetCondDistEntryLimit() const
	{
		return m_condDistEntryLimit;
	}
	void TradingSettings::SetCondDistEntryLimit(int val)
	{
		m_condDistEntryLimit = val;
	}

	int TradingSettings::GetMinQuantity() const
	{
		return m_minQuantity;
	}
	void TradingSettings::SetMinQuantity(int val)
	{
		m_minQuantity;
	}

	int TradingSettings::GetMaxQuantity() const
	{
		return m_maxQuantity;
	}
	void TradingSettings::SetMaxQuantity(int val)
	{
		m_maxQuantity = val;
	}

	int	TradingSettings::GetBaseUnitSize() const
	{
		return m_baseUnitSize;
	}
	void TradingSettings::SetBaseUnitSize(int val)
	{
		m_baseUnitSize = val;
	}

	O2GMarketStatus TradingSettings::GetMarketStatus() const
	{
		return m_marketStatus;
	}
	void TradingSettings::SetMarketStatus(O2GMarketStatus ms)
	{
		m_marketStatus = ms;
	}

	int TradingSettings::GetMinTrailingStep() const
	{
		return m_minTrailingStep;
	}
	void TradingSettings::SetMinTrailingStep(int val)
	{
		m_minTrailingStep = val;
	}

	int TradingSettings::GetMaxTrailingStep() const
	{
		return m_maxTrailingStep;
	}
	void TradingSettings::SetMaxTrailingStep(int val)
	{
		m_maxTrailingStep = val;
	}

	double TradingSettings::GetMMR() const
	{
		return m_mmr;
	}
	void TradingSettings::SetMMR(double val)
	{
		m_mmr = val;
	}

	double TradingSettings::GetMMR2() const
	{
		return m_mmr2;
	}
	void TradingSettings::SetMMR2(double val)
	{
		m_mmr2 = val;
	}

	double TradingSettings::GetEMR() const
	{
		return m_emr;
	}
	void TradingSettings::SetEMR(double val)
	{
		m_emr = val;
	}

	double TradingSettings::GetLMR() const
	{
		return m_lmr;
	}
	void TradingSettings::SetLMR(double val)
	{
		m_lmr = val;
	}
} // namespace

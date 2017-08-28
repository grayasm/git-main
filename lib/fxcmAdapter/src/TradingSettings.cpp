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
	void TradingSettings::SetIntrument(const misc::string& instrument)
	{
		m_instrument = instrument;
	}

	int TradingSettings::GetCondDistStopForTrade() const;
	void TradingSettings::SetCondDistStopForTrade(int val);

	int TradingSettings::GetCondDistLimitForTrade() const;
	void TradingSettings::SetCondDistLimitForTrade(int val);

	int TradingSettings::GetCondDistEntryStop() const;
	void TradingSettings::SetCondDistEntryStop(int val);

	int TradingSettings::GetCondDistEntryLimit() const;
	void TradingSettings::SetCondDistEntryLimit(int val);

	int TradingSettings::GetMinQuantity() const;
	void TradingSettings::SetMinQuantity(int val);

	int TradingSettings::GetMaxQuantity() const;
	void TradingSettings::SetMaxQuantity(int val);

	int	TradingSettings::GetBaseUnitSize() const;
	void TradingSettings::SetBaseUnitSize(int val);

	O2GMarketStatus TradingSettings::GetMarketStatus() const;
	void TradingSettings::SetMarketStatus(O2GMarketStatus ms);

	int TradingSettings::GetMinTrailingStep() const;
	void TradingSettings::SetMinTrailingStep(int val);

	int TradingSettings::GetMaxTrailingStep() const;
	void TradingSettings::SetMaxTrailingStep(int val);

	double TradingSettings::GetMMR() const;
	void TradingSettings::SetMMR(double val);

	double TradingSettings::GetMMR2() const;
	void TradingSettings::SetMMR2(double val);

	double TradingSettings::GetEMR() const;
	void TradingSettings::SetEMR(double val);

	double TradingSettings::GetLMR() const;
	void TradingSettings::SetLMR(double val);


} // namespace

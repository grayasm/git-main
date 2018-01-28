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


#include "IniParams.hpp"
#include "strconv.hpp"

namespace fxcm
{
	misc::string		g_Section("session");
	misc::string		g_Instrument("instrument");
	misc::string		g_BuySell("buysell");
	misc::string		g_ContingencyID("contingencyid");
	misc::string		g_OrderID("orderid");
	misc::string		g_PrimaryID("primaryid");
	misc::string		g_SecondaryID("secondaryid");
	misc::string		g_Timeframe("timeframe");
	misc::string		g_Account("account");
	misc::string		g_OrderType("ordertype");
	misc::string		g_Status("status");
	misc::string		g_ExpDate("expdate");
	misc::string		g_Lots("lots");
	misc::string		g_TrailStep("trailstep");
	misc::string		g_DateFrom("datefrom");
	misc::string		g_DateTo("dateto");
	misc::string		g_HistoryFile("historyfile");
	misc::string		g_OffersFile("offersfile");
	misc::string		g_RangeInPips("rangeinpips");
	misc::string		g_Rate("rate");
	misc::string		g_RateStop("ratestop");
	misc::string		g_RateLimit("ratelimit");


	IniParams::IniParams()
	{
		Init();
	}

	IniParams::IniParams(const misc::string& inifile)
	{
		Init();

		misc::iniserv iniReader(inifile);
		misc::string emptys("");
		
		m_iniFile = inifile;
		m_section = g_Section;

		m_instrument = iniReader.get(m_section, g_Instrument, emptys);
		m_buysell = iniReader.get(m_section, g_BuySell, emptys);
		m_contingencyID = iniReader.get(m_section, g_ContingencyID, emptys);
		m_orderID = iniReader.get(m_section, g_OrderID, emptys);
		m_primaryID = iniReader.get(m_section, g_PrimaryID, emptys);
		m_secondaryID = iniReader.get(m_section, g_SecondaryID, emptys);
		m_timeframe = iniReader.get(m_section, g_Timeframe, emptys);
		m_account = iniReader.get(m_section, g_Account, emptys);
		m_orderType = iniReader.get(m_section, g_OrderType, emptys);
		m_status = iniReader.get(m_section, g_Status, emptys);
		m_expDate = iniReader.get(m_section, g_ExpDate, emptys);
		m_lots = iniReader.get(m_section, g_Lots, int(0));
		m_trailStep = iniReader.get(m_section, g_TrailStep, int(0));
		m_dateFrom = iniReader.get(m_section, g_DateFrom, emptys);
		m_dateTo = iniReader.get(m_section, g_DateTo, emptys);
		
		m_historyfile = iniReader.get(m_section, g_HistoryFile, emptys);
		misc::trim(m_historyfile, '"'); // remove double quote at both ends
		misc::trim(m_historyfile, ' '); // remove empty spaces at both ends

		m_offersfile = iniReader.get(m_section, g_OffersFile, emptys);
		misc::trim(m_offersfile, '"'); // remove double quote at both ends
		misc::trim(m_offersfile, ' '); // remove empty spaces at both ends

		
		m_rangeInPips = iniReader.get(m_section, g_RangeInPips, double(0));
		m_rate = iniReader.get(m_section, g_Rate, double(0));
		m_rateStop = iniReader.get(m_section, g_RateStop, double(0));
		m_rateLimit = iniReader.get(m_section, g_RateLimit, double(0));
	}

	IniParams::~IniParams()
	{

	}

	IniParams::IniParams(const IniParams& tc)
	{
		Init();

		*this = tc;
	}

	IniParams& IniParams::operator=(const IniParams& tc)
	{
		if (this != &tc)
		{
			m_iniFile = tc.m_iniFile;
			m_section = tc.m_section;
			m_instrument = tc.m_instrument;
			m_buysell = tc.m_buysell;
			m_contingencyID = tc.m_contingencyID;
			m_orderID = tc.m_orderID;
			m_primaryID = tc.m_primaryID;
			m_secondaryID = tc.m_secondaryID;
			m_timeframe = tc.m_timeframe;
			m_account = tc.m_account;
			m_orderType = tc.m_orderType;
			m_status = tc.m_status;
			m_expDate = tc.m_expDate;
			m_lots = tc.m_lots;
			m_trailStep = tc.m_trailStep;
			m_dateFrom = tc.m_dateFrom;
			m_dateTo = tc.m_dateTo;
			m_historyfile = tc.m_historyfile;
			m_offersfile = tc.m_offersfile;
			m_rangeInPips = tc.m_rangeInPips;
			m_rate = tc.m_rate;
			m_rateStop = tc.m_rateStop;
			m_rateLimit = tc.m_rateLimit;
		}
		return *this;
	}

	const misc::string& IniParams::GetInstrument() const
	{
		return m_instrument;
	}

	void IniParams::SetInstrument(const misc::string& val)
	{
		m_instrument = val;
	}

	const misc::string& IniParams::GetBuySell() const
	{
		return m_buysell;
	}

	void IniParams::SetBuySell(const misc::string& val)
	{
		m_buysell = val;
	}

	const misc::string& IniParams::GetContingencyID() const
	{
		return m_contingencyID;
	}

	void IniParams::SetContingencyID(const misc::string& val)
	{
		m_contingencyID = val;
	}

	const misc::string& IniParams::GetOrderID() const
	{
		return m_orderID;
	}

	void IniParams::SetOrderID(const misc::string& val)
	{
		m_orderID = val;
	}

	const misc::string& IniParams::GetPrimaryID() const
	{
		return m_primaryID;
	}

	void IniParams::SetPrimaryID(const misc::string& val)
	{
		m_primaryID = val;
	}

	const misc::string& IniParams::GetSecondaryID() const
	{
		return m_secondaryID;
	}

	void IniParams::SetSecondaryID(const misc::string& val)
	{
		m_secondaryID = val;
	}

	const misc::string& IniParams::GetTimeframe() const
	{
		return m_timeframe;
	}

	void IniParams::SetTimeframe(const misc::string& val)
	{
		m_timeframe = val;
	}

	const misc::string& IniParams::GetAccount() const
	{
		return m_account;
	}

	void IniParams::SetAccount(const misc::string& val)
	{
		m_account = val;
	}

	const misc::string& IniParams::GetOrderType() const
	{
		return m_orderType;
	}

	void IniParams::SetOrderType(const misc::string& val)
	{
		m_orderType = val;
	}

	const misc::string& IniParams::GetStatus() const
	{
		return m_status;
	}

	void IniParams::SetStatus(const misc::string& val)
	{
		m_status = val;
	}

	const misc::string& IniParams::GetExpDate() const
	{
		return m_expDate;
	}

	void IniParams::SetExpDate(const misc::string& val)
	{
		m_expDate = val;
	}

	int IniParams::GetLots() const
	{
		return m_lots;
	}

	void IniParams::SetLots(int val)
	{
		m_lots = val;
	}

	int IniParams::GetTrailStep() const
	{
		return m_trailStep;
	}

	void IniParams::SetTrailStep(int val)
	{
		m_trailStep = val;
	}

	const misc::string& IniParams::GetDateFrom() const
	{
		return m_dateFrom;
	}

	void IniParams::SetDateFrom(const misc::string& val)
	{
		m_dateFrom = val;
	}

	const misc::string& IniParams::GetDateTo() const
	{
		return m_dateTo;
	}

	void IniParams::SetDateTo(const misc::string& val)
	{
		m_dateTo = val;
	}

	const misc::string& IniParams::GetHistoryFile() const
	{
		return m_historyfile;
	}

	void IniParams::SetHistoryFile(const misc::string& val)
	{
		m_historyfile = val;
	}
	
	const misc::string& IniParams::GetOffersFile() const
	{
		return m_offersfile;
	}

	void IniParams::SetOffersFile(const misc::string& val)
	{
		m_offersfile = val;
	}

	double IniParams::GetRangeInPips() const
	{
		return m_rangeInPips;
	}

	void IniParams::SetRangeInPips(double val)
	{
		m_rangeInPips = val;
	}

	double IniParams::GetRate() const
	{
		return m_rate;
	}

	void IniParams::SetRate(double val)
	{
		m_rate = val;
	}

	double IniParams::GetRateStop() const
	{
		return m_rateStop;
	}

	void IniParams::SetRateStop(double val)
	{
		m_rateStop = val;
	}

	double IniParams::GetRateLimit() const
	{
		return m_rateLimit;
	}

	void IniParams::SetRateLimit(double val)
	{
		m_rateLimit = val;
	}

	void IniParams::Init()
	{
		m_iniFile = "";
		m_section = "";
		m_instrument = "";
		m_buysell = "";
		m_contingencyID = "";
		m_orderID = "";
		m_primaryID = "";
		m_secondaryID = "";
		m_timeframe = "";
		m_account = "";
		m_orderType = "";
		m_status = "";
		m_expDate = "";
		m_lots = 0;
		m_trailStep = 0;
		m_dateFrom = "";
		m_dateTo = "";
		m_historyfile = "";
		m_offersfile = "";
		m_rangeInPips = 0;
		m_rate = 0;
		m_rateStop = 0;
		m_rateLimit = 0;
	}
} // namespace

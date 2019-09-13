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
	stl::string		g_Section("session");
	stl::string		g_Instrument("instrument");
	stl::string		g_BuySell("buysell");
	stl::string		g_ContingencyID("contingencyid");
	stl::string		g_OrderID("orderid");
	stl::string		g_PrimaryID("primaryid");
	stl::string		g_SecondaryID("secondaryid");
	stl::string		g_Timeframe("timeframe");
	stl::string		g_Account("account");
	stl::string		g_AccountSymbol("accountSymbol");
	stl::string		g_OrderType("ordertype");
	stl::string		g_Status("status");
	stl::string		g_ExpDate("expdate");
	stl::string		g_Lots("lots");
	stl::string		g_TrailStep("trailstep");
	stl::string		g_DateFrom("datefrom");
	stl::string		g_DateTo("dateto");
	stl::string		g_HistoryFile("historyfile");
	stl::string		g_OffersFile("offersfile");
	stl::string		g_EnableOfferUpdater("enableOfferUpdater");
	stl::string		g_EnableOfferWriter("enableOfferWriter");
	stl::string		g_LoggingFile("loggingfile");
	stl::string		g_EnableLogging("enableLogging");
	stl::string		g_RangeInPips("rangeinpips");
	stl::string		g_Rate("rate");
	stl::string		g_RateStop("ratestop");
	stl::string		g_RateLimit("ratelimit");


	IniParams::IniParams()
	{
		Init();
	}

	IniParams::IniParams(const stl::string& inifile)
	{
		Init();

		misc::iniserv iniReader(inifile);
		stl::string emptys("");
		
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
		m_accountSymbol = iniReader.get(m_section, g_AccountSymbol, emptys);
		m_orderType = iniReader.get(m_section, g_OrderType, emptys);
		m_status = iniReader.get(m_section, g_Status, emptys);
		m_expDate = iniReader.get(m_section, g_ExpDate, emptys);
		m_lots = iniReader.get(m_section, g_Lots, int(0));
		m_trailStep = iniReader.get(m_section, g_TrailStep, int(0));
		m_dateFrom = iniReader.get(m_section, g_DateFrom, emptys);
		m_dateTo = iniReader.get(m_section, g_DateTo, emptys);
		
		m_historyfile = iniReader.get(m_section, g_HistoryFile, emptys);
		stl::trim(m_historyfile, '"'); // remove double quote at both ends
		stl::trim(m_historyfile, ' '); // remove empty spaces at both ends

		m_offersfile = iniReader.get(m_section, g_OffersFile, emptys);
		stl::trim(m_offersfile, '"'); // remove double quote at both ends
		stl::trim(m_offersfile, ' '); // remove empty spaces at both ends

		m_enableOfferUpdater = iniReader.get(m_section, g_EnableOfferUpdater, bool(true));
		m_enableOfferWriter = iniReader.get(m_section, g_EnableOfferWriter, bool(true));

		m_loggingfile = iniReader.get(m_section, g_LoggingFile, emptys);
		stl::trim(m_loggingfile, '"'); // remove double quote at both ends
		stl::trim(m_loggingfile, ' '); // remove empty spaces at both ends

		m_enableLogging = iniReader.get(m_section, g_EnableLogging, bool(false));
		
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
			m_accountSymbol = tc.m_accountSymbol;
			m_orderType = tc.m_orderType;
			m_status = tc.m_status;
			m_expDate = tc.m_expDate;
			m_lots = tc.m_lots;
			m_trailStep = tc.m_trailStep;
			m_dateFrom = tc.m_dateFrom;
			m_dateTo = tc.m_dateTo;
			m_historyfile = tc.m_historyfile;
			m_offersfile = tc.m_offersfile;
			m_enableOfferUpdater = tc.m_enableOfferUpdater;
			m_enableOfferWriter = tc.m_enableOfferWriter;
			m_loggingfile = tc.m_loggingfile;
			m_enableLogging = tc.m_enableLogging;
			m_rangeInPips = tc.m_rangeInPips;
			m_rate = tc.m_rate;
			m_rateStop = tc.m_rateStop;
			m_rateLimit = tc.m_rateLimit;
		}
		return *this;
	}

	const stl::string& IniParams::GetInstrument() const
	{
		return m_instrument;
	}

	void IniParams::SetInstrument(const stl::string& val)
	{
		m_instrument = val;
	}

	const stl::string& IniParams::GetBuySell() const
	{
		return m_buysell;
	}

	void IniParams::SetBuySell(const stl::string& val)
	{
		m_buysell = val;
	}

	const stl::string& IniParams::GetContingencyID() const
	{
		return m_contingencyID;
	}

	void IniParams::SetContingencyID(const stl::string& val)
	{
		m_contingencyID = val;
	}

	const stl::string& IniParams::GetOrderID() const
	{
		return m_orderID;
	}

	void IniParams::SetOrderID(const stl::string& val)
	{
		m_orderID = val;
	}

	const stl::string& IniParams::GetPrimaryID() const
	{
		return m_primaryID;
	}

	void IniParams::SetPrimaryID(const stl::string& val)
	{
		m_primaryID = val;
	}

	const stl::string& IniParams::GetSecondaryID() const
	{
		return m_secondaryID;
	}

	void IniParams::SetSecondaryID(const stl::string& val)
	{
		m_secondaryID = val;
	}

	const stl::string& IniParams::GetTimeframe() const
	{
		return m_timeframe;
	}

	void IniParams::SetTimeframe(const stl::string& val)
	{
		m_timeframe = val;
	}

	const stl::string& IniParams::GetAccount() const
	{
		return m_account;
	}

	void IniParams::SetAccount(const stl::string& val)
	{
		m_account = val;
	}

	const stl::string& IniParams::GetAccountSymbol() const
	{
		return m_accountSymbol;
	}

	void IniParams::SetAccountSymbol(const stl::string& val)
	{
		m_accountSymbol = val;
	}

	const stl::string& IniParams::GetOrderType() const
	{
		return m_orderType;
	}

	void IniParams::SetOrderType(const stl::string& val)
	{
		m_orderType = val;
	}

	const stl::string& IniParams::GetStatus() const
	{
		return m_status;
	}

	void IniParams::SetStatus(const stl::string& val)
	{
		m_status = val;
	}

	const stl::string& IniParams::GetExpDate() const
	{
		return m_expDate;
	}

	void IniParams::SetExpDate(const stl::string& val)
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

	const stl::string& IniParams::GetDateFrom() const
	{
		return m_dateFrom;
	}

	void IniParams::SetDateFrom(const stl::string& val)
	{
		m_dateFrom = val;
	}

	const stl::string& IniParams::GetDateTo() const
	{
		return m_dateTo;
	}

	void IniParams::SetDateTo(const stl::string& val)
	{
		m_dateTo = val;
	}

	const stl::string& IniParams::GetHistoryFile() const
	{
		return m_historyfile;
	}

	void IniParams::SetHistoryFile(const stl::string& val)
	{
		m_historyfile = val;
	}
	
	const stl::string& IniParams::GetOffersFile() const
	{
		return m_offersfile;
	}

	void IniParams::SetOffersFile(const stl::string& val)
	{
		m_offersfile = val;
	}

	bool IniParams::GetEnableOfferUpdater() const
	{
		return m_enableOfferUpdater;
	}

	void IniParams::SetEnableOfferUpdater(bool enable)
	{
		m_enableOfferUpdater = enable;
	}

	bool IniParams::GetEnableOfferWriter() const
	{
		return m_enableOfferWriter;
	}

	void IniParams::SetEnableOfferWriter(bool enable)
	{
		m_enableOfferWriter = enable;
	}

	const stl::string& IniParams::GetLoggingFile() const
	{
		return m_loggingfile;
	}

	void IniParams::SetLoggingFile(const stl::string& val)
	{
		m_loggingfile = val;
	}

	bool IniParams::GetEnableLogging() const
	{
		return m_enableLogging;
	}

	void IniParams::SetEnableLogging(bool enable)
	{
		m_enableLogging = enable;
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
		m_accountSymbol = "";
		m_orderType = "";
		m_status = "";
		m_expDate = "";
		m_lots = 0;
		m_trailStep = 0;
		m_dateFrom = "";
		m_dateTo = "";
		m_historyfile = "";
		m_offersfile = "";
		m_enableOfferUpdater = true;
		m_enableOfferWriter = true;
		m_loggingfile = "";
		m_enableLogging = false;
		m_rangeInPips = 0;
		m_rate = 0;
		m_rateStop = 0;
		m_rateLimit = 0;
	}
} // namespace

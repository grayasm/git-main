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


#ifndef __IniParams_hpp__
#define __IniParams_hpp__

#include "autoptr.hpp"
#include "string.hpp"
#include "iniserv.hpp"

typedef double DATE;




namespace fxcm
{
	class IniParams
	{
	public:
		typedef misc::autoptr<IniParams> Ptr;

		IniParams();
		IniParams(const misc::string& inifile);
		~IniParams();
		IniParams(const IniParams& tc);
		IniParams& operator=(const IniParams& tc);

		const misc::string& GetInstrument() const;
		void SetInstrument(const misc::string& val);

		const misc::string& GetBuySell() const;
		void SetBuySell(const misc::string& val);

		const misc::string& GetContingencyID() const;
		void SetContingencyID(const misc::string& val);

		const misc::string& GetOrderID() const;
		void SetOrderID(const misc::string& val);

		const misc::string& GetPrimaryID() const;
		void SetPrimaryID(const misc::string& val);

		const misc::string& GetSecondaryID() const;
		void SetSecondaryID(const misc::string& val);

		const misc::string& GetTimeframe() const;
		void SetTimeframe(const misc::string& val);

		const misc::string& GetAccount() const;
		void SetAccount(const misc::string& val);

		const misc::string& GetOrderType() const;
		void SetOrderType(const misc::string& val);

		const misc::string& GetStatus() const;
		void SetStatus(const misc::string& val);

		const misc::string& GetExpDate() const;
		void SetExpDate(const misc::string& val);

		int GetLots() const;
		void SetLots(int val);

		int GetTrailStep() const;
		void SetTrailStep(int val);

		// "m.d.Y H:M:S"
		const misc::string& GetDateFrom() const;
		void SetDateFrom(const misc::string& val);

		const misc::string& GetDateTo() const;
		void SetDateTo(const misc::string& val);

		const misc::string& GetHistoryFile() const;
		void SetHistoryFile(const misc::string& val);

		const misc::string& GetOffersFile() const;
		void SetOffersFile(const misc::string& val);

		double GetRangeInPips() const;
		void SetRangeInPips(double val);

		double GetRate() const;
		void SetRate(double val);

		double GetRateStop() const;
		void SetRateStop(double val);

		double GetRateLimit() const;
		void SetRateLimit(double val);

	private:
		void Init();

	private:
		misc::string		m_iniFile;
		misc::string		m_section;
		misc::string		m_instrument;
		misc::string		m_buysell;
		misc::string		m_contingencyID;
		misc::string		m_orderID;
		misc::string		m_primaryID;
		misc::string		m_secondaryID;
		misc::string		m_timeframe;
		misc::string		m_account;
		misc::string		m_orderType;
		misc::string		m_status;
		misc::string		m_expDate;
		int					m_lots;
		int					m_trailStep;
		misc::string		m_dateFrom;
		misc::string		m_dateTo;
		misc::string		m_historyfile;
		misc::string		m_offersfile;
		double				m_rangeInPips;
		double				m_rate;
		double				m_rateStop;
		double				m_rateLimit;
	};
} // namespace


#endif // __IniParams_hpp__

/*
Copyright (C) 2017 Mihai Vasilian
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
		typedef stl::autoptr<IniParams> Ptr;

		IniParams();
		IniParams(const stl::string& inifile);
		~IniParams();
		IniParams(const IniParams& tc);
		IniParams& operator=(const IniParams& tc);

		const stl::string& GetInstrument() const;
		void SetInstrument(const stl::string& val);

		const stl::string& GetBuySell() const;
		void SetBuySell(const stl::string& val);

		const stl::string& GetContingencyID() const;
		void SetContingencyID(const stl::string& val);

		const stl::string& GetOrderID() const;
		void SetOrderID(const stl::string& val);

		const stl::string& GetPrimaryID() const;
		void SetPrimaryID(const stl::string& val);

		const stl::string& GetSecondaryID() const;
		void SetSecondaryID(const stl::string& val);

		const stl::string& GetTimeframe() const;
		void SetTimeframe(const stl::string& val);

		const stl::string& GetAccount() const;
		void SetAccount(const stl::string& val);

		const stl::string& GetAccountSymbol() const;
		void SetAccountSymbol(const stl::string& val);

		const stl::string& GetOrderType() const;
		void SetOrderType(const stl::string& val);

		const stl::string& GetStatus() const;
		void SetStatus(const stl::string& val);

		const stl::string& GetExpDate() const;
		void SetExpDate(const stl::string& val);

		int GetLots() const;
		void SetLots(int val);

		int GetTrailStep() const;
		void SetTrailStep(int val);

		// "m.d.Y H:M:S"
		const stl::string& GetDateFrom() const;
		void SetDateFrom(const stl::string& val);

		const stl::string& GetDateTo() const;
		void SetDateTo(const stl::string& val);

		const stl::string& GetHistoryFile() const;
		void SetHistoryFile(const stl::string& val);

		const stl::string& GetOffersFile() const;
		void SetOffersFile(const stl::string& val);

		bool GetEnableOfferUpdater() const;
		void SetEnableOfferUpdater(bool enable);

		bool GetEnableOfferWriter() const;
		void SetEnableOfferWriter(bool enable);

		const stl::string& GetLoggingFile() const;
		void SetLoggingFile(const stl::string& val);

		bool GetEnableLogging() const;
		void SetEnableLogging(bool enable);

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
		stl::string		m_iniFile;
		stl::string		m_section;
		stl::string		m_instrument;
		stl::string		m_buysell;
		stl::string		m_contingencyID;
		stl::string		m_orderID;
		stl::string		m_primaryID;
		stl::string		m_secondaryID;
		stl::string		m_timeframe;
		stl::string		m_account;
		stl::string		m_accountSymbol;
		stl::string		m_orderType;
		stl::string		m_status;
		stl::string		m_expDate;
		int					m_lots;
		int					m_trailStep;
		stl::string		m_dateFrom;
		stl::string		m_dateTo;
		stl::string		m_historyfile;
		stl::string		m_offersfile;
		bool				m_enableOfferUpdater;
		bool				m_enableOfferWriter;
		stl::string		m_loggingfile;
		bool				m_enableLogging;
		double				m_rangeInPips;
		double				m_rate;
		double				m_rateStop;
		double				m_rateLimit;
	};
} // namespace


#endif // __IniParams_hpp__

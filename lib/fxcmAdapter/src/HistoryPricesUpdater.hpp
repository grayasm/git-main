/*
Copyright (C) 2018 Mihai Vasilian
*/

#ifndef __HistoryPricesUpdater_hpp__
#define __HistoryPricesUpdater_hpp__


#include <vector>
#include <string>
#include <ForexConnect.h>
#include "critical_section.hpp"
#include "autoptr.hpp"
#include "vector.hpp"
#include "OHLCPrice.hpp"


namespace fxcm
{
	class HistoryPricesUpdater
	{
	public:
		typedef stl::vector<fx::OHLCPrice> HistoryPricesVec;

		HistoryPricesUpdater(IO2GSession* session);
		~HistoryPricesUpdater();

		void SetInstrument(const char* sInstrument);
		void SetTimeframe(const char* sTimeframe);
		void ClearPrices();

		int UpdatePrices(IO2GResponse* response);
		const HistoryPricesVec& GetPrices() const;

	private:
		// disable copying
		HistoryPricesUpdater(const HistoryPricesUpdater&);
		HistoryPricesUpdater& operator=(const HistoryPricesUpdater&);

	private:
		IO2GSession*					m_session;
		sys::critical_section			m_criticalSection;
		stl::string					m_instrument;
		stl::string					m_timeframe;
		HistoryPricesVec				m_historyPricesVec;
	};
} // namespace

#endif // __HistoryPricesUpdater_hpp__

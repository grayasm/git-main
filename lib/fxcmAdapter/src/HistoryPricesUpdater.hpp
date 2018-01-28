/*
Copyright (C) 2018 Mihai Vasilian

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software Foundation, Inc.
51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

contact: grayasm@gmail.com
*/

#ifndef __HistoryPricesUpdater_hpp__
#define __HistoryPricesUpdater_hpp__


#include <vector>
#include <ForexConnect.h>
#include "critical_section.hpp"
#include "autoptr.hpp"
#include "vector.hpp"
#include "HistoryPrice.hpp"


namespace fxcm
{
	class HistoryPricesUpdater
	{
	public:
		typedef misc::vector<HistoryPrice> HistoryPricesVec;

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
		misc::critical_section			m_criticalSection;
		misc::string					m_instrument;
		misc::string					m_timeframe;
		HistoryPricesVec				m_historyPricesVec;
	};
} // namespace

#endif // __HistoryPricesUpdater_hpp__

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
	along with this program; if not, write to the Free Software Foundation, Inc.
	51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

	contact: grayasm@gmail.com
*/

#ifndef __OffersPrinter_hpp__
#define __OffersPrinter_hpp__


#include <vector>
#include <ForexConnect.h>
#include "critical_section.hpp"
#include "autoptr.hpp"
#include "Offer.hpp"


namespace fxcm
{
	class OffersPrinter
	{
	public:
		typedef misc::autoptr<OffersPrinter> Ptr;
		OffersPrinter(IO2GSession* session, bool outputOffers);
		~OffersPrinter();

		void PrintOffers(IO2GResponse* response);
		void PrintLevel2MarketData(IO2GResponse* response);

	private:
		// disable copying
		OffersPrinter(const OffersPrinter&);
		OffersPrinter& operator=(const OffersPrinter&);

		void FormatDate(DATE date, char* buf);

	private:
		IO2GSession*					m_session;
		misc::critical_section			m_criticalSection;
		std::vector<Offer>				m_offers;
		bool							m_outputOffers;
	};
} // namespace

#endif // __OffersPrinter_hpp__

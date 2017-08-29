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

#ifndef __OffersUpdater_hpp__
#define __OffersUpdater_hpp__


#include <stddef.h>
#include <ForexConnect.h>
#include "vector.hpp"
#include "critical_section.hpp"
#include "autoptr.hpp"
#include "Offer.hpp"



namespace fxcm
{
	class OffersUpdater
	{
	public:
		typedef misc::autoptr<OffersUpdater> Ptr;
		OffersUpdater(IO2GSession* session);
		~OffersUpdater();

		void UpdateOffers(IO2GResponse* response);
		int GetLastOffer(Offer& offer, const char* sInstrument);
		
	private:
		// disable copying
		OffersUpdater(const OffersUpdater&);
		OffersUpdater& operator=(const OffersUpdater&);

		void FormatDate(DATE date, char* buf);

	private:
		IO2GSession*					m_session;
		misc::critical_section			m_criticalSection;
		misc::vector<Offer>				m_offers;
	};
} // namespace

#endif // __OffersUpdater_hpp__

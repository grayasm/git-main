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
#include <map>
#include <ForexConnect.h>
#include "critical_section.hpp"
#include "autoptr.hpp"
#include "vector.hpp"
#include "Offer.hpp"


namespace fxcm
{
	class OffersUpdater
	{
	public:
		typedef stl::autoptr<OffersUpdater>		Ptr;
		typedef std::map<stl::string, fx::Offer>	OffersMap;

		OffersUpdater(IO2GSession* session);
		~OffersUpdater();
		// disable copying
		OffersUpdater(const OffersUpdater&) = delete;
		OffersUpdater& operator=(const OffersUpdater&) = delete;

		void UpdateOffers(IO2GResponse* response);
		int GetLastOffer(fx::Offer& offer, const char* sInstrument);
        int GetAllOffers(OffersMap& offers);

	private:
		IO2GSession*					m_session;
		misc::critical_section			m_criticalSection;
		OffersMap						m_offersMap;
	};
} // namespace

#endif // __OffersUpdater_hpp__

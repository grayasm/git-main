/*
Copyright (C) 2017 Mihai Vasilian
*/

#ifndef __OffersUpdater_hpp__
#define __OffersUpdater_hpp__


#include <stddef.h>
#include <map>
#include <string>
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
		sys::critical_section			m_criticalSection;
		OffersMap						m_offersMap;
	};
} // namespace

#endif // __OffersUpdater_hpp__

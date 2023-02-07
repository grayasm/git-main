/*
Copyright (C) 2018 Mihai Vasilian
*/

#ifndef __OffersWriter_hpp__
#define __OffersWriter_hpp__


#include <stddef.h>
#include <map>
#include <string>
#include <ForexConnect.h>
#include "critical_section.hpp"
#include "autoptr.hpp"
#include "vector.hpp"
#include "filename.hpp"
#include "IniParams.hpp"
#include "Offer.hpp"



namespace fxcm
{
	class OffersWriter
	{
	public:
		typedef stl::autoptr<OffersWriter>		Ptr;
		typedef stl::vector<fx::Offer>			OffersVec;

		// no copy
		OffersWriter() = delete;
		OffersWriter& operator=(const OffersWriter&) = delete;

		OffersWriter(IO2GSession* session, const IniParams& iniParams);
		~OffersWriter();

		void UpdateOffers(IO2GResponse* response);

	private:
		void WriteOffers();

	private:
		IO2GSession*					m_session;
		sys::critical_section			m_criticalSection;
		IniParams						m_iniParams;
		OffersVec						m_offersVec;
		bool							m_isEnabled;
		sys::filename					m_writeFile;
	};
} // namespace

#endif // __OffersWriter_hpp__

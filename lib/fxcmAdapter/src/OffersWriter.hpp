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

#ifndef __OffersWriter_hpp__
#define __OffersWriter_hpp__


#include <stddef.h>
#include <map>
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
		typedef misc::autoptr<OffersWriter>	Ptr;
		typedef misc::vector<Offer>			OffersVec;

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
		misc::critical_section			m_criticalSection;
		IniParams						m_iniParams;
		OffersVec						m_offersVec;
		bool							m_isEnabled;
		misc::filename					m_writeFile;
	};
} // namespace

#endif // __OffersWriter_hpp__

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


#ifndef __ResponseListener4Offers_hpp__
#define __ResponseListener4Offers_hpp__

#include <stddef.h>
#include <ForexConnect.h>
#include "string.hpp"
#include "event.hpp"
#include "OfferCollection.hpp"
#include "critical_section.hpp"

namespace fxcm
{
	class ResponseListener4Offers : public IO2GResponseListener
	{
	public:
		ResponseListener4Offers(IO2GSession* session);

		// vtable begin
		long addRef();
		long release();
		void onRequestCompleted(const char* requestId, IO2GResponse* response=0);
		void onRequestFailed(const char* requestId, const char* error);
		void onTablesUpdates(IO2GResponse* tablesUpdates);
		// vtable end

		void SetRequestID(const misc::string& requestID);
		void SetInstrument(const misc::string& instrument);
		bool WaitEvents();
		IO2GResponse* GetResponse();
		void PrintOffers(IO2GSession* session,
						IO2GResponse* response,
						const misc::string& instrument);
		void PrintLevel2MarketData(	IO2GSession* session,
									IO2GResponse* response,
									const misc::string& instrument);
	protected:
		~ResponseListener4Offers();

	private:
		// These do not require locking
		void FormatDate(DATE date, char* buf);

	private:
		long					m_RefCount;
		IO2GSession*			m_Session;
		misc::string			m_RequestID;
		misc::string			m_Instrument;
		misc::event				m_ResponseEvent;
		IO2GResponse*			m_Response;
		OfferCollection			m_Offers;
		misc::critical_section	m_CriticalSection;
	};
} // namespace


#endif // __ResponseListener4Offers_hpp__

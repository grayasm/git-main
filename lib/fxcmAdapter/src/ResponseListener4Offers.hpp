/*
Copyright (C) 2017 Mihai Vasilian
*/


#ifndef __ResponseListener4Offers_hpp__
#define __ResponseListener4Offers_hpp__

#include <stddef.h>
#include <string>
#include <ForexConnect.h>
#include "string.hpp"
#include "event.hpp"
#include "critical_section.hpp"
#include "OffersUpdater.hpp"
#include "OffersWriter.hpp"


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

		void SetRequestID(const stl::string& requestID);
		bool WaitEvents();
		IO2GResponse* GetResponse();
		void SetOffersUpdater(OffersUpdater* ou);
		void SetOffersWriter(OffersWriter* ow);


	protected:
		~ResponseListener4Offers();

	private:
		long					m_RefCount;
		IO2GSession*			m_Session;
		stl::string			m_RequestID;
		sys::event				m_ResponseEvent;
		IO2GResponse*			m_Response;
		sys::critical_section	m_CriticalSection;
		OffersUpdater*			m_offersUpdater;
		OffersWriter*			m_offersWriter;
	};
} // namespace


#endif // __ResponseListener4Offers_hpp__

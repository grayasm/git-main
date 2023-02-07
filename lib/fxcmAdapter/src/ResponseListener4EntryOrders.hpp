/*
Copyright (C) 2017 Mihai Vasilian
*/


#ifndef __ResponseListener4EntryOrders_hpp__
#define __ResponseListener4EntryOrders_hpp__

#include <stddef.h>
#include <string>
#include <ForexConnect.h>
#include "string.hpp"
#include "event.hpp"
#include "critical_section.hpp"



namespace fxcm
{
	class ResponseListener4EntryOrders : public IO2GResponseListener
	{
	public:
		ResponseListener4EntryOrders(IO2GSession* session);

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


	protected:
		~ResponseListener4EntryOrders();

	private:
		long					m_RefCount;
		IO2GSession*			m_Session;
		stl::string			m_RequestID;
		sys::event				m_ResponseEvent;
		IO2GResponse*			m_Response;
		sys::critical_section	m_CriticalSection;
	};
} // namespace


#endif // __ResponseListener4EntryOrders_hpp__

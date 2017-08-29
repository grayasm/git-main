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


#ifndef __ResponseListener4FindingOrders_hpp__
#define __ResponseListener4FindingOrders_hpp__

#include <stddef.h>
#include <ForexConnect.h>
#include "string.hpp"
#include "event.hpp"
#include "critical_section.hpp"



namespace fxcm
{
	class ResponseListener4FindingOrders : public IO2GResponseListener
	{
	public:
		ResponseListener4FindingOrders(IO2GSession* session);

		// vtable begin
		long addRef();
		long release();
		void onRequestCompleted(const char* requestId, IO2GResponse* response=0);
		void onRequestFailed(const char* requestId, const char* error);
		void onTablesUpdates(IO2GResponse* tablesUpdates);
		// vtable end

		void SetRequestID(const char* requestID);
		bool WaitEvents();
		IO2GResponse* GetResponse();


	protected:
		~ResponseListener4FindingOrders();

	private:
		long					m_RefCount;
		IO2GSession*			m_Session;
		misc::string			m_RequestID;
		misc::event				m_ResponseEvent;
		IO2GResponse*			m_Response;
		misc::critical_section	m_CriticalSection;
	};
} // namespace


#endif // __ResponseListener4FindingOrders_hpp__

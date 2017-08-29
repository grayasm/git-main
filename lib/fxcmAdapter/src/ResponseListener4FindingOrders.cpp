/*
	Copyright (C) 2017 Mihai Vasilian

	This program is free software; you can redistribute it and/or modify it
	under the terms of the GNU General Public License as published by the
	Free Software Foundation; either version 2 of the License, or (at your
	option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
	See the GNU General Public License for more details.

	You should have received a copy of the GNU General Public License along
	with this program. If not, see http://www.gnu.org/licenses/.

	contact: grayasm@gmail.com
*/

#include "ResponseListener4FindingOrders.hpp"
#include "autocritical_section.hpp"
#include "stream.hpp"
#include <sstream>




namespace fxcm
{
	ResponseListener4FindingOrders::ResponseListener4FindingOrders(IO2GSession* session)
	{
		m_Session = session;
		m_Session->addRef();
		m_RefCount = 1;
		// m_ResponseEvent is non-signaled
		m_RequestID = "";
		m_Response = NULL;
		// m_CriticalSection - is unlocked
	}

	long ResponseListener4FindingOrders::addRef()
	{
		misc::autocritical_section autocs(m_CriticalSection);
		m_RefCount++;
		return m_RefCount;
	}

	long ResponseListener4FindingOrders::release()
	{
		misc::autocritical_section autocs(m_CriticalSection);
		m_RefCount--;
		if (m_RefCount == 0)	// see NonTableManagerSamples, any sample
			delete this;
		return m_RefCount;
	}

	void ResponseListener4FindingOrders::onRequestCompleted(const char* requestId, IO2GResponse* response)
	{
		if (response && m_RequestID == requestId)
		{
			m_Response = response;
			m_Response->addRef();
			if (response->getType() != CreateOrderResponse)
				m_ResponseEvent.unlock();
		}
	}

	void ResponseListener4FindingOrders::onRequestFailed(const char* requestId, const char* error)
	{
		if (m_RequestID == requestId)
		{
			misc::cout << __FUNCTION__ 
				<< ": The request has been failed. ID: "
				<< requestId << " : " << error << std::endl;
			m_ResponseEvent.unlock();
		}
	}

	void ResponseListener4FindingOrders::onTablesUpdates(IO2GResponse* tablesUpdates)
	{
	}

	void ResponseListener4FindingOrders::SetRequestID(const char* requestID)
	{
		m_RequestID = requestID;
		if (m_Response)
		{
			m_Response->release();
			m_Response = NULL;
		}
		m_ResponseEvent.unlock();
	}

	bool ResponseListener4FindingOrders::WaitEvents()
	{
		return (m_ResponseEvent.trylock(30000) == 0);
	}

	IO2GResponse* ResponseListener4FindingOrders::GetResponse()
	{
		if (m_Response)
			m_Response->addRef();
		return m_Response; // ~O2G2Ptr will release() it.
	}

	ResponseListener4FindingOrders::~ResponseListener4FindingOrders()
	{
		if (m_Response)
			m_Response->release();
		m_Session->release();
		// m_ResponseEvent will CloseHandle itself on ~dtor
		// m_offersPrinter is owned by the Session
	}

} // namespace

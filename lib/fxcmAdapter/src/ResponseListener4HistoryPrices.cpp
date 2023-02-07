/*
Copyright (C) 2018 Mihai Vasilian
*/

#include "ResponseListener4HistoryPrices.hpp"
#include "autocritical_section.hpp"
#include "stream.hpp"
#include <sstream>




namespace fxcm
{
	ResponseListener4HistoryPrices::ResponseListener4HistoryPrices(IO2GSession* session)
	{
		m_Session = session;
		m_Session->addRef();
		m_RefCount = 1;
		// m_ResponseEvent is non-signaled
		m_RequestID = "";
		m_Response = NULL;
		// m_CriticalSection - is unlocked
		stl::cout.precision(6);
	}

	long ResponseListener4HistoryPrices::addRef()
	{
		sys::autocritical_section autocs(m_CriticalSection);
		m_RefCount++;
		return m_RefCount;
	}

	long ResponseListener4HistoryPrices::release()
	{
		// protect m_CriticalSection against 'delete this'
		{
			sys::autocritical_section autocs(m_CriticalSection);
			m_RefCount--;
			if (m_RefCount)
				return m_RefCount;
		}

		delete this;
		return 0;
	}

	void ResponseListener4HistoryPrices::onRequestCompleted(const char* requestId, IO2GResponse* response)
	{
		if (response && m_RequestID == requestId)
		{
			m_Response = response;
			m_Response->addRef();
			if (response->getType() != CreateOrderResponse)
				m_ResponseEvent.unlock();
		}
	}

	void ResponseListener4HistoryPrices::onRequestFailed(const char* requestId, const char* error)
	{
		if (m_RequestID == requestId)
		{
			stl::cout << __FUNCTION__
				<< ": The request has been failed. ID: "
				<< requestId << " : " << error << std::endl;
			m_ResponseEvent.unlock();
		}
	}

	void ResponseListener4HistoryPrices::onTablesUpdates(IO2GResponse* tablesUpdates)
	{
		// empty in GetHistPrices sample
	}

	void ResponseListener4HistoryPrices::SetRequestID(const stl::string& requestID)
	{
		m_RequestID = requestID;
		if (m_Response)
		{
			m_Response->release();
			m_Response = NULL;
		}
		m_ResponseEvent.unlock();
	}

	bool ResponseListener4HistoryPrices::WaitEvents()
	{
		return (m_ResponseEvent.trylock(30000) == 0);
	}

	IO2GResponse* ResponseListener4HistoryPrices::GetResponse()
	{
		if (m_Response)
			m_Response->addRef();
		return m_Response; // ~O2G2Ptr will release() it.
	}

	ResponseListener4HistoryPrices::~ResponseListener4HistoryPrices()
	{
		if (m_Response)
			m_Response->release();
		m_Session->release();
		// m_ResponseEvent will CloseHandle itself on ~dtor
	}

} // namespace

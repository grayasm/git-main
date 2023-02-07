/*
Copyright (C) 2018 Mihai Vasilian
*/

#include "OrderMonitor.hpp"
#include "algorithm.hpp"





namespace fxcm
{
	OrderMonitor::OrderMonitor(IO2GOrderRow *order)
	{
		m_orderState = OrderExecuting;
		// m_rejectMessage; - empty
		// m_trades; - empty  (has allocated resources*)
		// m_closedTrades; - empty (has allocated resources*)
		m_totalAmount = 0;
		m_rejectAmount = 0;
		m_order = order;
		m_order->addRef();		// (allocated *resource)
		m_result = Executing;
	}

	OrderMonitor::~OrderMonitor()
	{
		for (size_t i = 0; i < m_trades.size(); ++i)
			m_trades[i]->release();
		for (size_t i = 0; i < m_closedTrades.size(); ++i)
			m_closedTrades[i]->release();
		m_order->release();
	}

	void OrderMonitor::OnTradeAdded(IO2GTradeRow *trade)
	{
		stl::string tradeOrderID = trade->getOpenOrderID();
		stl::string orderID = m_order->getOrderID();

		if (tradeOrderID == orderID)
		{
			trade->addRef();
			m_trades.push_back(trade);

			if (m_orderState == OrderExecuted ||
				m_orderState == OrderRejected ||
				m_orderState == OrderCanceled)
			{
				if (IsAllTradeReceived())
					SetResult(true);
			}
		}

	}

	void OrderMonitor::OnOrderDeleted(IO2GOrderRow *order)
	{
		stl::string deletedOrderID = order->getOrderID();
		stl::string orderID = m_order->getOrderID();

		if (deletedOrderID == orderID)
		{
			// Store Reject amount
			if (*(order->getStatus()) == 'R')
			{
				m_orderState = OrderRejected;
				m_rejectAmount = order->getAmount();
				m_totalAmount = order->getOriginAmount() - m_rejectAmount;

				if (!m_rejectMessage.empty() && IsAllTradeReceived())
					SetResult(true);
			}
			else if (*(order->getStatus()) == 'C')
			{
				m_orderState = OrderCanceled;
				m_rejectAmount = order->getAmount();
				m_totalAmount = order->getOriginAmount() - m_rejectAmount;
				if (IsAllTradeReceived())
					SetResult(false);
			}
			else
			{
				m_rejectAmount = 0;
				m_totalAmount = order->getOriginAmount();
				m_orderState = OrderExecuted;
				if (IsAllTradeReceived())
					SetResult(true);
			}
		}
	}

	void OrderMonitor::OnMessageAdded(IO2GMessageRow *message)
	{
		if (m_orderState == OrderRejected ||
			m_orderState == OrderExecuting)
		{
			bool isRejectMessage = CheckAndStoreMessage(message);
			if (m_orderState == OrderRejected && isRejectMessage)
				SetResult(true);
		}
	}

	void OrderMonitor::OnClosedTradeAdded(IO2GClosedTradeRow *closedTrade)
	{
		stl::string closedTradeOrderID = closedTrade->getCloseOrderID();
		stl::string orderID = m_order->getOrderID();
		
		if (orderID == closedTradeOrderID)
		{
			closedTrade->addRef();
			m_closedTrades.push_back(closedTrade);
		}

		if (m_orderState == OrderExecuted ||
			m_orderState == OrderRejected ||
			m_orderState == OrderCanceled)
		{
			if (IsAllTradeReceived())
				SetResult(true);
		}
	}

	OrderMonitor::ExecutionResult OrderMonitor::GetResult() const
	{
		return m_result;
	}

	bool OrderMonitor::IsOrderCompleted() const
	{
		return m_result != Executing;
	}

	IO2GOrderRow* OrderMonitor::GetOrder()
	{
		m_order->addRef();
		return m_order; // ~O2G2Ptr will release() it.
	}

	void OrderMonitor::GetTrades(IO2GTradeRowVec& trades) const
	{
		trades.clear();
		trades.resize(m_trades.size());
		stl::copy(m_trades.begin(), m_trades.end(), trades.begin());
		for (size_t i = 0; i < m_trades.size(); ++i)
			m_trades[i]->addRef();
	}

	void OrderMonitor::GetClosedTrades(IO2GClosedTradeRowVec& closedTrades) const
	{
		closedTrades.clear();
		closedTrades.resize(m_closedTrades.size());
		stl::copy(m_closedTrades.begin(), m_closedTrades.end(), closedTrades.begin());
		for (size_t i = 0; i < m_closedTrades.size(); ++i)
			m_closedTrades[i]->addRef();
	}

	int OrderMonitor::GetRejectAmount() const
	{
		return m_rejectAmount;
	}

	stl::string OrderMonitor::GetRejectMessage() const
	{
		return m_rejectMessage;
	}

	void OrderMonitor::SetResult(bool bSuccess)
	{
		if (bSuccess)
		{
			if (m_rejectAmount == 0)
				m_result = Executed;
			else
				m_result = (m_trades.size() == 0 && m_closedTrades.size() == 0) ? FullyRejected : PartialRejected;
		}
		else
			m_result = Canceled;
	}

	bool OrderMonitor::IsAllTradeReceived() const
	{
		if (m_orderState == OrderExecuting)
			return false;

		int currentTotalAmount = 0;
		for (size_t i = 0; i < m_trades.size(); ++i)
			currentTotalAmount += m_trades[i]->getAmount();

		for (size_t i = 0; i < m_closedTrades.size(); ++i)
			currentTotalAmount += m_closedTrades[i]->getAmount();

		return currentTotalAmount == m_totalAmount;
	}

	bool OrderMonitor::CheckAndStoreMessage(IO2GMessageRow *message)
	{
		stl::string feature;
		feature = message->getFeature();

		if (feature == O2G2::MessageFeature::MarketCondition)
		{
			stl::string text = message->getText();
			size_t findPos = text.find(m_order->getOrderID());
			if (findPos != stl::string::npos)
			{
				m_rejectMessage = message->getText();
				return true;
			}
		}
		return false;
	}

} // namespace

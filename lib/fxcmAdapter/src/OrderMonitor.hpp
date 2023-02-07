/*
Copyright (C) 2018 Mihai Vasilian
*/

#ifndef __OrderMonitor_hpp__
#define __OrderMonitor_hpp__

#include <stddef.h>
#include <string>
#include <ForexConnect.h>
#include "autoptr.hpp"
#include "vector.hpp"
#include "string.hpp"


namespace fxcm
{
	class OrderMonitor
	{
	public:
		typedef stl::autoptr<OrderMonitor> Ptr;
		typedef stl::vector<IO2GTradeRow*>	IO2GTradeRowVec;
		typedef stl::vector<IO2GClosedTradeRow*>	IO2GClosedTradeRowVec;

		enum ExecutionResult
		{
			Executing = 0,
			Executed,
			PartialRejected,
			FullyRejected,
			Canceled
		};

		explicit OrderMonitor(IO2GOrderRow *order);
		~OrderMonitor();
		OrderMonitor(const OrderMonitor&) = delete;
		OrderMonitor& operator=(const OrderMonitor&) = delete;


		void OnTradeAdded(IO2GTradeRow *trade);
		void OnOrderDeleted(IO2GOrderRow *order);
		void OnMessageAdded(IO2GMessageRow *message);
		void OnClosedTradeAdded(IO2GClosedTradeRow *closedTrade);


		ExecutionResult GetResult() const;
		bool IsOrderCompleted() const;
		IO2GOrderRow* GetOrder();
		void GetTrades(IO2GTradeRowVec& trades) const;
		void GetClosedTrades(IO2GClosedTradeRowVec& closedTrades) const;
		int GetRejectAmount() const;
		stl::string GetRejectMessage() const;

	private:
		enum OrderState
		{
			OrderExecuting = 0,
			OrderExecuted,
			OrderCanceled,
			OrderRejected
		};

		void SetResult(bool bSuccess);
		bool IsAllTradeReceived() const;
		bool CheckAndStoreMessage(IO2GMessageRow *message);

	private:
		OrderState				m_orderState;
		stl::string			m_rejectMessage;
		IO2GTradeRowVec			m_trades;
		IO2GClosedTradeRowVec	m_closedTrades;
		int						m_totalAmount;
		int						m_rejectAmount;
		IO2GOrderRow*			m_order;
		ExecutionResult			m_result;
	};
} // namespace


#endif // __OrderMonitor_hpp__

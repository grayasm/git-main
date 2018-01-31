/*
  Copyright (C) 2014 Mihai Vasilian

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


#ifndef __Position_hpp__
#define __Position_hpp__

// C
// C++
// local
#include "autoptr.hpp"
#include "Currency.hpp"


namespace fx
{

	//! Position closed or in the market.
	class Position
	{
	public:
		typedef misc::autoptr<Position>	Ptr;

		Position();

		Position(const misc::string& orderID,
			const misc::string& tradeID,
			const Currency& currency,
			bool buy,
			double amount,
			double commission,
			double interest);

		~Position();
		Position(const Position& tc);
		Position& operator=(const Position& tc);

		//! Returns the market order for this position.
		const misc::string& GetOrderID() const;

		//! Returns the market open trade id. Empty if entry order.
		const misc::string& GetTradeID() const;

		//! Currency at the time this position entered the market.
		const Currency& GetCurrency() const;

		//! False is position is a SELL (Short).
		bool IsBuy() const;

		//! Returns the total number of lots (K).
		double GetAmount() const;			

		//! False is position was closed.
		bool IsOpen() const;    

		//! Request to close this position at the given price.
		void Close(const Price& close);
		
		//! Total margin allocated for this position.
		double GetMMR() const;

		//! Returns the pips scored by this position at the given price.		
		//! Position must not be closed.
		//! Pips are for 1 unit. To get the total number, multiply with the amount.
		double GetPL(const Price& rate) const;

		//! Returns the total profit scored by this position at the given price.
		//! Position must not be closed.
		//! Commission and interest are not included.
		double GetGPL(const Price& rate) const;

		//! Returns the pips scored by this position at closing time.
		//! Position must be closed.
		//! Pips are for 1 unit. To get the total number, multiply with the amount.
		double GetPL() const;

		//! Returns the total profit scored by this position at closing time.
		//! Position must be closed.
		//! Commission and interest are not included in the result.
		double GetGPL() const;

		//! Returns the closing price.
		//! Positions must be closed.
		const Price& GetClose() const;

		//! Set the commission for entire amount of this position.
		void SetCommission(double commission);
		
		//! Get the broker commission.
		double GetCommission() const;

		//! Set the interest for period while entire amount was opened in the market.
		void SetInterest(double interest);
		
		//! Get the interest.
		double GetInterest() const;

		//! Returns the market price where this position would have the
		//! given number of pips.
		Price GetQuotes(double pips) const;

		//! Returns a string with internal data for debugging
		misc::string ToString() const;

	private:
		void Init();

	private:
		misc::string	m_orderID;		// "222140555" order ID
		misc::string	m_tradeID;		// "105902921" trade ID
		bool			m_isOpen;       // false for closed position
		Currency		m_currency;		// currency at the open price
		bool			m_buy;          // false for sell position
		double			m_amount;       // lot amount in K    
		Price			m_close;		// market price where position was closed
		double			m_commission;	// commission for entire amount opened/closed
		double			m_interest;		// interest (need confirmation)
	};


	//##########################################################################
	struct openprice_greater : misc::binary_function <Position,Position,bool>
	{
		bool operator()(const Position& x, const Position& y) const;
	};

	//##########################################################################


}  // namespace fx


#endif // __Position_hpp__
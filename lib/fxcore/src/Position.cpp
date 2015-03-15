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


#include "Position.hpp"

//c
#include <stdio.h>
#include <stdlib.h>
#include <float.h>
//c++
//local
#include "strconv.hpp"
#include "math.hpp"



namespace fx
{	    
	void Position::Init()
	{
		// m_orderID
		// m_tradeID
		m_isOpen = false;
		// m_currency;
		m_buy = false;
		m_amount = 0;
		// m_close;
		m_commission = 0;
		m_interest = 0;
	}

	Position::Position()
	{
		Init();
	}

	Position::Position(
		const misc::string& orderID,
		const misc::string& tradeID,
		const Currency& currency,
		bool buy,
		double amount,
		double commission,
		double interest)
	{
		m_orderID = orderID;
		m_tradeID = tradeID;
		m_isOpen = true;
		m_currency = currency;
		m_buy = buy;
		m_amount = amount;
		m_commission = commission;
		m_interest = interest;
	}

	Position::~Position()
	{
	}

	Position::Position(const Position& tc)
	{        
		*this = tc;
	}

	Position& Position::operator=(const Position& tc)
	{
		if(this != &tc)
		{
			m_orderID = tc.m_orderID;
			m_tradeID = tc.m_tradeID;
			m_isOpen = tc.m_isOpen;
			m_currency = tc.m_currency;
			m_buy = tc.m_buy;
			m_amount = tc.m_amount;
			m_close = tc.m_close;
			m_commission = tc.m_commission;
			m_interest = tc.m_interest;
		}
		return *this;
	}

	const misc::string& Position::GetOrderID() const
	{
		return m_orderID;
	}

	const misc::string& Position::GetTradeID() const
	{
		return m_tradeID;
	}

	const Currency& Position::GetCurrency() const
	{
		return m_currency;
	}

	bool Position::IsBuy() const
	{ 
		return m_buy;
	}

	double Position::GetAmount() const
	{ 
		return m_amount;
	}

	bool Position::IsOpen() const 
	{
		return m_isOpen;
	}

	void Position::Close(const Price& close)
	{
		if(!m_isOpen)
			throw misc::exception("Position is already closed.");

		m_close = close;
		m_isOpen = false;
	}

	double Position::GetMMR() const
	{
		if(m_isOpen)
		{
			return m_currency.GetMargin() * m_amount;
		}
		else
		{
			return 0;
		}
	}

	double Position::GetPL(const Price& rate) const
	{
		if(!m_isOpen)
			throw misc::exception("Position is already closed.");
		
		const Price& p_Open  = m_currency.GetPrice();
		const Price& p_Close = rate;
		
		// Calculate total pips for this position at give price.
		double s = (m_buy == true ? 1.0f : -1.0f);
		double open  = (m_buy == true ? p_Open.GetBuy() : p_Open.GetSell());
		double close = (m_buy == true ? p_Close.GetSell() : p_Close.GetBuy());
		
		double pips = s * (close - open) * m_currency.GetRate2Pip();
		return pips;
	}

	double Position::GetGPL(const Price& rate) const
	{
		if(!m_isOpen)
			throw misc::exception("Position is already closed.");

		double pips = GetPL(rate);
		double profit = m_amount * pips * m_currency.GetPipCost();
		return profit;
	}

	double Position::GetPL() const
	{
		if(m_isOpen)
			throw misc::exception("Position must be closed.");

		const Price& p_Open  = m_currency.GetPrice();	

		// Calculate total pips for this position at give price.
		double s = (m_buy == true ? 1.0f : -1.0f);
		double open  = (m_buy == true ? p_Open.GetBuy() : p_Open.GetSell());
		double close = (m_buy == true ? m_close.GetSell() : m_close.GetBuy());

		double pips = s * (close - open) * m_currency.GetRate2Pip();
		return pips;
	}

	double Position::GetGPL() const
	{
		if(m_isOpen)
			throw misc::exception("Position must be closed.");

		double pips = GetPL();
		double profit = m_amount * pips * m_currency.GetPipCost();
		return profit;
	}

	const Price& Position::GetClose() const
	{
		if(m_isOpen)
			throw misc::exception("Position must be closed.");

		return m_close;
	}

	void Position::SetCommission(double commission)
	{
		m_commission = commission;
	}

	double Position::GetCommission() const
	{
		return m_commission;
	}

	void Position::SetInterest(double interest)
	{
		m_interest = interest;
	}

	double Position::GetInterest() const
	{
		return m_interest;
	}

	Price Position::GetQuotes(double pips) const
	{
		if(!m_isOpen)
			throw misc::exception("Position is already closed.");

		double s = (m_buy == true ? 1.0f : -1.0f);
		double rate2pip = m_currency.GetRate2Pip();
		const Price& p_Open = m_currency.GetPrice();
		double open = (m_buy == true ? p_Open.GetBuy() : p_Open.GetSell());
		double close = open + s * pips / rate2pip;
		double spread = (p_Open.GetBuy() - p_Open.GetSell()) * rate2pip;

		double q1 = (m_buy == true ? close + spread : close);
		double q2 = (m_buy == true ? close : close - spread);

		return Price(q1, q2);
	}

	misc::string Position::ToString() const
	{
		misc::string msg;
		msg += "O: "; msg += m_orderID; msg += "; ";
		msg += "T: "; msg += m_tradeID; msg += "; ";
		msg += m_isOpen == true ? "Open  ; " : "Closed; ";
		msg += m_currency.GetSymbol(); msg += "; ";
		msg += m_buy == true ? "B; " : "S; ";
		msg += "L: "; msg += misc::from_value(m_amount, 0); msg += "k; ";
		msg += "MO: ";
		short digits = (short)math::digits(m_currency.GetRate2Pip());
		const fx::Price& openPrice = m_currency.GetPrice();
		msg += (openPrice.GetBuy()  == FLT_MAX ? "0" : misc::from_value(openPrice.GetBuy() , digits)); msg += "-";
		msg += (openPrice.GetSell() == FLT_MAX ? "0" : misc::from_value(openPrice.GetSell(), digits)); msg += "; ";
		
		msg += "MC: ";
		msg += (m_close.GetBuy()  == FLT_MAX ? "0" : misc::from_value(m_close.GetBuy(),  digits)); msg += "-";
		msg += (m_close.GetSell() == FLT_MAX ? "0" : misc::from_value(m_close.GetSell(), digits)); msg += "; ";
		
		return msg;
	}



	//##########################################################################
	bool openprice_greater::operator()(const Position& x, const Position& y) const
	{
		const fx::Currency& xc = x.GetCurrency();
		const fx::Price& xp = xc.GetPrice();
		double xop = (x.IsBuy() ? xp.GetBuy() : xp.GetSell());

		const fx::Currency& yc = y.GetCurrency();
		const fx::Price& yp = yc.GetPrice();
		double yop = (y.IsBuy() ? yp.GetBuy() : yp.GetSell());

		return xop > yop;
	}


}  // namespace fx
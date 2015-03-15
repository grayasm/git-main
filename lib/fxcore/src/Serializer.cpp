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

#include "Serializer.hpp"



namespace fx
{
	Serializer::Serializer(const misc::string& file)
	{
		m_out = new misc::ofstream(file.c_str());
	}

	Serializer::~Serializer()
	{
		if(m_out->is_open())
			m_out->close();
		delete m_out;
	}
	
	Serializer& Serializer::operator<<(const StrategyHedgeFixGrid& s)
	{
		if(!m_out->is_open())
			return *this;

		*m_out << "\nS; " << "hfg";
		(*this) << s.m_ep;			// entry position
		*m_out << "\nwait; " << (s.m_wait == true ? "true" : "false");
		*m_out << "\n dh; " << s.m_dh;
		*m_out << "\n dg; " << s.m_dg;
		*m_out << "\n ha; " << s.m_ha;
		*m_out << "\n de; " << s.m_de;
		*m_out << "\n maxn; " << s.m_maxn;
		*m_out << "\n maxp; " << s.m_maxp;
		*m_out << "\n plugin; " << s.m_plugin->GetID().c_str();

		(*this) << s.m_ct;

		*m_out << "\nenter; "; *this << s.m_enter;	// where entered the market
		*m_out << "\nrate; "; *this << s.m_rate;	// at that time, not important;
		*m_out << "\nprev_rate; "; *this << s.m_prev_rate;	// previous price

		*m_out << "\ngrid; " << s.m_grid.size(); 

		for(size_t i = 0; i < s.m_grid.size(); ++i)
		{
			const FixGridPositionStub& stub = *(s.m_grid[i]);
			*this << stub;			
		}

		*m_out << "\nblocked; " << (s.m_blocked == true ? "true" : "false");
		
		return *this;

	}

	Serializer& Serializer::operator<<(const Strategy2HedgeFixGrid& s)
	{
		if(!m_out->is_open())
			return *this;

		*m_out << "\nS; " << "2hfg";
		(*this) << s.m_ep;			// entry position
		*m_out << "\nwait; " << (s.m_wait == true ? "true" : "false");
		*m_out << "\n dh; " << s.m_dh;
		*m_out << "\n dg; " << s.m_dg;
		*m_out << "\n ha; " << s.m_ha;
		*m_out << "\n de; " << s.m_de;
		*m_out << "\n maxn; " << s.m_maxn;
		*m_out << "\n maxp; " << s.m_maxp;
		*m_out << "\n plugin; " << s.m_plugin->GetID().c_str();

		(*this) << s.m_ct;

		*m_out << "\nenter; "; *this << s.m_enter;	// where entered the market
		*m_out << "\nrate; "; *this << s.m_rate;	// at that time, not important;
		*m_out << "\nprev_rate; "; *this << s.m_prev_rate;	// previous price

		*m_out << "\ngrid; " << s.m_grid.size(); 

		for(size_t i = 0; i < s.m_grid.size(); ++i)
		{
			const FixGridPositionStub& stub = *(s.m_grid[i]);
			*this << stub;			
		}

		*m_out << "\nblocked; " << (s.m_blocked == true ? "true" : "false");

		return *this;
	}

	Serializer& Serializer::operator<<(const StrategyFixGrid& s)
	{
		if(!m_out->is_open())
			return *this;

		*m_out << "\nS; " << "1fg";
		(*this) << s.m_ep;			// entry position
		*m_out << "\nwait; " << (s.m_wait == true ? "true" : "false");
		*m_out << "\n dg; " << s.m_dg;
		*m_out << "\n pa; " << s.m_pa;
		*m_out << "\n de; " << s.m_de;
		*m_out << "\n maxn; " << s.m_maxn;
		*m_out << "\n maxp; " << s.m_maxp;
		*m_out << "\n plugin; " << s.m_plugin->GetID().c_str();

		(*this) << s.m_ct;

		*m_out << "\nrate; "; *this << s.m_rate;	// at that time, not important;
		*m_out << "\nprev_rate; "; *this << s.m_prev_rate;	// previous price

		*m_out << "\ngrid; " << s.m_grid.size(); 

		for(size_t i = 0; i < s.m_grid.size(); ++i)
		{
			const FixGridPositionStub& stub = *(s.m_grid[i]);
			*this << stub;			
		}

		*m_out << "\nblocked; " << (s.m_blocked == true ? "true" : "false");

		return *this;
	}

	Serializer& Serializer::operator<<(const Price& price)
	{
		*m_out << price.GetBuy() << " ; ";
		*m_out << price.GetSell() << " ; ";

		return *this;
	}

	Serializer& Serializer::operator<<(const Currency& currency)
	{
		*m_out << currency.GetSymbol() << " ; ";
		(*this) << currency.GetPrice();
		*m_out << currency.GetMargin() << " ; ";
		*m_out << currency.GetPipCost() << " ; ";
		*m_out << currency.GetRate2Pip() << " ; ";

		return *this;
	}
	
	Serializer& Serializer::operator<<(const Position& p)
	{
		if(!m_out->is_open())
			return *this;

		*m_out << "\nP; ";
		*m_out << p.GetOrderID().c_str() << " ; " ;
		*m_out << p.GetTradeID().c_str() << " ; " ;
		bool isOpen = p.IsOpen();
		*m_out << (isOpen == true ? "open" : "closed") << " ; ";
		(*this) << p.GetCurrency();

		*m_out << (p.IsBuy() == true ? "buy" : "sell") << " ; ";
		int amount = (int)p.GetAmount();
		*m_out << amount << " ; ";
		*m_out << p.GetCommission() << " ; ";
		*m_out << p.GetInterest() << " ; ";

		if(!isOpen)
		{
			(*this) << p.GetClose();
		}

		return *this;
	}

	Serializer& Serializer::operator<<(const Transaction& t)
	{
		if(!m_out->is_open())
			return *this;

		*m_out << "\nT ; ";

		const Transaction::Positions& positions = t.GetPositions();
		*m_out << positions.size();

		for(size_t i = 0; i < positions.size(); ++i)
		{
			const Position& p = positions[i];
			(*this) << p;
		}

		return *this;
	}

	Serializer& Serializer::operator<<(const FixGridPositionStub& ps)
	{
		if(!m_out->is_open())
			return *this;

		*m_out << "\nfgps; ";
		(*this) << ps.m_gp;
		*m_out << "\nde; " << ps.m_de;
		
		// m_plugin - serialized by parent
		// *m_ct	- serialized by parent

		(*this) << ps.m_gt;
		*m_out << "\nrate; "; *this << ps.m_rate;

		return *this;
	}

}; // namespace
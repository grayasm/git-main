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


#include "FixGridPositionStub.hpp"
#include <math.h>
#include <float.h>
#include "stream.hpp"
#include "strconv.hpp"
#include "Serializer.hpp"
#include "Deserializer.hpp"

namespace fx
{
	//##########################################################################
	FixGridPositionStub::FixGridPositionStub()
	{
		Reset();
	}

	FixGridPositionStub::~FixGridPositionStub()
	{
	}

	FixGridPositionStub::FixGridPositionStub(const FixGridPositionStub& tc)
	{
		*this = tc;
	}

	FixGridPositionStub& FixGridPositionStub::operator=(const FixGridPositionStub& tc)
	{
		if(this != &tc)
		{
			Reset();

			m_gp = tc.m_gp;
			m_de = tc.m_de;
			m_plugin = tc.m_plugin;
			// m_ct = tc.m_ct;  - needs to be updated by parent
			m_gt = tc.m_gt;
			m_rate = tc.m_rate;
		}
		return *this;
	}

	FixGridPositionStub::FixGridPositionStub(
		const fx::Position& gp,			// fix grid position to be monitored
		double de,						// distance to exit
		MarketPlugin::Ptr plugin,		// market execution plugin
		fx::Transaction* ct)			// current transaction
	{
		Reset();

		m_gp = gp;
		m_de = de;
		m_plugin = plugin;
		m_ct = ct;
		// m_gt;
		// m_rate

		Validate();
	}

	bool FixGridPositionStub::Update(const Price& rate)
	{
		bool ret = false;		
		m_rate = rate;
		
		if(CanOpenOrder())
		{
			ret = OpenOrder();
		}
		else if(CanCloseOrder())
		{
			ret = CloseOrder();
		}
		return ret;
	}

	bool FixGridPositionStub::IsActive() const
	{
		return !m_gt.IsEmpty();
	}

	void FixGridPositionStub::Reset()
	{
		m_gp = fx::Position(); // OrderID = ""
		m_de = 0;
		m_plugin = 0;
		m_ct = 0;
		m_gt = fx::Transaction();
		m_rate = fx::Price(); // FLT_MAX
	}

	void FixGridPositionStub::Validate()
	{
		bool valid = true;
		if(m_de <= 0)
			valid = false;

		if(!valid)
			throw misc::exception("Invalid position stub");
	}

	bool FixGridPositionStub::CanOpenOrder()
	{
		// has order open at market ?
		if(!m_gt.IsEmpty())
			return false;

		// compare market price with grid position			
		const fx::Price& gpp = m_gp.GetCurrency().GetPrice();
		bool sell = !m_gp.IsBuy();
		double posp = (sell == true ? gpp.GetSell() : gpp.GetBuy());		// position price
		double marp = (sell == true ? m_rate.GetSell() : m_rate.GetBuy());	// market price

		/* I do not expect the price to bounce over the grid location, because
		 * in case of big volatility the entry will not happen.
		 */
		bool open = (sell == true ? marp <= posp : marp >= posp);
		return open;
	}

	bool FixGridPositionStub::OpenOrder()
	{
		if(!m_gt.IsEmpty())
			throw misc::exception("Order already exists.");

		misc::vector<fx::Position> otrades; // same OrderID;
		misc::string error;
		if(m_plugin->OpenMarketOrder(m_gp, otrades, error))
		{
			for(size_t i = 0; i < otrades.size(); ++i)
			{
				m_gt.Add(otrades[i]);
				m_ct->Add(otrades[i]);
			}
		}
		return true;
	}

	bool FixGridPositionStub::CanCloseOrder()
	{
		if(m_gt.IsEmpty())
			return false;

		bool sell = !m_gp.IsBuy();
		double midp = 0;
		for(fx::Transaction::PosIt pIt = m_gt.GetBegin();
			pIt != m_gt.GetEnd(); ++pIt)
		{
			const fx::Price& price = pIt->GetCurrency().GetPrice();

			// Calculate with the open price (Sell - Sell, Buy - Buy)
			// otherwise the spread can kill the hedge's distance to exit.
			midp += (sell == true ? price.GetSell() : price.GetBuy());
		}

		midp /= m_gt.Size();

		double marp = (sell == true ? m_rate.GetSell() : m_rate.GetBuy());
		double pip2rate = 1 / m_gp.GetCurrency().GetRate2Pip();

		// The distance to exit is between Sell-Sell or Buy-Buy prices for now.
		double exitp = (sell == true ?
			midp + m_de * pip2rate :
			midp - m_de * pip2rate);
		bool close = (sell == true ? marp >= exitp : marp <= exitp);

		return close;
	}


	bool FixGridPositionStub::CloseOrder()
	{
		if(m_gt.IsEmpty())
			throw misc::exception("Cannot find the order.");

		// grid positions
		fx::Transaction::Positions& gtpositions = 
			const_cast<fx::Transaction::Positions&>(m_gt.GetPositions());

		for(fx::Transaction::PosIt gIt = gtpositions.begin(); gIt != gtpositions.end(); /*..*/)
		{
			misc::vector<fx::Position> ctrades;				
			misc::string error;
			if(m_plugin->CloseMarketOrder(*gIt, ctrades, error))
			{
				// 1) remove grid position from parent transaction (strategy member)
				// 2) remove grid position from grid transaction (local member)
				// 3) add closed positions (liquidity) to parent transaction

				fx::Transaction::Positions& ctpositions = 
					const_cast<fx::Transaction::Positions&>(m_ct->GetPositions());

				for(fx::Transaction::PosIt ctIt = ctpositions.begin(); 
					ctIt != ctpositions.end(); ++ctIt)
				{
					if(ctIt->GetOrderID() == gIt->GetOrderID() &&
						ctIt->GetTradeID() == gIt->GetTradeID())
					{
						//1)
						ctpositions.erase(ctIt);
						//2)
						fx::Transaction::PosIt tmpIt = gtpositions.erase(gIt);
						gIt = tmpIt;
						break;
					}
				}

				//3)
				for(size_t i = 0; i < ctrades.size(); ++i)
					m_ct->Add(ctrades[i]);
			}
			else
			{
				++gIt;
			}
		}
		return true;
	}
} // namespace

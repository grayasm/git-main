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


#include "StrategyHedgeFixGrid.hpp"
#include <math.h>
#include <float.h>
#include "stream.hpp"
#include "strconv.hpp"
#include "Serializer.hpp"
#include "Deserializer.hpp"

namespace fx
{
	StrategyHedgeFixGrid::StrategyHedgeFixGrid()
	{
		Reset();
	}

	StrategyHedgeFixGrid::StrategyHedgeFixGrid(const StrategyHedgeFixGrid& tc)
	{
		Reset();
		*this = tc;
	}

	StrategyHedgeFixGrid& StrategyHedgeFixGrid::operator=(const StrategyHedgeFixGrid& tc)
	{
		if(this != &tc)
		{
			m_ep = tc.m_ep;
			m_wait = tc.m_wait;
			m_dh = tc.m_dh;
			m_dg = tc.m_dg;
			m_ha = tc.m_ha;
			m_de = tc.m_de;
			m_maxn = tc.m_maxn;
			m_maxp = tc.m_maxp;
			m_plugin = tc.m_plugin;
			m_ct = tc.m_ct;
			m_enter = tc.m_enter;
			m_rate = tc.m_rate;
			m_prev_rate = tc.m_prev_rate;
			m_grid = tc.m_grid;
			// update pointers to new address
			for(size_t i = 0; i < m_grid.size(); ++i)
				m_grid[i]->m_ct = &m_ct;
			m_blocked = tc.m_blocked;
		}
		return *this;
	}

	StrategyHedgeFixGrid::StrategyHedgeFixGrid(
		const fx::Position& ep,
		bool wait,
		double dh,
		double dg,
		double ha,
		double de,
		double maxn,
		double maxp,
		MarketPlugin::Ptr plugin)
	{
		m_ep = ep;
		m_wait = wait;
		m_dh = dh;
		m_dg = dg;
		m_ha = ha;
		m_de = de;
		m_maxn = maxn;
		m_maxp = maxp;
		m_plugin = plugin;

		// m_ct;
		// m_enter;
		// m_rate;
		// m_prev_rate;
		// m_grid;
		m_blocked = false;

		Validate();
	}

	
	StrategyHedgeFixGrid::~StrategyHedgeFixGrid()
	{
	}

	void StrategyHedgeFixGrid::AcceptVisitor(StrategyVisitor& visitor)
	{
		visitor.Visit(*this);
	}

	bool StrategyHedgeFixGrid::Update(const Price& rate)
	{
		// set last and current price
		m_prev_rate = m_rate;
		m_rate = rate;
		if(m_prev_rate.GetBuy() == FLT_MAX &&
			m_prev_rate.GetSell() == FLT_MAX)
			m_prev_rate = m_rate;


		// creating entry order
		if(CanEnterMarket())
		{
			EnterMarket();
		}		
		
		if(m_ct.IsEmpty())
			// failed/waiting to enter the market, should try again
			return true;

		if(CanCreateGrid())
		{
			// let another cycle run
			return CreateGrid();
		}

		UpdateGrid();
		ShowStatus();


		
		double trPL = m_ct.GetPL(m_ep.GetCurrency().GetSymbol(), m_rate);		// PL of entire transaction
		double trGPL = m_ct.GetGPL(m_ep.GetCurrency().GetSymbol(), m_rate); // Gross of entire transaction + commissions & interest
		double tgGPL = m_maxp * m_ep.GetAmount() * m_ep.GetCurrency().GetPipCost();	// target gross profit


		if(trPL <= -m_maxn * m_ep.GetAmount())	// transaction at stop PL
		{
			if(BlockTransaction())
			{
				m_blocked = true;
				return false;
			}
		}

		
		if(trPL >= m_maxp * m_ep.GetAmount())	// transaction in PL target
		{
			if(trGPL >= tgGPL)	// transaction in GPL target
			{
				if(CloseTransaction())
				{
					m_blocked = true;
					return false;
				}			
			}			
		}

		return true;
	}
	
	double StrategyHedgeFixGrid::GetPL() const
	{
		return m_ct.GetPL(m_ep.GetCurrency().GetSymbol(), m_rate);
	}


	double StrategyHedgeFixGrid::GetGPL() const
	{
		return m_ct.GetGPL(m_ep.GetCurrency().GetSymbol(), m_rate);
	}

	bool StrategyHedgeFixGrid::ReInit()
	{
		// restore internal status as initially

		/*	Strategy must be blocked to be reinitialized.
		 *	It must be either in profit or loss.
		 *	It must have reached it's negative or positive target.
		 */
		if(!m_blocked)
			throw misc::exception("Cannot re-initialize unblocked strategy.");


		m_ct = fx::Transaction();
		m_enter = fx::Price();
		m_rate = fx::Price();
		m_prev_rate = fx::Price();
		m_grid.clear();
		m_blocked = false;

		return true;
	}

	misc::string StrategyHedgeFixGrid::ToString() const
	{
		const fx::Currency& curr = m_ep.GetCurrency();
		const fx::Price& epp = curr.GetPrice();
		double open = (m_ep.IsBuy() == true ? epp.GetBuy() : epp.GetSell());
		const Transaction::Positions& positions = m_ct.GetPositions();

		misc::string msg;
		msg += "HFG: "; msg += curr.GetSymbol();
		msg += m_ep.IsBuy() == true ? " B" : " S";
		msg += misc::from_value(open, 5);
		msg += " A:"; msg += misc::from_value(m_ep.GetAmount(), 0);
		msg += " T:"; msg += misc::from_value(positions.size());
		size_t count = 0;
		for(size_t i = 0; i < positions.size(); ++i)
		{
			const Position& pos = positions[i];
			if(pos.IsOpen())
				++count;
		}
		msg += " O:"; msg += misc::from_value(count);
		msg += " C:"; msg += misc::from_value(positions.size() - count);
		msg += " PL:"; msg += misc::from_value(m_ct.GetPL(curr.GetSymbol(), m_rate), 2);
		msg += " GPL:"; msg += misc::from_value(m_ct.GetGPL(curr.GetSymbol(), m_rate), 2);
		msg += " BLK:"; msg += (m_blocked == true ? "true" : "false");
		msg += "\tdh:"; msg += misc::from_value(m_dh, 2);
		msg += " dg:"; msg += misc::from_value(m_dg, 2);
		msg += " ha:"; msg += misc::from_value(m_ha, 1);
		msg += " de:"; msg += misc::from_value(m_de, 2);
		msg += " mn:"; msg += misc::from_value(m_maxn, 2);
		msg += " mp:"; msg += misc::from_value(m_maxp, 2);


		return msg;
	}

	void StrategyHedgeFixGrid::Reset()
	{
		m_ep = fx::Position();	// OrderID = ""
		m_wait = false;			// do not wait for market to reach entry level
		m_dh = 0;
		m_dg = 0;
		m_ha = 0;
		m_de = 0;
		m_maxn = 0;
		m_maxp = 0;
		m_plugin = 0;
		m_ct = fx::Transaction();
		m_enter = fx::Price();		// FLT_MAX
		m_rate = fx::Price();		// FLT_MAX
		m_prev_rate = fx::Price();	// FLT_MAX
		m_grid.clear();
		m_blocked = false;
	}

	void StrategyHedgeFixGrid::Validate()
	{
		bool valid = true;
		if(m_dh <= 1 /*|| ceil(m_dh) != m_dh*/) // 164.2 deserialized to 164.1999
			valid = false;

		if(m_dg <= 1)
			valid = false;

		if(m_ha <= 0 || ceil(m_ha) != m_ha) // natural no
			valid = false;

		if(m_de <= 0)
			valid = false;

		if(m_maxn <= 0)
			valid = false;

		if(m_maxn < m_dh + m_dg) // ensure we use the grid
			valid = false;

		if(m_maxp <= 0)			// profit must > 0
			valid = false;

		if(m_plugin.IsNull())
			valid = false;

		if(!m_ct.IsEmpty())
			valid = false;

		if(!m_grid.empty())
			valid = false;

		if(m_blocked != false)
			valid = false;
		
		if(m_ha > m_ep.GetAmount())
			valid = false;

		if(!valid)
			throw misc::exception("Strategy is not valid.");
	}

	bool StrategyHedgeFixGrid::CanEnterMarket()
	{
		if(!m_ct.IsEmpty())
			return false;

		// should wait for market to reach certain level ?
		if(!m_wait)
			return true;

		
		// determine entry condition
		bool isBuy = m_ep.IsBuy();
		const fx::Currency& curr = m_ep.GetCurrency();
		const fx::Price& price = curr.GetPrice();

		double prevmarket = (isBuy == true ? m_prev_rate.GetBuy() : m_prev_rate.GetSell());
		double currmarket = (isBuy == true ? m_rate.GetBuy() : m_rate.GetSell());
		double entry = (isBuy == true ? price.GetBuy() : price.GetSell());

		bool allow = false;
		if(isBuy)
		{
			// price bounces from below to above the entry position.
			allow = (prevmarket <= entry && currmarket >= entry);
		}
		else
		{
			// price bounces from above to below the entry position.
			allow = (prevmarket >= entry && currmarket <= entry);
		}

		return allow;
	}

	bool StrategyHedgeFixGrid::EnterMarket()
	{
		// check orders
		if(!m_ct.IsEmpty())
			throw misc::exception("Orders added already.");
		
		// enter the market, open order
		misc::vector<fx::Position> orders;
		misc::string error;		
		if(!m_plugin->OpenMarketOrder(m_ep, orders, error))
			return false;

		if(orders.empty())
			return false;

		//TODO: are we totally filled ? (integrity check)
		
		// add orders to internal transaction
		for(size_t i = 0; i < orders.size(); ++i)
		{
			m_ct.Add(orders[i]);
		}

		// calculate the average of market entry
		double midprice = 0;
		for(size_t i = 0; i < orders.size(); ++i)
		{
			const fx::Position& order = orders[i];
			const fx::Price& price = order.GetCurrency().GetPrice();
			midprice += (m_ep.IsBuy() == true ? price.GetBuy() : price.GetSell());
		}
		midprice /= orders.size();

		// set the entry for later reference
		double buy = (m_ep.IsBuy() == true ? midprice : FLT_MAX);
		double sell = (m_ep.IsBuy() == true ? FLT_MAX : midprice);
		m_enter = fx::Price(buy, sell);

		return !m_ct.IsEmpty();
	}

	bool StrategyHedgeFixGrid::CanCreateGrid()
	{
		return m_grid.empty();
	}

	bool StrategyHedgeFixGrid::CreateGrid()
	{
		if(!m_grid.empty())
			throw misc::exception("Grid must be empty.");


		/* Create the grid from the entry price, not from what was given in 
		 * entry position.
		 */
		bool isBuy = m_ep.IsBuy();

		// market plugin updates only the real open price (2nd parameter is FLT_MAX)
		double eopen = (isBuy == true ? m_enter.GetBuy() : m_enter.GetSell());
		double pip2rate = 1 / m_ep.GetCurrency().GetRate2Pip();

		double h0p = (isBuy == true ? eopen - m_dh * pip2rate : eopen + m_dh * pip2rate);
		double hno = ceil(m_ep.GetAmount() / m_ha);   // number of hedges
		double intvl = std::min<double>(hno - 1, 1);  // number of intervals
		double d2h = m_dg / intvl;		// distance between 2 hedges in pips
		double d2hp = d2h * pip2rate;	// distance between 2 hedges as price

		double sumamt = 0;			// sum of total amount
		for(size_t i =0; i < (size_t)hno; ++i)
		{
			fx::Position	hpos;	// new hedge position
			fx::Currency	hcurr;	// currency value for the hedge
			fx::Price		hprice;	// price value for the hedge

			double openp(0);		// open price
			if(isBuy == true)
				openp = h0p - i * d2hp;
			else
				openp = h0p + i * d2hp;
			
			double gpbuy = (isBuy == true ? FLT_MAX : openp);
			double gpsell= (isBuy == true ? openp : FLT_MAX);


			/*
			        BUY                  BUY (openp, x)
			         x                    o
			         |                    |
			         |                    |
			         o                    x
			        SELL (x, openp)      SELL
			*/
			hprice = fx::Price(gpbuy, gpsell);
			
			hcurr = fx::Currency(
				m_ep.GetCurrency().GetSymbol(),
				hprice,
				m_ep.GetCurrency().GetMargin(),
				m_ep.GetCurrency().GetPipCost(),
				m_ep.GetCurrency().GetRate2Pip());


			// calculate amount
			double amount = m_ha;
			if(sumamt + amount > m_ep.GetAmount())
			{
				amount = m_ep.GetAmount() - sumamt;	// remained
				if(amount < 1)
					throw misc::exception("Outside valid range");
			}
			sumamt += amount;

			double commission = 0;
			double interest = 0;

			// set grid position
			hpos = fx::Position("", "", hcurr, !isBuy, amount, commission, interest);
			
			FixGridPositionStub::Ptr pstub = 
				new FixGridPositionStub(hpos, m_de, m_plugin, &m_ct);

			m_grid.push_back(pstub);						
		}

		return true;
	}

	bool StrategyHedgeFixGrid::UpdateGrid()
	{
		for(Grid::iterator beg = m_grid.begin(); beg != m_grid.end(); ++beg)
		{
			FixGridPositionStub::Ptr& pstub = *beg;
			pstub->Update(m_rate);
		}
		return true;
	}

	bool StrategyHedgeFixGrid::ShowStatus()
	{
		// Order positions by price descending.
		openprice_greater comp;
		misc::sort(m_ct.GetBegin(), m_ct.GetEnd(), comp);

		size_t buyOT(0), buyCT(0), buyOk(0), buyCk(0);
		size_t sellOT(0), sellCT(0), sellOk(0), sellCk(0);

		for(Transaction::PosIt itb = m_ct.GetBegin(); itb!= m_ct.GetEnd(); ++itb)
		{
			const fx::Position& pos = *itb;
			bool bBuy = pos.IsBuy();
			double kAmount = pos.GetAmount(); // k
			bool bOpen = pos.IsOpen();

			if(bOpen)
			{
				if(bBuy)
				{
					buyOT++; 
					buyOk += (size_t)kAmount; 
				}
				else
				{
					sellOT++;
					sellOk += (size_t)kAmount;
				}
			}
			else
			{
				if(bBuy)
				{
					buyCT++;
					buyCk += (size_t)kAmount;
				}
				else
				{
					sellCT++;
					sellCk += (size_t)kAmount;
				}
			}
		}

		const misc::string& symbol = m_ep.GetCurrency().GetSymbol();
		double dPL = m_ct.GetPL(symbol, m_rate);
		double dGPL = m_ct.GetGPL(symbol, m_rate);
		const fx::Price& eprice = m_ep.GetCurrency().GetPrice();


		misc::cout << "\n";
		misc::cout << "\n-------------------------------------------------------";
		misc::cout << "\n 1 Hedge Fix Grid";
		misc::cout << "\n-------------------------------------------------------";
		misc::cout << "\nENTRY   B: " << eprice.GetBuy() << " S: " << eprice.GetSell();
		misc::cout << "\nMARKET  B: " << m_rate.GetBuy() << " S: " << m_rate.GetSell();
		misc::cout << "\nTRADE  PL: " << dPL << " GPL: " << dGPL;
		misc::cout << "\nLONG    O: " << buyOT  << " pos (" << buyOk << "k)   C: " << buyCT << " pos (" << buyCk << "k)";
		misc::cout << "\nSHORT   O: " << sellOT  << " pos (" << sellOk << "k)   C: " << sellCT << " pos (" << sellCk << "k)";
		misc::cout << "\n";

		return true;
	}
	
	bool StrategyHedgeFixGrid::BlockTransaction()
	{
		double amount = 0;
		Transaction tro;
		for(Transaction::PosCIt beg = m_ct.GetBegin(); beg != m_ct.GetEnd(); ++beg)
		{
			if(beg->IsOpen())
			{
				tro.Add(*beg);
				if(beg->IsBuy())
					amount += beg->GetAmount();
				else
					amount -= beg->GetAmount();
			}
		}

		// hedging complete
		if(amount == 0)
			return true;

		// check if excess is correct
		if((m_ep.IsBuy() && amount < 0) ||
			(!m_ep.IsBuy() && amount > 0))
			throw misc::exception("Invalid amount for hedge");

		// hedge the excess
		bool buy = (amount < 0);

		double commission = 0;
		double interest = 0;
		fx::Position pos("", "", m_ep.GetCurrency(), buy, fabs(amount), commission, interest);

		misc::vector<fx::Position> otrades;
		misc::string error;
		if(m_plugin->OpenMarketOrder(pos, otrades, error))
		{
			for(size_t i = 0; i < otrades.size(); ++i)
				m_ct.Add(otrades[i]);
		}

		return !otrades.empty();
	}

	bool StrategyHedgeFixGrid::CloseTransaction()
	{
		bool ret = true;
		fx::Transaction::Positions& positions = 
			const_cast<fx::Transaction::Positions&>(m_ct.GetPositions());
		for(fx::Transaction::PosIt beg = positions.begin(); beg != positions.end(); /*..*/)
		{
			// Search for all open trades at market for initial order.
			fx::Position& pos = *beg;
			if(!pos.IsOpen())
			{
				++beg;
				continue;
			}

			misc::vector<fx::Position> ctrades;
			misc::string error;
			if(m_plugin->CloseMarketOrder(pos, ctrades, error))
			{
				fx::Transaction::PosIt tmp = positions.erase(beg);
				beg = tmp;
				for(size_t i=0; i < ctrades.size(); ++i)
					positions.push_back(ctrades[i]);
			}
			else
			{
				// get another chance to close failed order
				ret = false;
				++beg;
			}
		}

		return ret;
	}

	


} // namespace

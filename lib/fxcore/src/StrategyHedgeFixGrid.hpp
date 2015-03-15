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

#ifndef __StrategyHedgeFixGrid_hpp__
#define __StrategyHedgeFixGrid_hpp__


#include "StrategyBase.hpp"
#include "Transaction.hpp"
#include "MarketDummyPlugin.hpp"


namespace fx
{
	class Serializer;
	class Deserializer;
	class StrategyHedgeFixGrid;
	class Strategy2HedgeFixGrid;
	class StrategyFixGrid;

	//##########################################################################
	/*	This class takes care of one position in the grid.
	 *	It opens or closes the corresponding position as needed.	
	 */
	class FixGridPositionStub
	{
	public:
		typedef misc::autoptr<FixGridPositionStub> Ptr;
		friend class Serializer;
		friend class Deserializer;
		friend class StrategyHedgeFixGrid;
		friend class Strategy2HedgeFixGrid;
		friend class StrategyFixGrid;

	public:
		FixGridPositionStub();
		~FixGridPositionStub();
		FixGridPositionStub(const FixGridPositionStub& tc);
		FixGridPositionStub& operator=(const FixGridPositionStub& tc);

		FixGridPositionStub(
			const fx::Position& gp,			// fix grid's hedge position to be monitored
			double de,						// distance to exit
			MarketPlugin::Ptr plugin,		// market execution plugin
			fx::Transaction* ct				// parent transaction
			);

		bool Update(const Price& rate);
		bool IsActive() const;


	private:
		void Reset();
		void Validate();
		bool CanOpenOrder();
		bool OpenOrder();
		bool CanCloseOrder();
		bool CloseOrder();

	private:
		fx::Position		m_gp;				// grid position - position where to hedge
		double				m_de;				// distance to exit
		MarketPlugin::Ptr	m_plugin;			// market execution plugin
		fx::Transaction*	m_ct;				// parent transaction with all opened and closed positions at any time
		fx::Transaction		m_gt;				// all positions opened for this grid position (liquidity)
		fx::Price			m_rate;
	};

	//##########################################################################
	/*
	 *	We enter the market at its price (Buy or Sell Market Order), or wait
	 *	until it bounces over the entry level (optional).	 
	 *	Below or above the entry at the distance to the first hedge position starts the grid.
	 *	In the grid, all hedging positions are displaced at equal distance.
	 *	In the grid, a hedge position is added if the price reached its entry.
	 *	Each hedging position is closed in negative at the distance to exit.
	 *	If the price reacts negative and reaches again the hedge position
	 *	it will be opened again.
	 *
	 *	The draw down limit is established for entry position: 50k, -20pips = -1000 pips
	 *	and the strategy stops when all closed and open positions have in total 
	 *	this PL number.
	 *	
	 *	The profit limit is established for entry position: 30k, +10pips = +300 pips
	 *	and the strategy stop when all closed and open positions have in total
	 *	this PL number.
	 *	
	 *	        [profit]
	 *	            
	 *	            
	 *	            
	 *	         O-BUY-O   [entry]
	 *	           |
	 *	           |
	 *	           |
	 *	           |
	 *	           |
	 *	           |
	 *	       x-------x   [hedge's exit]
	 *	           |
	 *	        o-sell-o   [hedge]
	 */
	class StrategyHedgeFixGrid : public StrategyBase
	{
	public:
		typedef misc::autoptr<StrategyHedgeFixGrid> Ptr;
		friend class Serializer;
		friend class Deserializer;

	public:
		StrategyHedgeFixGrid();
		StrategyHedgeFixGrid(const StrategyHedgeFixGrid& tc);
		StrategyHedgeFixGrid& operator=(const StrategyHedgeFixGrid& tc);

		StrategyHedgeFixGrid(
			const fx::Position& ep,				// entry position - where to enter the market
			bool wait,							// wait until price bounces over the entry
			double dh,							// distance from entry to first hedge in pips
			double dg,							// distance of the grid in pips
			double ha,							// hedge amount for each position in the grid
			double de,							// distance to exit for each hedge in the grid
			double maxn,						// maxim negative - total draw down for entry position (100k, -20pips)
			double maxp,						// maxim positive - total profit for entry position (100k, +20pips)
			MarketPlugin::Ptr plugin			// market execution plugin
			);
				
		~StrategyHedgeFixGrid();

		// --- virtual table ---
		void AcceptVisitor(StrategyVisitor& visitor);
		bool Update(const Price& rate);
		double GetPL() const;
		double GetGPL() const;
		bool ReInit();
		// --- end of virtual ---

		misc::string ToString() const;		

	private:
		//! Reset entire content
		void Reset();
		void Validate();
				
		bool CanEnterMarket();
		bool EnterMarket();		
		bool CanCreateGrid();
		bool CreateGrid();
		bool UpdateGrid();
		bool ShowStatus();
		bool BlockTransaction();
		bool CloseTransaction();
		

	private:
		fx::Position		m_ep;	// entry position		
		bool				m_wait;	// open entry at market when price bounces over entry
		double				m_dh;	// distance from entry to first hedge in pips
		double				m_dg;	// distance of the grid in pips
		double				m_ha;	// hedge amount for each position in the grid
		double				m_de;	// distance to exit for each hedge in the grid
		double				m_maxn;	// maxim negative - total pips as max allowed to be consumed
		double				m_maxp;	// maxim positive - close in profit entire strategy
		MarketPlugin::Ptr	m_plugin; // market execution plugin

		fx::Transaction		m_ct;		// current transaction
		fx::Price			m_enter;	// average price of all trades (liquidity) when entered the market
		fx::Price			m_rate;		// latest updated price
		fx::Price			m_prev_rate;// previous price value
		typedef misc::vector<FixGridPositionStub::Ptr> Grid;
		Grid				m_grid;
		bool				m_blocked;	// closed in profit, blocked at loss
	};

	
}

#endif // __StrategyHedgeFixGrid_hpp__


/*
  Copyright (C) 2015 Mihai Vasilian

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



#ifndef __Strategy2FixGrid_hpp__
#define __Strategy2FixGrid_hpp__


#include "StrategyBase.hpp"
#include "FixGridPositionStub.hpp"

namespace fx
{
	/*
	 *	The strategy uses 2 grids in both directions with an interval between them.
	 *	The middle of the interval is considered the virtual entry.
	 *	The 'ep' size is the size of one grid, and its price is the virtual entry.
	 *	When waiting for the market the strategy activates when the price bounces over
	 *	the virtual entry. Otherwise the strategy activates immediately.
	 *	
	 *	First position for each grid is displaced at 1/2 interval from entry.
	 *	In the grid positions are calculated relative to the grid size.
	 *	Each position is opened when price reaches its location, and closed 
	 *	in negative at the distance to exit.
	 *	
	 *	
	 *	The draw down limit is established for one grid size: 50k, -20pips = -1000 pips
	 *	and the strategy stops when all closed and open positions have in total 
	 *	this PL number.
	 *	
	 *	The profit limit is established for one grid size: 30k, +10pips = +300 pips
	 *	and the strategy stops when all closed and open positions have in total
	 *	this PL number.
	 *	
	 *	
	 *	
	 *	
	 *	       x
	 *	       x   [grid]
	 *	       x
	 *	       |
	 *	       |
	 *	       |
	 *	   o-entry-o [virtual]
	 *	       |
	 *	       |
	 *	       |
	 *	       x
	 *	       x   [grid]
	 *	       x
	 */
	class Strategy2FixGrid : public StrategyBase
	{
	public:
		typedef misc::autoptr<Strategy2FixGrid> Ptr;
		friend class Serializer;
		friend class Deserializer;

		Strategy2FixGrid();
		~Strategy2FixGrid();
		Strategy2FixGrid(const Strategy2FixGrid& tc);
		Strategy2FixGrid& operator=(const Strategy2FixGrid& tc);

		Strategy2FixGrid(
			const fx::Position& ep,				// entry position - size for one grid, price is virtual entry
			bool wait,							// wait until price bounces over the virtual entry
			double dbg,							// distance between the two grids in pips
			double dg,							// distance of the grid in pips
			double pa,							// amount for each position in the grid
			double de,							// distance to exit for each position in the grid
			double maxn,						// maxim negative - total draw down for entry position (100k, -20pips)
			double maxp,						// maxim positive - total profit for entry position (100k, +20pips)
			MarketPlugin::Ptr plugin			// market execution plugin
			);

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
		bool CanCreateGrid();
		bool CreateGrid();
		bool UpdateGrid();
		bool ShowStatus();
		bool BlockTransaction();
		bool CloseTransaction();


	protected:
		fx::Position		m_ep;	// virtual entry price, size for one grid		
		bool				m_wait;	// wait for price to bounce over the virtual entry
		double				m_dbg;	// distance between the two grids in pips
		double				m_dg;	// distance of the grid in pips
		double				m_pa;	// amount for each position in the grid
		double				m_de;	// distance to exit for each position in the grid
		double				m_maxn;	// maxim negative - total pips as max allowed to be consumed
		double				m_maxp;	// maxim positive - close in profit entire strategy
		MarketPlugin::Ptr	m_plugin; // market execution plugin

		fx::Transaction		m_ct;		// current transaction
		fx::Price			m_rate;		// latest updated price
		fx::Price			m_prev_rate;// previous price value
		typedef misc::vector<FixGridPositionStub::Ptr> Grid;
		Grid				m_grid;
		bool				m_blocked;	// closed in profit, blocked at loss

	};

} // namespace


#endif // __Strategy2FixGrid_hpp__
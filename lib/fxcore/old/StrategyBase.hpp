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


#ifndef __StrategyBase_hpp__
#define __StrategyBase_hpp__

// C
// C++
// local
#include "autoptr.hpp"


namespace fx
{
	class StrategyBase;
	class StrategyHedgeFixGrid;
	class Strategy2HedgeFixGrid;
	class StrategyFixGrid;
	class Strategy2FixGrid;
	class Price;

	class StrategyVisitor
	{
	public:
		virtual void Visit(StrategyBase& tv) = 0;
		virtual void Visit(StrategyHedgeFixGrid& tv) = 0;
		virtual void Visit(Strategy2HedgeFixGrid& tv) = 0;
		virtual void Visit(StrategyFixGrid& tv) = 0;
		virtual void Visit(Strategy2FixGrid& tv) = 0;
	};
	
	class StrategyBase
	{
	public:
		typedef misc::autoptr<StrategyBase> Ptr;
		StrategyBase(){}
		virtual ~StrategyBase(){}
		
		virtual void AcceptVisitor(StrategyVisitor& visitor) = 0;
		/*!	Updates the strategy with new market price.
		 *!	On success it returns true. If an error happened or if the strategy has
		 *!	closed its execution the return value is false.
		 */
		virtual bool Update(const fx::Price& price) = 0;
		
		/*! Total PL scored by strategy at call time, with last
		 *! updated market price.
		 */
		virtual double GetPL() const = 0;

		/*! Total GPL scored by strategy at call time, with last
		 *! updated market price. 
		 */
		virtual double GetGPL() const = 0;

		/*!	ReInit must get the strategy ready for trading again.
		 *! All internal members must be set as initially.
		 */
		virtual bool ReInit() = 0;
	};

} // namespace

#endif // __StrategyBase_hpp__


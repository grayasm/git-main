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


#ifndef __CandleBase_hpp__
#define __CandleBase_hpp__

#include "time.hpp"
#include "Price.hpp"


namespace fx
{
	class CandleBase;
	class Candle;
	class HACandle;
	class RenkoCandle;

	//! Visitor class
	class CandleVisitor
	{
	public:
		virtual void Visit(CandleBase& tv) = 0;
		virtual void Visit(Candle& tv) = 0;
		virtual void Visit(HACandle& tv) = 0;
		virtual void Visit(RenkoCandle& tv) = 0;
	};


	//! Candle base class.
	class CandleBase
	{
	public:
		CandleBase() { }
		virtual ~CandleBase() { }
		CandleBase(const CandleBase&) { }
		CandleBase& operator=(const CandleBase&) { }

		//! Get functions for candle parameters
		virtual const fx::Price& GetHigh() const = 0;
		virtual const fx::Price& GetLow() const = 0;
		virtual const fx::Price& GetOpen() const = 0;
		virtual const fx::Price& GetClose() const = 0;
		virtual const misc::time& GetTimeBegin() const = 0;
		virtual const misc::time& GetTimeEnd() const = 0;

		//! Accept visitor
		virtual void AcceptVisitor(CandleVisitor& visitor) = 0;
	};
} // namespace

#endif // __CandleBase_hpp__

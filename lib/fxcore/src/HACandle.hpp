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


#ifndef __HACandle_hpp__
#define __HACandle_hpp__


#include "autoptr.hpp"
#include "CandleBase.hpp"

namespace fx
{
	//! Heikin Ashi Candle class.
	class HACandle : public CandleBase
	{
		void Init();
	public:
	// types
		typedef misc::autoptr<HACandle> Ptr;
	// members
		HACandle();
		HACandle(const fx::Price& high, const fx::Price& low,
				const fx::Price& open, const fx::Price& close,
				const misc::time& begin, const misc::time& end);
		HACandle(const HACandle& tc);
		HACandle& operator=(const HACandle& tc);

		//! --- vtable begin ---
		~HACandle();
		//! Get functions for candle parameters
		const fx::Price& GetHigh() const;
		const fx::Price& GetLow() const;
		const fx::Price& GetOpen() const;
		const fx::Price& GetClose() const;
		const misc::time& GetTimeBegin() const;
		const misc::time& GetTimeEnd() const;
		//! Accept visitor
		void AcceptVisitor(CandleVisitor& visitor);
		//! --- vtable end ---

	private:
		fx::Price m_high;
		fx::Price m_low;
		fx::Price m_open;
		fx::Price m_close;
		misc::time m_begin;
		misc::time m_end;
	};
} // namespace

#endif // __HACandle_hpp__

/*
	Copyright (C) 2018 Mihai Vasilian

	This program is free software; you can redistribute it and/or
	modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation; either version 2
	of the License, or (at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program; if not, write to the Free Software Foundation, Inc.
	51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

	contact: grayasm@gmail.com

	IND will serve as the base class for all indicators.
	It defines all methods necessary to build one without knowing anything
	more about it.
	Using this abstraction it is possible to build a big number of different
	indicators (passed around as a vector) using one set of history data.
*/

#ifndef __IND_hpp__
#define __IND_hpp__

#include "string.hpp"
#include "time.hpp"
#include "Offer.hpp"


namespace fx
{
	class IND
	{
	public:
		typedef time_t			Timeframe;

		IND();
		IND(const IND&);
		IND& operator=(const IND&);
		virtual ~IND();
		
		// --- virtual table ---		
		virtual const misc::string& GetInstrument() const = 0;
		virtual int GetPeriod() const = 0;
		virtual Timeframe GetTimeframe() const = 0;			
		virtual bool IsValid() const = 0;
		virtual void Update(const fx::Offer& offer) = 0;
		virtual const misc::time& GetRefTime() const = 0; // begin of current candle
		// --- end of virtual table ---
	};
} // namespace

#endif // __IND_hpp__

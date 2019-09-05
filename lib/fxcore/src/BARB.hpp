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
	along with this program; if not, write to the Free Software Foundation,
	Inc. 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

	contact: grayasm@gmail.com

	BARB will serve as the base class for all candle data structures.
	Each candle has a current bar and a period for which it stores the bars.
	IsNew will tell if the offer will paint a new bar or not.
*/


#ifndef __BARB_hpp__
#define __BARB_hpp__

#include <list>
#include "autoptr.hpp"
#include "IND.hpp"
#include "OHLCPrice.hpp"


namespace fx
{
	class BARB : public fx::IND
	{
	public:
		typedef stl::autoptr<BARB>			Ptr;
		typedef std::list<fx::OHLCPrice>	OHLCPriceList;

		BARB();
		BARB(const BARB&);
		BARB& operator=(const BARB&);
		virtual ~BARB();

		// --- additional virtual table ---
		virtual bool IsNew(const fx::Offer& offer) const = 0;
		virtual const fx::OHLCPrice& GetOHLC() const = 0;
		virtual const OHLCPriceList& GetOHLCList() const = 0;
		// --- end of additional virtual table ---
	};
} // namespace


#endif // __BARB_hpp__

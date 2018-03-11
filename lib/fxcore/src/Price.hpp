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


#ifndef __Price_hpp__
#define __Price_hpp__



// C
// C++
// local
#include "autoptr.hpp"


namespace fx
{
	/*	Class manages a buy and sell quote for a currency.
		Although a buy and a sell quote is an exchange rate,
		here it is seen as a price (buying and selling in the market).
	*/
	class Price
	{
	public:
		typedef misc::autoptr<Price> Ptr;

		Price();
		Price(double buy, double sell);
		~Price();
		Price(const Price& tc);
		Price& operator=(const Price& tc);

		double GetBuy() const;
		double GetSell() const;

	private:
		void Init();

	private:
		double	m_buy;
		double	m_sell;
	};
}


#endif // __Price_hpp__

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



#include "Price.hpp"
#include <float.h>



namespace fx
{
	Price::Price()
	{
		Init();
	}

	Price::Price(double buy, double sell)
	{
		Init();
		m_buy = buy;
		m_sell = sell;
	}

	Price::~Price()
	{

	}

	Price::Price(const Price& tc)
	{
		Init();
		*this = tc;
	}

	Price& Price::operator=(const Price& tc)
	{
		if(this != &tc)
		{
			m_buy = tc.m_buy;
			m_sell = tc.m_sell;
		}
		return *this;
	}

	double Price::GetBuy() const
	{
		return m_buy;
	}

	double Price::GetSell() const
	{
		return m_sell;
	}

	void Price::Init()
	{
		m_buy = FLT_MAX;
		m_sell = FLT_MAX;
	}

} // namespace fx


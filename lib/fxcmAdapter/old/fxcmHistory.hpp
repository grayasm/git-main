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


#ifndef __fxcmHistory_hpp__
#define __fxcmHistory_hpp__

// fxcm
// c/c++
// local
#include "date.hpp"
#include "vector.hpp"
#include "Price.hpp"


namespace fxcm
{
	class HistoryPrice
	{
		bool		m_isBar;
		misc::DATE	m_date;
		fx::Price	m_currPrice;
		fx::Price	m_openPrice;
		fx::Price	m_closePrice;
		fx::Price	m_highPrice;
		fx::Price	m_lowPrice;
		int			m_volume;

		void Init();

	public:
		HistoryPrice();
		~HistoryPrice();
		HistoryPrice(const HistoryPrice& tc);
		HistoryPrice& operator=(const HistoryPrice& tc);

		void EnableBar(bool isBar);
		bool IsBar() const;

		void SetDate(const misc::DATE& date);
		const misc::DATE& GetDate() const;

		void SetCurrPrice(const fx::Price& currPrice);
		const fx::Price& GetCurrPrice() const;

		void SetOpenPrice(const fx::Price& openPrice);
		const fx::Price& GetOpenPrice() const;

		void SetClosePrice(const fx::Price& closePrice);
		const fx::Price& GetClosePrice() const;

		void SetHighPrice(const fx::Price& highPrice);
		const fx::Price& GetHighPrice() const;

		void SetLowPrice(const fx::Price& lowPrice);
		const fx::Price& GetLowPrice() const;

		void SetVolume(int volume);
		int GetVolume() const;
	};
	
	typedef misc::vector<HistoryPrice>	HistPriceData;
	
} // namespace


#endif // __fxcmHistory_hpp__
/*
	Copyright (C) 2017 Mihai Vasilian

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
*/

#ifndef __Offer_hpp__
#define __Offer_hpp__

#include "string.hpp"
#include "time.hpp"

namespace fxcm
{
	class Offer
	{
	public:
		Offer();

		Offer(	const misc::string& id,
				const misc::string& instrument,
				int precision,
				double pipsize,
				const misc::time& time,
				double bid,
				double ask);
		Offer(const Offer& tc);
		Offer& operator=(const Offer& tc);
		~Offer();

		const misc::string& GetId() const;
		void SetId(const misc::string& id);

		const misc::string& GetInstrument() const;
		void SetInstrument(const misc::string& instrument);

		double GetPrecision() const;
		void SetPrecision(double precision);

		const misc::time& GetTime() const;
		void SetTime(const misc::time& time);

		double GetPipSize() const;
		void SetPipSize(double pipsize);

		double GetBid() const;
		void SetBid(double bid);

		double GetAsk() const;
		void SetAsk(double ask);

	private:
		void Init();

	private:
		misc::string		m_id;
		misc::string		m_instrument;
		int					m_precision;
		misc::time			m_time;
		double				m_pipsize;
		double				m_bid;
		double				m_ask;
	};
} // namespace

#endif // __Offer_hpp__

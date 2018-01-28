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


#include "Offer.hpp"


namespace fxcm
{
	Offer::Offer()
	{
		Init();
	}

	Offer::Offer(
		const misc::string& id,
		const misc::string& instrument,
		int precision,
		double pipsize,
		const misc::time& time,
		double bid,
		double ask)
	{
		m_id = id;
		m_instrument = instrument;
		m_precision = precision;
		m_pipsize = pipsize;
		m_time = time;
		m_bid = bid;
		m_ask = ask;
	}

	Offer::Offer(const Offer& tc)
	{
		*this = tc;
	}

	Offer& Offer::operator=(const Offer& tc)
	{
		if (this != &tc)
		{
			m_id = tc.m_id;
			m_instrument = tc.m_instrument;
			m_precision = tc.m_precision;
			m_pipsize = tc.m_pipsize;
			m_time = tc.m_time;
			m_bid = tc.m_bid;
			m_ask = tc.m_ask;
		}
		return *this;
	}

	Offer::~Offer()
	{
	}

	const misc::string& Offer::GetId() const
	{
		return m_id;
	}

	void Offer::SetId(const misc::string& id)
	{
		m_id = id;
	}

	const misc::string& Offer::GetInstrument() const
	{
		return m_instrument;
	}

	void Offer::SetInstrument(const misc::string& instrument)
	{
		m_instrument = instrument;
	}

	double Offer::GetPrecision() const
	{
		return m_precision;
	}

	void Offer::SetPrecision(double precision)
	{
		m_precision = precision;
	}

	const misc::time& Offer::GetTime() const
	{
		return m_time;
	}

	void Offer::SetTime(const misc::time& time)
	{
		m_time = time;
	}

	double Offer::GetPipSize() const
	{
		return m_pipsize;
	}

	void Offer::SetPipSize(double pipsize)
	{
		m_pipsize = pipsize;
	}

	double Offer::GetBid() const
	{
		return m_bid;
	}

	void Offer::SetBid(double bid)
	{
		m_bid = bid;
	}

	double Offer::GetAsk() const
	{
		return m_ask;
	}

	void Offer::SetAsk(double ask)
	{
		m_ask = ask;
	}

	void Offer::Init()
	{
		m_id = "";
		m_instrument = "";
		m_precision = 0;
		// m_time;  - default
		m_pipsize = 0;
		m_bid = 0;
		m_ask = 0;
	}
} // namespace

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


namespace fx
{
	Offer::Offer()
	{
		Init();
	}

	Offer::Offer(
		const stl::string& id,
		const stl::string& instrument,
		int precision,
		double pointSize,
		const sys::time& time,
		double bid,
		double ask,
		double vol,
		bool isTradingOpen)
	{
		m_offerID = id;
		m_instrument = instrument;
		m_precision = precision;
		m_pointSize = pointSize;
		m_time = time;
		m_bid = bid;
		m_ask = ask;
		m_volume = vol;
		m_isTradingOpen = isTradingOpen;
	}

	Offer::Offer(const Offer& tc)
	{
		*this = tc;
	}

	Offer& Offer::operator=(const Offer& tc)
	{
		if (this != &tc)
		{
			m_offerID = tc.m_offerID;
			m_instrument = tc.m_instrument;
			m_precision = tc.m_precision;
			m_pointSize = tc.m_pointSize;
			m_time = tc.m_time;
			m_bid = tc.m_bid;
			m_ask = tc.m_ask;
			m_volume = tc.m_volume;
			m_isTradingOpen = tc.m_isTradingOpen;
		}
		return *this;
	}

	Offer::~Offer()
	{
	}

	const stl::string& Offer::GetOfferID() const
	{
		return m_offerID;
	}

	void Offer::SetOfferID(const stl::string& id)
	{
		m_offerID = id;
	}

	const stl::string& Offer::GetInstrument() const
	{
		return m_instrument;
	}

	void Offer::SetInstrument(const stl::string& instrument)
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

	const sys::time& Offer::GetTime() const
	{
		return m_time;
	}

	void Offer::SetTime(const sys::time& time)
	{
		m_time = time;
	}

	double Offer::GetPointSize() const
	{
		return m_pointSize;
	}

	void Offer::SetPointSize(double pipsize)
	{
		m_pointSize = pipsize;
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

	double Offer::GetVolume() const
	{
		return m_volume;
	}

	void Offer::SetVolume(double vol)
	{
		m_volume = vol;
	}

	bool Offer::GetIsTradingOpen() const
	{
		return m_isTradingOpen;
	}

	void Offer::SetIsTradingOpen(bool isOpen)
	{
		m_isTradingOpen = isOpen;
	}

	void Offer::Init()
	{
		m_offerID = "";
		m_instrument = "";
		m_precision = 0;
		// m_time;  - default
		m_pointSize = 0;
		m_bid = 0;
		m_ask = 0;
		m_volume = 0;
		m_isTradingOpen = false;
	}
} // namespace

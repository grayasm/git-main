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

namespace fx
{
    class Offer
    {
    public:
        Offer();

        Offer(  const stl::string& offerID,
                const stl::string& instrument,
                int precision,
                double pointSize,
                const sys::time& time,
                double bid,
                double ask,
                double vol,
                bool isTradingOpen);

        Offer(const Offer& tc);
        Offer& operator=(const Offer& tc);
        ~Offer();

        const stl::string& GetOfferID() const;
        void SetOfferID(const stl::string& id);

        const stl::string& GetInstrument() const;
        void SetInstrument(const stl::string& instrument);

        double GetPrecision() const;
        void SetPrecision(double precision);

        const sys::time& GetTime() const;
        void SetTime(const sys::time& time);

        double GetPointSize() const;
        void SetPointSize(double pipsize);

        double GetBid() const;
        void SetBid(double bid);

        double GetAsk() const;
        void SetAsk(double ask);

        double GetVolume() const;
        void SetVolume(double vol);

        bool GetIsTradingOpen() const;
        void SetIsTradingOpen(bool isOpen);

    private:
        void Init();

    private:
        stl::string         m_offerID;
        stl::string         m_instrument;
        int                 m_precision;
        sys::time           m_time;
        double              m_pointSize;
        double              m_bid;        // sell at bid
        double              m_ask;        // buy at ask
        double              m_volume;
        bool                m_isTradingOpen;
    };
} // namespace

#endif // __Offer_hpp__

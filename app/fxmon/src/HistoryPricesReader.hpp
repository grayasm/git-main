/*
    Copyright (C) 2018 Mihai Vasilian

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

#ifndef __HistoryPricesReader_hpp__
#define __HistoryPricesReader_hpp__

#include "vector.hpp"
#include "string.hpp"
#include "Offer.hpp"

class HistoryPricesReader
{
public:
    HistoryPricesReader(const stl::string& instrument);
    ~HistoryPricesReader();
    HistoryPricesReader(const HistoryPricesReader&) = delete;
    HistoryPricesReader& operator=(const HistoryPricesReader&) = delete;

    // return all recorded offers in receiving order; false if at the end;
    bool GetOffer(fx::Offer& offer);


private:
    void ParseFile(const stl::string& filePath,
        stl::vector<fx::Offer>& result);
    void Interpolate(const fx::Offer& beg, const fx::Offer& end,
        stl::vector<fx::Offer>& result);

private:
    stl::string                 m_instrument;
    stl::vector<stl::string>    m_offerFileVec;
    int                         m_ofvPos;
    stl::vector<fx::Offer>      m_offersVec;
    int                         m_ovPos;
};

#endif // __HistoryPricesReader_hpp__

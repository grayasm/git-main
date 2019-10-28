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


#ifndef __Currency_hpp__
#define __Currency_hpp__


// C
// C++
// local
#include "autoptr.hpp"
#include "string.hpp"
#include "Price.hpp"


namespace fx
{
    class Currency
    {
        void Init();
    public:
        typedef stl::autoptr<Currency> Ptr;

        Currency();
        Currency(
            const stl::string& symbol,
            const Price& price,
            double margin,
            double pipCost,
            double rate2pip);
        ~Currency();
        Currency(const Currency& tc);
        Currency& operator=(const Currency& tc);

        const stl::string& GetSymbol() const;
        const Price& GetPrice() const;        
        double GetMargin() const;
        double GetPipCost() const;
        double GetRate2Pip() const;

    private:
        stl::string     m_symbol;       // "EUR/USD"
        Price           m_price;        // 1.36 / 1.35975 (spread 2.5)
        double          m_margin;       // 5
        double          m_pipCost;      // 0.07
        double          m_rate2pip;     // 10000
    };
}

#endif // __Currency_hpp__


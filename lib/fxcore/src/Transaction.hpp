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

#ifndef __Transaction_hpp__
#define __Transaction_hpp__

// C
// C++
// local
#include "vector.hpp"
#include "string.hpp"
#include "Position.hpp"



namespace fx
{
    /*  More positions managed together.
        They can be in the market (in execution) or closed already.
        They can be in more then one currency as the class make explicit
        for which symbol it will calculate.
    */
    class Transaction
    {                
    public:
        //  types
        typedef stl::vector<Position>        Positions;
        typedef Positions::iterator         PosIt;
        typedef Positions::const_iterator   PosCIt;
        typedef stl::vector<stl::string>    Symbols;
        typedef Symbols::iterator            SyIt;
        typedef Symbols::const_iterator        SyCIt;

    private:
        Positions    m_positions;

    public:
        Transaction();
        ~Transaction();
        Transaction(const Transaction& tc);    
        Transaction& operator=(const Transaction& tc);

        const Positions& GetPositions() const;

        PosIt GetBegin();

        PosIt GetEnd();

        PosCIt GetBegin() const;

        PosCIt GetEnd() const;
        
        void Add(const Position& position);
            
        //! True if there is no position.
        bool IsEmpty() const;

        //! Returns the number of positions.
        size_t Size() const;

        //!    Returns all the currency pairs as ["EUR/GBP","EUR/JPY",...] etc.
        Symbols GetSymbols() const;

        //! Returns the total margin allocated by all opened positions of symbol.
        //! Closed positions will not be considered.
        double GetMMR(const stl::string& symbol) const;

        //! Close all opened positions of symbol at give quote.
        void Close(const stl::string& symbol, const Price& rate, time_t tclose);

        //! Return the total profit for all positions of symbol at the give quote.
        //! Closed positions of symbol will be calculated at their closing price.
        //! Commission and interest for each order is included.
        double GetGPL(const stl::string& symbol, const Price& rate) const;

        //! Return the total pips of all positions of symbol at the give quote.
        //! Closed positions of symbol will be calculated at their closing price.
        //! The pips are not for 1 unit, but for total amount of each position.
        double GetPL(const stl::string& symbol, const Price& rate) const;

        //! Calculate the price where all positions of symbol will score the
        //! given number of pips.
        Price EstimateRate(const stl::string& symbol, double pips) const;
    };

}  // namespace fx


#endif // __Transaction_hpp__

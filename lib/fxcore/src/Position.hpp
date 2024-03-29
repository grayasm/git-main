/*
Copyright (C) 2014 Mihai Vasilian
*/


#ifndef __Position_hpp__
#define __Position_hpp__

// C
// C++
// local
#include "autoptr.hpp"
#include "Currency.hpp"


namespace fx
{

    //! Position closed or in the market.
    class Position
    {
    public:
        typedef stl::autoptr<Position>    Ptr;

        Position();

        Position(const stl::string& orderID,
            const stl::string& tradeID,
            const Currency& currency,
            bool buy,
            double amount,
            double commission,
            double interest,
            time_t topen);

        ~Position();
        Position(const Position& tc);
        Position& operator=(const Position& tc);

        //! Returns the market order for this position.
        const stl::string& GetOrderID() const;

        //! Returns the market open trade id. Empty if entry order.
        const stl::string& GetTradeID() const;

        //! Currency at the time this position entered the market.
        const Currency& GetCurrency() const;

        //! False is position is a SELL (Short).
        bool IsBuy() const;

        //! Returns the total number of lots (K).
        double GetAmount() const;            

        //! False is position was closed.
        bool IsOpen() const;    

        //! Request to close this position at the given price.
        void Close(const Price& close, time_t tclose);
        
        //! Total margin allocated for this position.
        double GetMMR() const;

        //! Returns the pips scored by this position at the given price.        
        //! Position must not be closed.
        //! Pips are for 1 unit. To get the total number, multiply with the amount.
        double GetPL(const Price& rate) const;

        //! Returns the total profit scored by this position at the given price.
        //! Position must not be closed.
        //! Commission and interest are not included.
        double GetGPL(const Price& rate) const;

        //! Returns the pips scored by this position at closing time.
        //! Position must be closed.
        //! Pips are for 1 unit. To get the total number, multiply with the amount.
        double GetPL() const;

        //! Returns the total profit scored by this position at closing time.
        //! Position must be closed.
        //! Commission and interest are not included in the result.
        double GetGPL() const;

        //! Returns the closing price.
        //! Positions must be closed.
        const Price& GetClose() const;

        //! Set the commission for entire amount of this position.
        void SetCommission(double commission);
        
        //! Get the broker commission.
        double GetCommission() const;

        //! Set the interest for period while entire amount was opened in the market.
        void SetInterest(double interest);
        
        //! Get the interest.
        double GetInterest() const;

        //! Get the time at open
        time_t GetOpenTime() const;

        //! Get the time at close
        //! Calculate the duration as time_t seconds = tclose - topen;
        time_t GetCloseTime() const;
        
        //! Returns the market price where this position would have the
        //! given number of pips.
        Price GetQuotes(double pips) const;

        //! Returns a string with internal data for debugging
        stl::string ToString() const;

    private:
        void Init();

    private:
        stl::string     m_orderID;      // "222140555" order ID
        stl::string     m_tradeID;      // "105902921" trade ID
        bool            m_isOpen;       // false for closed position
        Currency        m_currency;     // currency at the open price
        bool            m_buy;          // false for sell position
        double          m_amount;       // lot amount in K    
        Price           m_close;        // market price where position was closed
        double          m_commission;   // commission for entire amount opened/closed
        double          m_interest;     // interest (need confirmation)
        time_t          m_topen;        // time_t at open
        time_t          m_tclose;       // time_t at close
    };


    //##########################################################################
    struct openprice_greater : stl::binary_function <Position,Position,bool>
    {
        bool operator()(const Position& x, const Position& y) const;
    };

    //##########################################################################


}  // namespace fx


#endif // __Position_hpp__
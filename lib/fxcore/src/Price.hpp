/*
Copyright (C) 2014 Mihai Vasilian
*/


#ifndef __Price_hpp__
#define __Price_hpp__



// C
// C++
// local
#include "autoptr.hpp"


namespace fx
{
    /*  Class manages a buy and sell quote for a currency.
        Although a buy and a sell quote is an exchange rate,
        here it is seen as a price (buying and selling in the market).
    */
    class Price
    {
    public:
        typedef stl::autoptr<Price> Ptr;

        Price();
        Price(double buy, double sell);
        ~Price();
        Price(const Price& tc);
        Price& operator=(const Price& tc);

        double GetBuy() const;
        double GetSell() const;

    private:
        void Init();

    private:
        double    m_buy;
        double    m_sell;
    };
}


#endif // __Price_hpp__

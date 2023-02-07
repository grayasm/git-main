/*
Copyright (C) 2014 Mihai Vasilian
*/



#include "Price.hpp"
#include <float.h>



namespace fx
{
    Price::Price()
    {
        Init();
    }

    Price::Price(double buy, double sell)
    {
        Init();
        m_buy = buy;
        m_sell = sell;
    }

    Price::~Price()
    {

    }

    Price::Price(const Price& tc)
    {
        Init();
        *this = tc;
    }

    Price& Price::operator=(const Price& tc)
    {
        if(this != &tc)
        {
            m_buy = tc.m_buy;
            m_sell = tc.m_sell;
        }
        return *this;
    }

    double Price::GetBuy() const
    {
        return m_buy;
    }

    double Price::GetSell() const
    {
        return m_sell;
    }

    void Price::Init()
    {
        m_buy = FLT_MAX;
        m_sell = FLT_MAX;
    }

} // namespace fx


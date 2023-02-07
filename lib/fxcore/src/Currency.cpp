/*
Copyright (C) 2014 Mihai Vasilian
*/

#include "Currency.hpp"
#include <float.h>


namespace fx
{

    void Currency::Init()
    {
        m_symbol = U("");
        // m_price;
        m_margin = 0;
        m_pipCost = 0;
        m_rate2pip = 0;
    }

    Currency::Currency()
    {
        Init();
    }

    Currency::Currency(
        const stl::string& symbol,
        const Price& price,
        double margin,
        double pipCost,
        double rate2pip)
    {
        Init();
                
        m_symbol = symbol;
        m_price = price;
        m_margin = margin;
        m_pipCost = pipCost;
        m_rate2pip = rate2pip;
    }

    Currency::~Currency()
    {

    }

    Currency::Currency(const Currency& tc)
    {
        Init();
        *this = tc;
    }

    Currency& Currency::operator=(const Currency& tc)
    {
        if(this != &tc)
        {
            m_symbol = tc.m_symbol;
            m_price = tc.m_price;
            m_margin = tc.m_margin;
            m_pipCost = tc.m_pipCost;
            m_rate2pip = tc.m_rate2pip;
        }
        return *this;
    }

    const stl::string& Currency::GetSymbol() const
    {
        return m_symbol;
    }

    const Price& Currency::GetPrice() const
    {
        return m_price;
    }    

    double Currency::GetMargin() const
    {
        return m_margin;
    }

    double Currency::GetPipCost() const
    {
        return m_pipCost;
    }

    double Currency::GetRate2Pip() const
    {
        return m_rate2pip;
    }

} // namespace fx


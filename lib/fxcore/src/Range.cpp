/*
Copyright (C) 2018 Mihai Vasilian
*/


#include "Range.hpp"
#include <float.h>

namespace fx
{
    Range::Range()
    {
        // m_min, m_max - default ctor
    }

    Range::Range(const fx::Price& min, const fx::Price& max)
    {
        m_min = min;
        m_max = max;
    }

    Range::Range(const Range& tc)
    {
        *this = tc;
    }

    Range& Range::operator=(const Range& tc)
    {
        if (this != &tc)
        {
            m_min = tc.m_min;
            m_max = tc.m_max;
        }
        return *this;
    }

    const fx::Price& Range::GetMin() const
    {
        return m_min;
    }

    void Range::SetMin(const fx::Price& min)
    {
        m_min = min;
    }

    const fx::Price& Range::GetMax() const
    {
        return m_max;
    }

    void Range::SetMax(const fx::Price& max)
    {
        m_max = max;
    }

    bool Range::IsMinValid() const
    {
        return (m_min.GetBuy() != FLT_MAX && m_min.GetSell() != FLT_MAX);
    }

    bool Range::IsMaxValid() const
    {
        return (m_max.GetBuy() != FLT_MAX && m_max.GetSell() != FLT_MAX);
    }
} // namespace


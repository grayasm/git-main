/*
Copyright (C) 2018 Mihai Vasilian
*/

#ifndef __Range_hpp__
#define __Range_hpp__

#include "Price.hpp"


namespace fx
{
    class Range
    {
    public:
        Range();
        Range(const fx::Price& min, const fx::Price& max);
        Range(const Range& tc);
        Range& operator=(const Range& tc);

        const fx::Price& GetMin() const;
        void SetMin(const fx::Price& min);

        const fx::Price& GetMax() const;
        void SetMax(const fx::Price& max);

        bool IsMinValid() const;
        bool IsMaxValid() const;

    private:
        fx::Price m_min;
        fx::Price m_max;
    };
} // namespace

#endif // __Range_hpp__


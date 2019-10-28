/*
    Copyright (C) 2018 Mihai Vasilian

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


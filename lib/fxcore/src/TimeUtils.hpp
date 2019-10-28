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


#ifndef __TimeUtils_hpp__
#define __TimeUtils_hpp__

#include "time.hpp"


namespace fx
{
    class TimeUtils
    {
    public:
        TimeUtils() = delete;
        ~TimeUtils() = delete;

        // adjust both 'to' and 'interval' to valid market hours
        static void SetValidMarketTime(sys::time& to, time_t& interval);

    };
} // namespace

#endif // __TimeUtils_hpp__

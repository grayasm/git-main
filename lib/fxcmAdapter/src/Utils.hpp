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
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

contact: grayasm@gmail.com
*/

#ifndef __Utils_hpp__
#define __Utils_hpp__

#include <stddef.h>
#include <string>
#include <ForexConnect.h>
#include "time.hpp"


namespace fxcm
{
	class Utils
	{
	public:
		Utils() = delete;
		Utils(const Utils&) = delete;
		Utils& operator=(const Utils&) = delete;

		// mm.dd.YYYY HH:MM:SS
		static void FormatDate(DATE date, char* buff);
		static void FormatDate(DATE date, sys::time& time);
		static void FormatDate(DATE date, time_t& timet);

		static void TimeToDate(const sys::time& time, DATE& date);

		static bool IsOpeningOrder(IO2GOrderRow* order);
		static bool IsClosingOrder(IO2GOrderRow* order);
	};
} // namespace



#endif // __Utils_hpp__

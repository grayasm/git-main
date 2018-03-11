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

#include "TimeUtils.hpp"


namespace fx
{
	void TimeUtils::SetValidMarketTime(misc::time& to, time_t& interval)
	{
		/*	Sanitize to time.
			Broker may return error for intervals 19:12:04 -> 19:13:00
		*/
		to -= to.sec_();

		/*	Shift back to time, outside weekend hours.

			FRI 16:55 EST -> SUN 17:15 EST	coresponding to:
			FRI 22:00 UTC -> SUN 22:15 UTC
			
			And also avoid legal holidays (at least for FXCM).
			25-DEC and 01-JAN
		*/
		while ((to.wday() == misc::time::SAT) ||
			(to.wday() == misc::time::FRI && to.hour_() >= 22) ||
			(to.wday() == misc::time::SUN && to.hour_() < 22) ||
			(to.mon_() == misc::time::Month::DEC && to.mday_() == 25) ||
			(to.mon_() == misc::time::Month::JAN && to.mday_() == 1))
		{
			to -= misc::time::hourSEC;
		}


		/*	Shift back from time, outside weekend hours,
			by increasing the interval.			
		*/
		time_t adjustedinterval = interval;
		misc::time from = to - adjustedinterval;
		while ((from.wday() == misc::time::SAT) ||
			(from.wday() == misc::time::FRI && from.hour_() >= 22) ||
			(from.wday() == misc::time::SUN && from.hour_() < 22) ||
			(from.mon_() == misc::time::Month::DEC && from.mday_() == 25) ||
			(from.mon_() == misc::time::Month::JAN && from.mday_() == 1))
		{
			adjustedinterval += misc::time::hourSEC;
			from = to - adjustedinterval;
		}

		if (adjustedinterval != interval) // it was adjusted
		{
			interval += adjustedinterval;
		}
	}
} // namespace

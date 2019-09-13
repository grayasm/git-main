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
	void TimeUtils::SetValidMarketTime(sys::time& to, time_t& interval)
	{
		/*	Sanitize to time.
			Broker may return error for intervals 19:12:04 -> 19:13:00
		*/
		to -= to.sec_();

		/*	For each full week add 2 extra days to compensate for
			FRI 22:00 -> SUN 22:00 outside trading hours.
		*/
		int weeks = interval / (7 * sys::time::daySEC);
		interval += weeks * (2 * sys::time::daySEC);


		/*	Shift back to time, outside weekend hours.

			FRI 16:55 EST -> SUN 17:15 EST	coresponding to:
			FRI 22:00 UTC -> SUN 22:15 UTC
			
			And also avoid legal holidays (at least for FXCM).
			25-DEC and 01-JAN
		*/
		while ((to.wday() == sys::time::SAT) ||
			(to.wday() == sys::time::FRI && to.hour_() >= 22) ||
			(to.wday() == sys::time::SUN && to.hour_() < 22) ||
			(to.mon_() == sys::time::Month::DEC && to.mday_() == 25) ||
			(to.mon_() == sys::time::Month::JAN && to.mday_() == 1))
		{
			to -= sys::time::hourSEC;
		}


		/*	Shift back from time, outside weekend hours,
			by increasing the interval.			
		*/
		time_t adjustedinterval = interval;
		sys::time from = to - adjustedinterval;
		while ((from.wday() == sys::time::SAT) ||
			(from.wday() == sys::time::FRI && from.hour_() >= 22) ||
			(from.wday() == sys::time::SUN && from.hour_() < 22) ||
			(from.mon_() == sys::time::Month::DEC && from.mday_() == 25) ||
			(from.mon_() == sys::time::Month::JAN && from.mday_() == 1))
		{
			adjustedinterval += sys::time::hourSEC;
			from = to - adjustedinterval;
		}

		if (adjustedinterval != interval) // it was adjusted
		{
			interval += adjustedinterval;
		}
	}


} // namespace

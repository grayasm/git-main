/*
  Copyright (C) 2015 Mihai Vasilian

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

#ifndef __time_hpp__
#define __time_hpp__


#include <time.h>
#include "string.hpp"


namespace misc
{
	/*	The class operates only with time values in UTC.
	 *	
	 *	The class retains initial time_t variable which is the number of seconds
	 *	since Epoch 00:00 Jan 1, 1970 UTC
	 * 
	 *	This type is converted at initialization time to a struct tm type which
	 *	is a calendar date and time broken down into its components.
	 *	tm values are in UTC/GMT system.
	 *
	 *	Dates previous to UTC: 01-JAN-1900 cannot be represented by this class.
	 *	Date after UTC: 19-JAN-2038 03:14:08 cannot be represented by time_t type
	 *	signed 32 bit integer. The entire lib must be compiled as 64bit.
	 *  http://en.wikipedia.org/wiki/Year_2038_problem
	 */
	class time
	{
	public:
		/* Months of the year. */
		enum Month
		{
			JAN=0,FEB,MAR,APR,MAY,JUN,JUL,AUG,SEP,OCT,NOV,DEC
		};
		
		/* Day of the week. */
		enum WDay
		{
			SUN=0,MON,TUE,WED,THU,FRI,SAT
		};

		time();				/* UTC: 1970-JAN-1 00:00:00 */
		time(time_t t);
		
		/*	UTC time format.
		 *	year	Year. 1970 or greater
		 *  mon		Month. [JAN-DEC]
		 *  day		Day.   [1-31]
		 *  hour	Hours. [0-23]
		 *  min		Minutes. [0-59]
		 *  sec		Seconds. [0-59]
		 */
		time(int year, enum Month mon, int day, int hour, int min, int sec);
		
		/*	UTC string format: "m.d.Y H:M:S" */
		time(const misc::string& str);

		time(const time& tc);
		
		time& operator=(const time& tc);
		
		~time();
		
		time operator-(const time& beg) const;		/* req: beg >= this*/
		time operator+(const time& off) const;
		bool operator<(const time& t) const;
		bool operator>(const time& t) const;
		bool operator==(const time& t) const;
		bool operator!=(const time& t) const;
		bool operator<=(const time& t) const;
		bool operator>=(const time& t) const;
		
		void operator+=(int sec);
		void operator-=(int sec);
		
		misc::string tostring() const;
		misc::string tolocaltime() const;
		time_t totime_t() const;
		
		int sec_() const;			// _ suffixed to avoid nasty macros
		int min_() const;
		int hour_() const;
		int mday_() const;			// 1 up to 31
		int mon_() const;			// Jan=1, Feb=2, ..., Dec=12
		int year_() const;			// between 1970 and 2038(32) or 3000(64bit)

		enum WDay wday() const;		// day of week
		int yday() const;			// day of the year
		int isdst() const;			// -1 unknown, 0 not set, 1 dst is set
		
		
		static const int daySEC = 86400;
		static const int hourSEC=  3600;
		static const int minSEC =    60;
		
	private:
		/*	UTC time format.
		 *	year	Year. 1970 or greater
		 *  mon		Month. [0-11]
		 *  day		Day.   [1-31]
		 *  hour	Hours. [0-23]
		 *  min		Minutes. [0-59]
		 *  sec		Seconds. [0-59]
		 */
		time(int year, int mon, int day, int hour, int min, int sec);
		
		void init(time_t t);
		void init(struct tm t);
		int	yisleap(int year) const;
		/*	day		[1-31]
		 *  mon		[JAN-DEC]
		 *	year	[1970 - ...]
		 *	return	[0-365]
		 */
		int get_yday(int day, enum Month mon, int year) const;
		
	private:
		time_t		m_t;
		struct tm	m_tm;
	};
} // namespace

#endif // __time_hpp__
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
	 */
	class time
	{
	public:
		/* Months of the year. */
		enum Month
		{
			JAN=0,FEB,MAR,APR,MAY,JUN,JUL,AUG,SEP,OCT,NOV,DEC
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
		
		time& operator+=(int sec);
		
		misc::string tostring() const;
		
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
		void reduce(double sec, int& days, int& hours, int& minutes, int& seconds) const;
		
	private:
		time_t		m_t;
		struct tm	m_tm;
	};
} // namespace

#endif // __time_hpp__
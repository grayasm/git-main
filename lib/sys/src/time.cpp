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



#include "time.hpp"
#include "strconv.hpp"
#include <limits.h>


namespace sys
{
	time::time()
	{
		/* UTC: 1970-Jan-1 00:00:00 */
		struct tm initm;		
		initm.tm_year = 70; // 1970-1900
		initm.tm_mon = 0;
		initm.tm_mday = 1;
		initm.tm_hour = 0;
		initm.tm_min = 0;
		initm.tm_sec = 0;
		
		init( initm );
	}

	time::time(time_t t)
	{
		init(t); 
	}
	
	/*	UTC time format.
	 *	year	Year. 1970 or greater
	 *  mon		Month. [JAN-DEC]
	 *  day		Day.   [1-31]
	 *  hour	Hours. [0-23]
	 *  min		Minutes. [0-59]
	 *  sec		Seconds. [0-59]
	 */
	time::time(int year, enum Month mon, int day, int hour, int min, int sec)
	{
		if( year < 1970 || mon < JAN || mon > DEC ||
			day < 1 || hour < 0 || min < 0 || sec < 0 )
			throw stl::exception("time is invalid");

		struct tm initm;		
		initm.tm_year = year - 1900;
		initm.tm_mon = (mon - JAN);
		initm.tm_mday = day;
		initm.tm_hour = hour;
		initm.tm_min = min;
		initm.tm_sec = sec;
		
		init( initm );
	}
	
	/*	year	Year. 1900 or greater
	 *  mon		Month. [0-11]
	 *  day		Day.   [1-31]
	 *  hour	Hours. [0-23]
	 *  min		Minutes. [0-59]
	 *  sec		Seconds. [0-59]
	 */
	time::time(int year, int mon, int day, int hour, int min, int sec)
	{
		if(year < 1900 || mon < 0 || mon> 11 ||
			day < 1 || hour < 0 || min < 0 || sec < 0)
			throw stl::exception("time is invalid");

		struct tm initm;
		initm.tm_year = year - 1900;
		initm.tm_mon =  mon;
		initm.tm_mday = day;
		initm.tm_hour = hour;
		initm.tm_min = min;
		initm.tm_sec = sec;
		
		init( initm );
	}

	/*	UTC string format: "m.d.Y H:M:S" */
	time::time(const stl::string& str)
	{
		int mon, day, year, hour, min, sec;
		mon = day = year = hour = min = sec = -1;

		sscanf(str.c_str(), "%d.%d.%d %d:%d:%d",
			&mon, &day, &year, &hour, &min, &sec);

		if (year < 1900 || mon < 1 || mon > 12 ||
			day < 1 || hour < 0 || min < 0 || sec < 0)
			throw stl::exception("time is invalid");

		struct tm initm;
		initm.tm_year = year - 1900;
		initm.tm_mon = (mon - 1); // 0 for JAN
		initm.tm_mday = day;
		initm.tm_hour = hour;
		initm.tm_min = min;
		initm.tm_sec = sec;

		init( initm );
	}

	time::time(const time& tc)
	{
		*this = tc;
	}

	time& time::operator=(const time& tc)
	{
		if(this != &tc)
		{
			m_t = tc.m_t;
			m_tm = tc.m_tm;
		}
		return *this;
	}

	time::~time()
	{
	}

	time time::operator-(const time& beg) const
	{
		double diff = difftime(m_t, beg.m_t);

		if (diff < 0)
			throw stl::exception("time is invalid");

		time ret((time_t)diff);
		return ret;
	}

	time time::operator+(const time& off) const
	{
		time orig(1970, 0, 1, 0, 0, 0);
		double diff = difftime(off.m_t, orig.m_t);

		if (diff < 0)
			throw stl::exception("time is invalid");

		time ret(m_t + (time_t)diff);
		return ret;
	}
	
	bool time::operator<(const time& t) const
	{
		double sec = difftime(m_t, t.m_t);
		return sec < 0;
	}
	
	bool time::operator>(const time& t) const
	{
		double sec = difftime(m_t, t.m_t);
		return sec > 0;
	}

	bool time::operator==(const time& t) const
	{
		double sec = difftime(m_t, t.m_t);
		return sec == 0;
	}
	
    bool time::operator!=(const time& t) const
    {
		double sec = difftime(m_t, t.m_t);
		return sec != 0;
	}

	bool time::operator<=(const time& t) const
	{
		double sec = difftime(m_t, t.m_t);
		return sec <= 0;
	}

	bool time::operator>=(const time& t) const
	{
		double sec = difftime(m_t, t.m_t);
		return sec >= 0;
	}
	
	void time::operator+=(int sec)
	{
		time_t newt = m_t + sec;
		init( newt );
	}
	
	void time::operator-=(int sec)
	{
		time_t newt = m_t - sec;
		init( newt );
	}

	stl::string time::tostring() const
	{
		char  smon[12][4]={ "JAN","FEB","MAR","APR","MAY","JUN",
							"JUL","AUG","SEP","OCT","NOV","DEC"};
		stl::string stime;
		stime += stl::from_value( m_tm.tm_year + 1900 );
		stime += U("-");
		stime += smon[m_tm.tm_mon];
		stime += U("-");
		stime += stl::from_value( m_tm.tm_mday );
		stime += U(" ");
		stime += stl::from_value( m_tm.tm_hour );
		stime += U(":");
		stime += stl::from_value( m_tm.tm_min );
		stime += U(":");
		stime += stl::from_value( m_tm.tm_sec );
		return stime;
	}
	
	stl::string time::tolocaltime() const
	{
		char  smon[12][4]={ "JAN","FEB","MAR","APR","MAY","JUN",
							"JUL","AUG","SEP","OCT","NOV","DEC"};
		
		struct tm loctm = *localtime(&m_t);
		
		stl::string stime;
		stime += stl::from_value( loctm.tm_year + 1900 );
		stime += U("-");
		stime += smon[loctm.tm_mon];
		stime += U("-");
		stime += stl::from_value( loctm.tm_mday );
		stime += U(" ");
		stime += stl::from_value( loctm.tm_hour );
		stime += U(":");
		stime += stl::from_value( loctm.tm_min );
		stime += U(":");
		stime += stl::from_value( loctm.tm_sec );
		return stime;		
	}

	time_t time::totime_t() const
	{
		/* useful if initialized with a different ctor than: time(time_t) */
		return m_t;
	}

	int time::sec_() const
	{
		return m_tm.tm_sec;
	}

	int time::min_() const
	{
		return m_tm.tm_min;
	}

	int time::hour_() const
	{
		return m_tm.tm_hour;
	}

	int time::mday_() const
	{
		return m_tm.tm_mday;
	}

	int time::mon_() const
	{
		return (m_tm.tm_mon + 1);
	}

	int time::year_() const
	{
		return (m_tm.tm_year + 1900);
	}

	enum time::WDay time::wday() const
	{
		return (WDay) (SUN + m_tm.tm_wday); // SUN + [0-6]
	}
	
	int time::yday() const
	{
		return m_tm.tm_yday;
	}

	int time::isdst() const
	{
		return m_tm.tm_isdst;
	}

	void time::init(time_t t)
	{
		/* already epoch time */
		m_t = t;
		m_tm = *gmtime(&m_t);
	}
	
	void time::init(struct tm t)
	{
		// For UTC: 1-JAN-1900 00:00:00
		// we need a 8 bytes signed integer.		
		long tm_year = t.tm_year;
		long tm_yday = 0;
		{
			int tm_mday = t.tm_mday;
			int tm_mon = t.tm_mon;			
			tm_yday = get_yday(tm_mday, (enum Month)tm_mon, tm_year + 1900);
		}
		
		long tm_hour = t.tm_hour;
		long tm_min = t.tm_min;
		long tm_sec = t.tm_sec;	
	
		/* Seconds since the Epoch.
		 * http://pubs.opengroup.org/onlinepubs/9699919799/basedefs/V1_chap04.html#tag_04_15
		 */
		m_t =
			tm_sec + tm_min*60 + tm_hour*3600 + tm_yday*86400 +
			(tm_year-70)*31536000 + ((tm_year-69)/4)*86400 -
			((tm_year-1)/100)*86400 + ((tm_year+299)/400)*86400;

		/* time in UTC format */
		m_tm = *gmtime(&m_t);	
	}
	
	int time::yisleap(int year) const
	{
		return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
	}

	int time::get_yday(int day, enum Month mon, int year) const
	{
		if(day < 1 || mon < JAN || mon > DEC || year < 1900)
			throw stl::exception("time is invalid");
		
		int leap = yisleap(year);
		int month = (mon - JAN);
		
		int dcheck[12] = {31,28 + leap,31,30,31,30,31,31,30,31,30,31};
		if(day > dcheck[month])
			throw stl::exception("time is invalid");
		
		static const int days[2][12] = {
			{0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334},
			{0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335}
		};
		
		return days[leap][month] + day - 1; // [0-365]
	}


} // namespace
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


namespace misc
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
	
	time::time(int year, enum Month mon, int day, int hour, int min, int sec)
	{
		if( year < 1970 || mon < JAN || mon > DEC ||
			day < 1 || hour < 0 || min < 0 || sec < 0 )
			throw misc::exception("time is invalid");

		struct tm initm;		
		initm.tm_year = year - 1900;
		initm.tm_mon = (mon - JAN);
		initm.tm_mday = day;
		initm.tm_hour = hour;
		initm.tm_min = min;
		initm.tm_sec = sec;
		
		init( initm );
	}
	
	/*	year	Year. 1970 or greater
	 *  mon		Month. [0-11]
	 *  day		Day.   [1-31]
	 *  hour	Hours. [0-23]
	 *  min		Minutes. [0-59]
	 *  sec		Seconds. [0-59]
	 */
	time::time(int year, int mon, int day, int hour, int min, int sec)
	{
		if(year < 1970 || mon < 0 || day < 1 || hour < 0 || min < 0 || sec < 0)
			throw misc::exception("time is invalid");

		struct tm initm;
		initm.tm_year = year - 1900;
		initm.tm_mon =  mon;
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
		double sec = difftime(m_t, beg.m_t);
		int d=0,h=0,m=0,s=0;
		reduce(sec, d, h, m, s);
		time ret(1970, 0, 1+d, 0+h, 0+m, 0+s);
		return ret;
	}

	time time::operator+(const time& off) const
	{
		time orig(1970, 0, 1, 0, 0, 0);
		double sec = difftime(off.m_t, orig.m_t);
		int d=0,h=0,m=0,s=0;
		reduce(sec, d, h, m, s);
		time ret(m_tm.tm_year + 1900, m_tm.tm_mon, m_tm.tm_mday + d, 
				 m_tm.tm_hour + h, m_tm.tm_min + m, m_tm.tm_sec + s);
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
	
	time& time::operator+=(int sec)
	{
		m_tm.tm_sec += sec;
		init( m_tm );
		return *this;
	}

	misc::string time::tostring() const
	{
		char  smon[12][4]={ "JAN","FEB","MAR","APR","MAY","JUN",
							"JUL","AUG","SEP","OCT","NOV","DEC"};
		misc::string stime;
		stime += misc::from_value( m_tm.tm_year + 1900 );
		stime += U("-");
		stime += smon[m_tm.tm_mon];
		stime += U("-");
		stime += misc::from_value( m_tm.tm_mday );
		stime += U(" ");
		stime += misc::from_value( m_tm.tm_hour );
		stime += U(":");
		stime += misc::from_value( m_tm.tm_min );
		stime += U(":");
		stime += misc::from_value( m_tm.tm_sec );
		return stime;
	}

	void time::init(time_t t)
	{
		/* already epoch time */
		m_t = t;
		m_tm = *gmtime(&m_t);
	}
	
	void time::init(struct tm t)
	{
		struct tm tmcpy = t;
		time_t loct = mktime(&tmcpy);	// modify copy of tmval
		struct tm tmcalc = *localtime(&loct); // calculate tm_yday
		
		/* calculate unix time time_t for t */
		int tm_year = t.tm_year;
		int tm_yday = tmcalc.tm_yday;
		int tm_hour = t.tm_hour;
		int tm_min = t.tm_min;
		int tm_sec = t.tm_sec;	
	
		/* Seconds since the Epoch.
		 * http://pubs.opengroup.org/onlinepubs/9699919799/basedefs/V1_chap04.html#tag_04_15
		 */
		m_t =
			tm_sec + tm_min*60 + tm_hour*3600 + tm_yday*86400 +
			(tm_year-70)*31536000 + ((tm_year-69)/4)*86400 -
			((tm_year-1)/100)*86400 + ((tm_year+299)/400)*86400;

		/* same time in UTC format */
		m_tm = *gmtime(&m_t);	
	}
	
	void time::reduce(double sec, int& days, int& hours, int& minutes, int& seconds) const
	{
		days = (int)(sec / 86400.);
		hours = (int)((sec - days * 86400) / 3600.);
		minutes = (int)((sec - days * 86400 - hours * 3600) / 60.);
		seconds = (int)(sec - days * 86400 - hours * 3600 - minutes * 60);
	}

} // namespace
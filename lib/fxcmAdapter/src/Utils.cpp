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

#include "Utils.hpp"
#include <sstream>
#include <iomanip>


namespace fxcm
{
	void Utils::FormatDate(DATE date, char* buf)
	{
		struct tm tmBuf = { 0 };
		CO2GDateUtils::OleTimeToCTime(date, &tmBuf);

		using namespace std;
		stringstream sstream;
		sstream << setw(2) << setfill('0') << tmBuf.tm_mon + 1 << "." \
			<< setw(2) << setfill('0') << tmBuf.tm_mday << "." \
			<< setw(4) << tmBuf.tm_year + 1900 << " " \
			<< setw(2) << setfill('0') << tmBuf.tm_hour << ":" \
			<< setw(2) << setfill('0') << tmBuf.tm_min << ":" \
			<< setw(2) << setfill('0') << tmBuf.tm_sec;
		strcpy(buf, sstream.str().c_str());
	}

	void Utils::FormatDate(DATE date, misc::time& mtime)
	{
		struct tm tmBuf = { 0 };
		CO2GDateUtils::OleTimeToCTime(date, &tmBuf);

		enum misc::time::Month month = (enum misc::time::Month)tmBuf.tm_mon;

		mtime = misc::time(
			tmBuf.tm_year + 1900,
			month,
			tmBuf.tm_mday,
			tmBuf.tm_hour,
			tmBuf.tm_min,
			tmBuf.tm_sec);
	}

	void Utils::FormatDate(DATE date, time_t& timet)
	{
		misc::time mtime;
		FormatDate(date, mtime);
		timet = mtime.totime_t();
	}

	void Utils::TimeToDate(const misc::time& time, DATE& date)
	{
		time_t tt = time.totime_t();
		struct tm *tmt = gmtime(&tt);
		CO2GDateUtils::CTimeToOleTime(tmt, &date);
	}

	bool Utils::IsOpeningOrder(IO2GOrderRow* order)
	{
		const char* type = order->getType();
		return type[0] == 'O';
	}

	bool Utils::IsClosingOrder(IO2GOrderRow* order)
	{
		const char* type = order->getType();
		return type[0] == 'C';
	}
} // namespace

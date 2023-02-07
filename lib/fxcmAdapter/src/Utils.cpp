/*
Copyright (C) 2018 Mihai Vasilian
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

	void Utils::FormatDate(DATE date, sys::time& mtime)
	{
		struct tm tmBuf = { 0 };
		CO2GDateUtils::OleTimeToCTime(date, &tmBuf);

		enum sys::time::Month month = (enum sys::time::Month)tmBuf.tm_mon;

		mtime = sys::time(
			tmBuf.tm_year + 1900,
			month,
			tmBuf.tm_mday,
			tmBuf.tm_hour,
			tmBuf.tm_min,
			tmBuf.tm_sec);
	}

	void Utils::FormatDate(DATE date, time_t& timet)
	{
		sys::time mtime;
		FormatDate(date, mtime);
		timet = mtime.totime_t();
	}

	void Utils::TimeToDate(const sys::time& time, DATE& date)
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

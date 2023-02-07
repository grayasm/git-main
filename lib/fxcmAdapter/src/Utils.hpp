/*
Copyright (C) 2018 Mihai Vasilian
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

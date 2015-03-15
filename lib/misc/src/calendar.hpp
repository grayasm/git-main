/*
  Copyright (C) 2014 Mihai Vasilian

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



#ifndef __calendar_hpp__
#define __calendar_hpp__


namespace misc
{
	struct date
	{
	public:
		int m_year;
		int m_month;
		int m_day;

		int m_hour;
		int m_minute;
		int m_seconds;
		int m_miliseconds;
	};


	class calendar
	{
	public:
		calendar();
		~calendar();
		calendar(const calendar& tc);
		calendar& operator=(const calendar& tc);

		
		void SetMonth(int month);
		int GetMonth() const;

		void SetYear(int year);
		int GetYear() const;

		int ComputeOffset(int year, int month);

		int NumDaysYear(int year);
		int NumDaysMonth(int year, int month);
		bool IsLeapYear(int year);
		void Display(int year, int month, int offset);

/*
		int GetDays(date from, date to);
		long GetMinutes(date from, date to);
		long GetSeconds(date from, date to);*/

	private:
		int m_month;
		int m_year;
	};
} // namespace




/**********************************************************************
 * This function will call all the functions necessary to make a calendar
 * for any given month and year.
 ***********************************************************************/
//int main()
//{
//   int numDays;
//   int offset;
//   int month;
//   int year;
//
//   month = getMonth(month);
//
//   year = GetYear(year);
//
//   offset = ComputeOffset(year, month);
//
//   Display(year, month, offset);
//
//   return 0;
//}


#endif // __calendar_hpp__
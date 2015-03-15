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


#include "calendar.hpp"
#include "exception.hpp"
#include <iostream>
#include <iomanip>


namespace misc
{
	calendar::calendar()
	{
	}

	calendar::~calendar()
	{
	}

	calendar::calendar(const calendar& tc)
	{
		*this = tc;
	}

	calendar& calendar::operator=(const calendar& tc)
	{
		if(this != &tc)
		{

		}
		return *this;
	}

	void calendar::SetMonth(int month)
	{
		if(month < 1 || month > 12)
			throw misc::exception("Invalid month.");
		m_month = month;
	}

	int calendar::GetMonth() const
	{
		return m_month;
	}

	void calendar::SetYear(int year)
	{
		if(year < 1753)
			throw misc::exception("Invalid year.");

		m_year = year;
	}

	int calendar::GetYear() const
	{
		return m_year;
	}

	int calendar::ComputeOffset(int year, int month)
	{
		int offset = 0;
		int count = year - 1753;
		for(int iYear = 0; iYear < count; iYear++)
		{
			offset = ( offset + 365 + IsLeapYear(year)) % 7;
		}

		for(int iMonth = 1; iMonth < month; iMonth++)
		{
			offset = ( offset + NumDaysMonth(year, iMonth)) % 7;
		}

		return offset;
	}


	int calendar::NumDaysYear(int year)
	{
		int daysYear = 365 + IsLeapYear(year);
		return daysYear;
	}

	int calendar::NumDaysMonth(int year, int month)
	{
		int daysMonth;

		if(month == 1)
			daysMonth = 31;
		else if(month == 2)
		{
			if(IsLeapYear(year) == true)
				daysMonth = 29;
			else
				daysMonth = 28;
		}
		else if(month == 3)
			daysMonth = 31;
		else if(month == 4)
			daysMonth = 30;
		else if(month == 5)
			daysMonth = 31;
		else if(month == 6)
			daysMonth = 30;
		else if(month == 7)
			daysMonth = 31;
		else if(month == 8)
			daysMonth = 31;
		else if(month == 9)
			daysMonth = 30;
		else if(month == 10)
			daysMonth = 31;
		else if(month == 11)
			daysMonth = 30;
		else if(month == 12)
			daysMonth = 31;

		return daysMonth;
	}

	bool calendar::IsLeapYear(int year)
	{
		if(year % 4 == 0 && year % 100 != 0 || year % 400 == 0)
			return true;
		else
			return false;
	}

	void calendar::Display(int year, int month, int offset)
	{
		int dayOfWeek;
		int day;
		using namespace std;

		cout << endl;
		if ( month == 1)
		cout << "January";
		else if ( month == 2)
		cout << "February";
		else if ( month == 3)
		cout << "March";
		else if ( month == 4)
		cout << "April";
		else if ( month == 5)
		cout << "May";
		else if ( month == 6)
		cout << "June";
		else if ( month == 7)
		cout << "July";
		else if ( month == 8)
		cout << "August";
		else if ( month == 9)
		cout << "September";
		else if ( month == 10)
		cout << "October";
		else if ( month == 11)
		cout << "November";
		else if ( month == 12)
		cout << "December";


		cout << ", " << year << "\n";
		// Display month header
		cout << "  Su  Mo  Tu  We  Th  Fr  Sa\n";

		// Gets the correct offset width and end the line on the right
		//day of the week
		if (offset == 0)
		{
			day = 2;
			cout << setw(6);
		}
		else if (offset == 1)
		{
			day = 3;
			cout << setw(10);
		}
		else if (offset == 2)
		{
			day = 4;
			cout << setw(14);
		}
		else if (offset == 3)
		{
		day = 5;
		cout << setw(18);
		}
		else if (offset == 4)
		{
		day = 6;
		cout << setw(22);
		}
		else if (offset == 5)
		{
		day = 7;
		cout << setw(26);
		}
		else if (offset == 6)
		{
		day = 1;
		cout << setw(2);
		}
		else
		cout << "Error offset must be >= 0 and <=6\n";

		// The loop for displaying the days and ending the line in the right place
		for ( dayOfWeek = 1; dayOfWeek <= NumDaysMonth(year, month); dayOfWeek++ )
		{
			cout << "  " <<  setw(2) << dayOfWeek;
			++day;
			if (day == 8)
			{
				cout << "\n";
				day = 1;
			}
		}

		if ( day >= 2 && day <= 7)
		cout << "\n";

		return;
	}
}

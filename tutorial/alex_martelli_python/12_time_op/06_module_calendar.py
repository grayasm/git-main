#!/usr/bin/env python3
# -*- coding: utf-8 -*-

'''The calendar module supplies calendar-related functions, including functions
to print a text calendar for a given month or year. By default, calendar takes
Monday as the first day of the week and Sunday as the last one. To change this,
call calendar.setfirstweekday . calendar handles years in module time ’s range,
typically 1970 to 2038.'''

import calendar

c = calendar.TextCalendar(calendar.SUNDAY)
c.prmonth(2007, 7)

'''
     July 2007
Su Mo Tu We Th Fr Sa
 1  2  3  4  5  6  7
 8  9 10 11 12 13 14
15 16 17 18 19 20 21
22 23 24 25 26 27 28
29 30 31
'''

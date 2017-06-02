#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# https://docs.python.org/3/library/datetime.html

import time
from datetime import timedelta
from datetime import date

'''
object
    timedelta
    tzinfo
        timezone
    time
    date
        datetime
'''

d = timedelta(microseconds=-1)
print(d.days, d.seconds, d.microseconds)  # -1 86399 999999

d = timedelta(hours=-5)
print(d)                                  # -1 day, 19:00:00


year = timedelta(days=365)
another_year = timedelta(weeks=40, days=84, hours=23,
                         minutes=50, seconds=600)  # adds up to 365 days
year.total_seconds()

print(year == another_year)  # True

ten_years = 10 * year
print(ten_years, ten_years.days // 365)            # 3650 days, 0:00:00 10

nine_years = ten_years - year
print(nine_years, nine_years.days // 365)          # 3285 days, 0:00:00 9

three_years = nine_years // 3
print(three_years, three_years.days // 365)        # 1095 days, 0:00:00 3

print(abs(three_years - ten_years) == 2 * three_years + year)  # True


# Example of counting days to an event:
today = date.today()
print(today)                                       # 2017-04-22

print(today == date.fromtimestamp(time.time()))    # True

my_birthday = date(today.year, 6, 24)
if my_birthday < today:
    my_birthday = my_birthday.replace(year=today.year + 1)
print(my_birthday)                                 # 2017-06-24

time_to_birthday = abs(my_birthday - today)
print(time_to_birthday.days)                       # 63

# Example of working with date:
d = date.fromordinal(730920)  # 730920th day after 1. 1. 0001
print(d)                      # 2002-03-11

t = d.timetuple()
for i in t:
    print(i)                  # 2002 3 11 0 0 0 0 70 -1

ic = d.isocalendar()
for i in ic:
    print(i)                  # 2002 11 1

print(d.isoformat())          # 2002-03-11
print(d.strftime("%d/%m/%y"))  # 11/03/02
print(d.strftime("%A %d. %B %Y"))  # Monday 11. March 2002
print('The {1} is {0:%d}, the {2} is {0:%B}.'.format(d, "day", "month"))
# The day is 11, the month is March.

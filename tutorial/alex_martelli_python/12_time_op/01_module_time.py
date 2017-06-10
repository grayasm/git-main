#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# https://www.tutorialspoint.com/python3/python_date_time.htm

import time
import calendar
import os


ticks = time.time()
print("Number of ticks since 12:00am, January 1, 1970:", ticks)
# 1492844657.600498

localtime = time.localtime(time.time())
print("Local current time :", localtime)
# time.struct_time(tm_year=2017, tm_mon=4, tm_mday=22, tm_hour=9, tm_min=4,
#                  tm_sec=17, tm_wday=5, tm_yday=112, tm_isdst=1)

localtime = time.asctime(time.localtime(time.time()))
print("Local current time :", localtime)  # Sat Apr 22 09:04:17 2017


cal = calendar.month(2016, 2)
print("Here is the calendar:")
print(cal)
'''
   February 2016
Mo Tu We Th Fr Sa Su
 1  2  3  4  5  6  7
 8  9 10 11 12 13 14
15 16 17 18 19 20 21
22 23 24 25 26 27 28
29
'''

print(time.strftime("%a, %d %b %Y %H:%M:%S +0000", time.gmtime()))
# Sat, 22 Apr 2017 07:04:17 +0000

print(time.strptime("30 Nov 00", "%d %b %y"))
# time.struct_time(tm_year=2000, tm_mon=11, tm_mday=30, tm_hour=0, tm_min=0,
#                  tm_sec=0, tm_wday=3, tm_yday=335, tm_isdst=-1)

os.environ['TZ'] = 'EST+05EDT,M4.1.0,M10.5.0'
time.tzset()
print(time.strftime('%X %x %Z'))  # 03:08:16 04/22/17 EDT

os.environ['TZ'] = 'AEST-10AEDT-11,M10.5.0,M3.5.0'
time.tzset()
print(time.strftime('%X %x %Z'))  # 17:08:16 04/22/17 AEST


os.environ['TZ'] = 'US/Eastern'
time.tzset()
print(time.tzname)                # ('EST', 'EDT')

os.environ['TZ'] = 'Egypt'
time.tzset()
print(time.tzname)                # ('EET', 'EET')

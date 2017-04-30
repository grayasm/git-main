#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# before running the script install pytz:
# pip install pytz

# https://pypi.python.org/pypi/pytz

from datetime import datetime
from datetime import timedelta
import pytz
from pytz import timezone

utc = pytz.utc
print(utc)  # UTC

eastern = timezone('US/Eastern')
print(eastern.zone)  # US/Eastern

amsterdam = timezone('Europe/Amsterdam')
fmt = '%Y-%m-%d %H:%M:%S %Z%z'


'''This library only supports two ways of building a localized time. The
first is to use the ``localize()`` method provided by the pytz library.
This is used to localize a naive datetime (datetime with no timezone
information):'''

loc_dt = eastern.localize(datetime(2002, 10, 27, 6, 0, 0))
print(loc_dt.strftime(fmt))  # 2002-10-27 06:00:00 EST-0500


'''The second way of building a localized time is by converting an existing
localized time using the standard ``astimezone()`` method:'''

ams_dt = loc_dt.astimezone(amsterdam)
print(ams_dt.strftime(fmt))  # 2002-10-27 12:00:00 CET+0100


'''Unfortunately using the tzinfo argument of the standard datetime
constructors ''does not work'' with pytz for many timezones.'''
print(datetime(2002, 10, 27, 12, 0, 0, tzinfo=amsterdam).strftime(fmt))
# 2002-10-27 12:00:00 LMT+0020


'''It is safe for timezones without daylight saving transitions though, such
as UTC:'''
print(datetime(2002, 10, 27, 12, 0, 0, tzinfo=pytz.utc).strftime(fmt))
# 2002-10-27 12:00:00 UTC+0000


'''The preferred way of dealing with times is to always work in UTC,
converting to localtime only when generating output to be read
by humans.'''
utc_dt = datetime(2002, 10, 27, 6, 0, 0, tzinfo=utc)
loc_dt = utc_dt.astimezone(eastern)
print(loc_dt.strftime(fmt))
# 2002-10-27 01:00:00 EST-0500


'''This library also allows you to do date arithmetic using local
times, although it is more complicated than working in UTC as you
need to use the ``normalize()`` method to handle daylight saving time
and other timezone transitions. In this example, ``loc_dt`` is set
to the instant when daylight saving time ends in the US/Eastern
timezone.'''

before = loc_dt - timedelta(minutes=10)
print(before.strftime(fmt))                     # 2002-10-27 00:50:00 EST-0500
print(eastern.normalize(before).strftime(fmt))  # 2002-10-27 01:50:00 EDT-0400

after = eastern.normalize(before + timedelta(minutes=20))
print(after.strftime(fmt))                      # 2002-10-27 01:10:00 EST-0500


'''Creating local times is also tricky, and the reason why working with
local times is not recommended. Unfortunately, you cannot just pass
a ``tzinfo`` argument when constructing a datetime (see the next
section for more details)'''

dt = datetime(2002, 10, 27, 1, 30, 0)
dt1 = eastern.localize(dt, is_dst=True)
print(dt1.strftime(fmt))                        # 2002-10-27 01:30:00 EDT-0400


dt2 = eastern.localize(dt, is_dst=False)
print(dt2.strftime(fmt))                        # 2002-10-27 01:30:00 EST-0500


'''Converting between timezones is more easily done, using the
standard astimezone method.'''

utc_dt = utc.localize(datetime.utcfromtimestamp(1143408899))
print(utc_dt.strftime(fmt))                     # 2006-03-26 21:34:59 UTC+0000


au_tz = timezone('Australia/Sydney')
au_dt = utc_dt.astimezone(au_tz)
print(au_dt.strftime(fmt))                      # 2006-03-27 08:34:59 AEDT+1100

utc_dt2 = au_dt.astimezone(utc)
utc_dt2.strftime(fmt)
print(utc_dt == utc_dt2)  # True


'''You can take shortcuts when dealing with the UTC side of timezone
conversions. ``normalize()`` and ``localize()`` are not really
necessary when there are no daylight saving time transitions to
deal with.'''

utc_dt = datetime.utcfromtimestamp(1143408899).replace(tzinfo=utc)
print(utc_dt.strftime(fmt))                    # 2006-03-26 21:34:59 UTC+0000

au_tz = timezone('Australia/Sydney')
au_dt = au_tz.normalize(utc_dt.astimezone(au_tz))
print(au_dt.strftime(fmt))                     # 2006-03-27 08:34:59 AEDT+1100

utc_dt2 = au_dt.astimezone(utc)
print(utc_dt2.strftime(fmt))                   # 2006-03-26 21:34:59 UTC+0000

# and much more ...

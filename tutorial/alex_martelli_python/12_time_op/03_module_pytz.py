#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# before running the script install pytz:
# pip install pytz

from datetime import datetime
from datetime import timedelta
import pytz
from pytz import timezone

utc = pytz.utc
print(utc)  # UTC

eastern = timezone('US/Eastern')
print(eastern.zone)  # US/Eastern

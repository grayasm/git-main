#!/usr/bin/env python
# -*- coding: utf-8 -*-

#
# The bisect Module
#
import bisect

# bisect.bisect(seq, item, lo=0, hi=None)
l = [1, 2, 3, 6, 5]
bisect.bisect(l, 4)  # returns: 3

# bisect.insort(seq, item, lo=0, hi=None)

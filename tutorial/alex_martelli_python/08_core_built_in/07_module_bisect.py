#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# pag. 176, The bisect Module
#           The bisect module uses a bisection algorithm to keep a list in
#           sorted order as items are inserted. bisect's operation is faster
#           than calling a list's sort method after each insertion.

#    https://pymotw.com/2/bisect/
import bisect
import random

# Use a constant see to ensure that we see
# the same pseudo-random numbers each time
# we run the loop.
random.seed(1)

# Generate 20 random numbers and
# insert them into a list in sorted
# order.
l = []
for i in range(1, 20):
    r = random.randint(1, 100)
    position = bisect.bisect(l, r)
    bisect.insort(l, r)
    print ('%2d %2d' % (r, position), l)

#!/usr/bin/env python3
# -*- coding: utf-8 -*-

#
# The heapq Module
#
import heapq

#  heapq.heapify(alist)
l = [6, 5, 4, 3, 2, 1]   # [6, 5, 4, 3, 2, 1]
heapq.heapify(l)        # [1, 2, 3, 4, 5, 6]

#  heapq.heappop(alist)
#  heapq.heappush(alist, item)
#  heapq.heapreplace(alist, item)
#  heapq.nlargest(n, seq)
#  heapq.nsmallest(n, seq)

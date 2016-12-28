#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# pag. 177, The heapq Module
#           The heapq module uses heap algorithms to keep a list in
#           “nearly sorted” order as items are inserted and extracted.
#           heapq ’s operation is faster than either calling a list’s sort
#           method after each insertion or using bisect , and, for many
#           purposes, (such as implementing “priority queues”) the nearly
#           sorted order supported by heapq may be just as useful as a
#           fully sorted order.

'''
heapq.heapify(alist)
heapq.heappop(alist)
heapq.heappush(alist, item)
heapq.heapreplace(alist, item)
heapq.nlargest(n, seq)
heapq.nsmallest(n, seq)
'''


import heapq

l = [6, 5, 4, 3, 2, 1]   # [6, 5, 4, 3, 2, 1]
heapq.heapify(l)         # [1, 2, 3, 4, 5, 6]

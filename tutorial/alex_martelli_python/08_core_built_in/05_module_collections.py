#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# pag. 173, The collections Module
#           The collections module (introduced in Python 2.4) is intended
#           to eventually supply several interesting types that are collections
#           (i.e., containers, like deque and defaultdict)


import collections

# *** deque ***

# 'collections.deque'
deq = collections.deque()
deq.append('a')
deq.appendleft('b')
deq.clear()
#  deq.extend(iterable)
#  deq.extendleft(item)
#  deq.pop()
#  deq.popleft()
#  deq.rotate(n=1)

# *** defaltdict ***

# 'collections.defaultdict'

# https://docs.python.org/2/library/collections.html#module-collections

# 'collections.OrderedDict'
# 'collections.Counter'
# 'collections.namedtuple()'

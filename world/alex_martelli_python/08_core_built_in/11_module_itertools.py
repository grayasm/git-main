#!/usr/bin/env python
# -*- coding: utf-8 -*-

#
# The intertools Module
#
# https://docs.python.org/2/library/itertools.html
import itertools

#  itertools.chain(*iterables)
#  itertools.count(firstval=0)
for i in itertools.count(5, 2):
    if i > 10:
        break
    print i

#  itertools.cycle(iterable)
#  itertools.ifilter(func, iterable)
#  itertools.imap(func, *iterables)
#  itertools.islice(iterable[,start],stop[,step])
#  itertools.izip(*iterables)
#  itertools.repeat(items[,times])
#  itertools.tee(iterable, n=2)

#!/usr/bin/env python3
# -*- coding: utf-8 -*-


# https://pymotw.com/3/timeit/
import timeit

# using setitem
t = timeit.Timer("print('main statement')", "print('setup')")

print('TIMEIT:')
print(t.timeit(2))

print('REPEAT:')
print(t.repeat(3, 2))

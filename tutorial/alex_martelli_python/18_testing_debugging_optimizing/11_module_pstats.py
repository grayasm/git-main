#!/usr/bin/env python3
# -*- coding: utf-8 -*-


# https://pymotw.com/3/profile/#module-pstats
import cProfile as profile
import pstats


def fib_seq(num):
    fibnums = []
    n = 0; m = 1; s = 0
    for i in range(num):
        s = n + m
        n = m
        m = s
        fibnums.append(s)
    return fibnums


# Create 5 set of stats
for i in range(5):
    filename = 'profile_stats_{}.stats'.format(i)
    profile.run('print({}, fib_seq(20))'.format(i), filename)

# Read all 5 stats files into a single object
stats = pstats.Stats('profile_stats_0.stats')
for i in range(1, 5):
    stats.add('profile_stats_{}.stats'.format(i))

# Clean up filenames for the report
stats.strip_dirs()

# Sort the statistics by the cumulative time spent
# in the function
stats.sort_stats('cumulative')

stats.print_stats()

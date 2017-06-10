#!/usr/bin/env python3
# -*- coding: utf-8 -*-


# https://docs.python.org/3/library/profile.html#module-profile
import cProfile
import pstats
import io


pr = cProfile.Profile()
pr.enable()


def slow(it):
    result = []
    for item in it:
        result.insert(0, item)
    return result


slow(range(20))


pr.disable()
s = io.StringIO()
sortby = 'cumulative'
ps = pstats.Stats(pr, stream=s).sort_stats(sortby)
ps.print_stats()
print(s.getvalue())

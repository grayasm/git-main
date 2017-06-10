#!/usr/bin/env python3
# -*- coding: utf-8 -*-


import timeit


def slow(it):
    result = []
    for item in it:
        result.insert(0, item)
    return result


def fast(it):
    result = []
    for item in it:
        result.append(item)
    result.reverse()
    return result


if __name__=='__main__':
    print(timeit.timeit("slow(range(50))", setup="from __main__ import slow"))
    print(timeit.timeit("fast(range(50))", setup="from __main__ import fast"))

# 11.5 sec
# 5.3 sec

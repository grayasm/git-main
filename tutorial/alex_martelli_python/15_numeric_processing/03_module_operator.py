#!/usr/bin/env python3
# -*- coding: utf-8 -*-


# https://docs.python.org/3/library/operator.html
import operator

print('lt(2, -3)= ', operator.lt(2, -3))  # False

a = 1.0000000000000001
b = 1.0
print('a = ', a)
print('b = ', b)
print('eq(a, b) = ', operator.eq(a, b))  # True, compare only first 15 digits

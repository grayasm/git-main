#!/usr/bin/env python3
# -*- coding: utf-8 -*-


# https://docs.python.org/3/library/cmath.html
# Mathematical functions for complex numbers

a = 1j
b = 1j
c = a * b
print('c = ', c)  # (-1 + 0j)

a = complex(2, 1)
b = complex(2, 1)
c = a * b
print('c = ', c)  # 4 + 2i + 2i + i^2 = 4 + 4i -1 = (3 + 4j)

import cmath

print('cmath.cos(1+1j)= ', cmath.cos(1+1j))
#  (0.8337300251311491-0.9888977057628651j)

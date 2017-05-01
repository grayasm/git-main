#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# http://www.python-course.eu/numpy.php
import numpy

cvalues = [25.3, 24.8, 26.9, 23.9]
C = numpy.array(cvalues)
print(C)                                  # [ 25.3  24.8  26.9  23.9]
print(C * 9 / 5 + 32)                     # [ 77.54  76.64  80.42  75.02]
fvalues = [x*9/5 + 32 for x in cvalues]
print(fvalues)                            # [77.54, 76.64, 80.42, 75.02]

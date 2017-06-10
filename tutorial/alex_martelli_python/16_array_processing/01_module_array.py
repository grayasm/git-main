#!/usr/bin/env python3
# -*- coding: utf-8 -*-


'''
The array module supplies a type, also called array , whose instances are
mutable sequences, like lists. An array a is a one-dimensional sequence whose
items can be only characters, or only numbers of one specific numeric type,
fixed when you create a.
'''

# https://pymotw.com/3/array/
import array


a = array.array('i', range(3))
print('Initial :', a)       # Initial : array('i', [0, 1, 2])

a.extend(range(3))
print('Extended:', a)       # Extended: array('i', [0, 1, 2, 0, 1, 2])

print('Slice   :', a[2:5])  # Slice   : array('i', [2, 0, 1])

print('Iterator:')
print(list(enumerate(a)))   # [(0, 0), (1, 1), (2, 2), (3, 0), (4, 1), (5, 2)]

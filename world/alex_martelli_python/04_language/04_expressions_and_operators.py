#!/usr/bin/env python
# -*- coding: utf-8 -*-

# -----------------------------------------------------------------------------
# Expressions and other Operators
a = `222, str`          # string conversion
print a

a = {1: 3.14, 2: 4.14}  # dictionary creation
a = [3.14, 4.14]        # list creation
a = (3.14, 4.14)        # tuple creation

def func(a):
    print a
func("show this")       # funcion call
b = a[0:1]              # slicing
print "slicing a[0:1]= ", b
b = a[1]                # indexing
print "indexing a[1]= ", b

''' I will shortly mention all the other as they look trivial:

x.attr
x**y
~x
+x, -x
x*y, x/y, x//y, x%y
x+y, x-y
x<<y, x>>y
x&y
x^y
x|y
x<y, x<=y, x>y, x>=y, x<>y, x!=y, x==y
x is y, x is not y
not x
x and y
x or y
lambda arg, ...:expr
'''

# Comparison chaining
a = 5
b = 15
c = 20
d = 21
e = a < b <= c < d
print "a < b <= c < d is ", e

# Short-Circuiting Operators
#      if expr1 and expr2:   -> if expr1 is False, expr2 is not executed
def expr2():
    print "If you see this is an error"
    return True

if a == 200 and expr2():
    print "If you see this is an error"

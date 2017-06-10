#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# pag. 172, The copy Module
#           Assignment in Python does not copy the righthand side object being
#           assigned. Rather, assignment adds a reference to the righthand side
#           object.
#           When you want a copy of object x , you can ask x for a copy of
#           itself, or you can ask x ’s type to make a new instance copied
#           from x (e.g. list(x), x.copy(), x[:], set(x), dict(x), etc).
#           Sometimes, however, you need a deep copy, where referenced objects
#           are copied recursively. Module copy supplies a deepcopy(x) function
#           to create and return a deep copy.


from copy import copy
from copy import deepcopy

l1 = [0, 1, 2, 3, 4, 5]
l2 = l1                     # not ok, passes only a reference!!
l1.clear()
print ("l2=", l2)           # []


l1 = [0, 1, 2, 3, 4, 5]     # list
l2 = copy(l1)               # using copy module (copy function)
l3 = deepcopy(l1)           # using copy module (deepcopy function)
l4 = l1.copy()              # using list copy
l5 = list(l1)               # using list new instance

l1.clear()
print ("l2=", l2)           # [0, 1, 2, 3, 4, 5]
print ("l3=", l3)           # [0, 1, 2, 3, 4, 5]
print ("l4=", l4)           # [0, 1, 2, 3, 4, 5]
print ("l5=", l5)           # [0, 1, 2, 3, 4, 5]


s1 = 'this is a sequence'   # string
s2 = s1                     # shallow copy
s3 = copy(s1)
s4 = deepcopy(s1)
s5 = s1.format(None)        # no copy, using smth else
s6 = str(s1)                # using str new instance

s1 = 'content replaced'
print ("s1=", s1)           # content replaced
print ("s2=", s2)           # this is a sequence
print ("s3=", s3)           # this is a sequence
print ("s4=", s4)           # this is a sequence
print ("s5=", s5)           # this is a sequence
print ("s6=", s6)           # this is a sequence


t1 = (0, 1, 2, 3, 4, 5)     # tuple
t2 = t1                     # shallow copy
t3 = copy(t1)
t4 = deepcopy(t1)
t5 = t1[:]                  # no copy, using slicing
t6 = tuple(t1)              # using tuple new instance

t1 = ()
print ("t1=", t1)           # ()
print ("t2=", t2)           # (0, 1, 2, 3, 4, 5)
print ("t3=", t3)           # (0, 1, 2, 3, 4, 5)
print ("t4=", t4)           # (0, 1, 2, 3, 4, 5)
print ("t5=", t5)           # (0, 1, 2, 3, 4, 5)
print ("t6=", t6)           # (0, 1, 2, 3, 4, 5)


se1 = (['x', 'y', 'z'])     # set
se2 = se1                   # not ok, passes only a reference!!
se3 = copy(se1)
se4 = deepcopy(se1)
se5 = se1.copy()
se6 = set(se1)

se1.clear()
print ("se1=", se1)         # []
print ("se2=", se2)         # []
print ("se3=", se3)         # ['x', 'y', 'z']
print ("se4=", se4)         # ['x', 'y', 'z']
print ("se5=", se5)         # ['x', 'y', 'z']
print ("se6=", se6)         # ['x', 'y', 'z']


d1 = {'x': 0, 'y': 0, 'z': 1}   # dictionary
d2 = d1                         # not ok, passes only a reference!!
d3 = copy(d1)
d4 = deepcopy(d1)
d5 = d1.copy()
d6 = dict(d1)

d1.clear()
print ("d1=", d1)           # {}
print ("d2=", d2)           # {}
print ("d3=", d3)           # {'z': 1, 'x': 0, 'y': 0}
print ("d4=", d4)           # {'z': 1, 'x': 0, 'y': 0}
print ("d5=", d5)           # {'z': 1, 'x': 0, 'y': 0}
print ("d6=", d6)           # {'z': 1, 'x': 0, 'y': 0}

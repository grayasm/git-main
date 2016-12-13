#!/usr/bin/env python
# -*- coding: utf-8 -*-


# pag. 58, Set Operations
#          Python provides a variety of operations applicable to sets.
#          Since sets are containers, the built-in len function can take a set
#          as its single argument and return the number of items in the set
#          object. A set is iterable, so you can pass it to any function
#          or method that takes an iterable argument. In this case, the items
#          of the set are iterated upon, in some arbitrary order.
#
#    set: arbitrarily unordered collections of unique items
#    frozenset:  similar but immutable

a = set((2, -3, 4, 4, -3))        # set([2, 4, -3]), unordered, but unique
b = a.copy()                      # reference to a, elements are not copied
c = b.difference(a)               # set([])
d = b.intersection(a)             # set([2, 4, -3])
e = b.issubset(a)                 # True
f = b.issuperset(a)               # True
g = b.symmetric_difference(a)     # set([])
h = b.union(a)                    # set([2, 4, -3])
b.add(11)                         # set([2, 11, 4, -3])
b.clear()                         # set([])
a.discard(-3)                     # set([2, 4])
i = a.pop()                       # 2 poped, a=set([4])
a.remove(4)                       # set([])

#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# pag. 154, Built-in Types
#           This section documents Python's core built-in types, such as
#           int, float, dict and many others. More details about many of these
#           types, and about operations on their instances, are found in
#           Chapter 4. In this section by "number" it's meant specifically
#           "noncomplex number"


import codecs
import sys


#
# Built-in Types
#

# 'basestring'  - base class for both str & unicode
print((isinstance('ciao', str)))  # prints: True


# 'bool'
x = -1
print(bool(x))    # prints: True


# 'classmethod' - returns a class method object
class c(object):
    def f(self): pass
    f = classmethod(f)

# 'complex'
c = complex(2, -3)

# 'dict'
d = dict([('x', 2), ('y', 42)])

# 'enumerate'  - returns iterator of pairs (index, value); index=0,1,2,..
a = ['x', 'y', 'z']
for i, item in enumerate(a):
    pass

# 'file', 'open'

# 'float'
f = float('1.23')


# 'frozenset'
s = frozenset([10, 20, 20, 20])  # only 2 items: 10, 20, immutable


# 'int'
i = int("200")


# 'list'
l = list([1, 2, 3, 4])

# 'long'  renamed to 'int' in python3
l = int("1323333")


# 'object' - new instance of most fundamental type, no functionality.
a = object()


# 'property' - property(fget=None, fset=None, fdel=None, doc=None)
class Pressure(object):
    def __init__(self):
        self._val = 0

    def getval(self):
        return self._val

    def setval(self, value):
        self._val = value

    def delval(self):
        del self._val

    pressure = property(getval, setval, delval, "Pressure value property")


# 'reversed'  - a new reversed iterator
l = [0, 10, 20, 40]
for i in reversed(l):
    print (i)               # prints: 40, 20, 10, 0


# 'set'
a = set([2, -3, 4, 4, -3])  # set([2, 4, -3])
b = {2, -3, 4}              # set([2, 4, -3])



# 'slice'    - slice([start,]stop[,step]) or obj[start:stop:step]
l = [0, 2, 3, 4, 5]
print(l[2: -1: 1])          # prints: [3, 4]


# 'staticmethod'
class c(object):
    def f(self): pass
    f = staticmethod(f)


# 'str'      - prints a representation of the object
#            - Implement __str__() or __repr__() in the class's metaclass.
class c(object):
    pass


print(str(c))              # prints: <class '__main__.c'>


class metac(type):
    def __repr__(self):
        return 'Wahaha!'


class c(object, metaclass=metac):
    pass


print(str(c))              # prints: Wahaha!


# 'super' - super(cls, obj)
#           Convenient when refactoring classes inheritance, so the base class
#           is not hardcoded. Always calls only the __init__ of base.
class A(object):
    def __init__(self):
        print ("A.__init__()")


class B(object):
    def __init__(self):
        print ("B.__init__()")


class C(A, B):
    def __init__(self):
        super(C, self).__init__()


x = C()     # prints: A.__init__() -> broken???? shouldn't B.__init__() show?


# 'tuple'
a = tuple((10, -5, 11))   # (10, -5, 11)
b = (10, -5, 11)          # (10, -5, 11)


# 'type'
li = [5, 4]
print((type(li)))          # prints: <type 'list'>


# 'unicode'   - unicode(string[,codec[,errors]])
#             - needs the first 4 lines in this file.
# python3: TypeError: decoding str is not supported
s = str('الإنجليزية', 'utf8')
print('utf-8 = ', s)

# 'range'     - range([start,]stop[,step=1]);
print ([i for i in range(-1, 4)])   # prints: [-1, 0, 1, 2, 3]

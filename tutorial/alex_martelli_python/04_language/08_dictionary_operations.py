#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# pag. 59, Dictionary Operations
#          Python provides a variety of operations applicable to dictionaries.
#          Since dictionaries are containers, the built-in "len" function can
#          take a dictionary as its single argument and return the number
#          of items (key/value pairs) in the dictionary object.
#          A dictionary is iterable, so you can pass it to any function or
#          method that takes an iterable argument. In this case, only the
#          keys of the dictionary are iterated upon, in some arbitrary order.
#          For example, for any dictionary D, min(D) returns the smallest key
#          in D.
#
#    the dictionary:
#    * is an arbitrary collections of items as (key:value) pairs
#    * mutable, not ordered
#    * 1 built-in type, the dictionary
#    * library and extension modules provide other mapping types
#    * keys must be hashable, values can be arbitrary types
#    * see: https://docs.python.org/2/library/stdtypes.html#dict


# *** Dictionary Membership ***
D = {97: 'a', 98: 'b', 99: 'c'}
print ('%d in D = %s' % (97, 97 in D))    # True, test key membership

# *** Indexing a Dictionary ***
a = {'x': 42, 'y': 3.14, 'z': 7}
print ("d['x']=", a['x'])                 # 42
print ("d['z']=", a['z'])                 # 7

try:
    print ("d['a']=", a['a'])             # raises KeyError exception
except:
    print ("no d['a'], stupid")

a = {'x': 42, 'y': 3.14}                  # plain assignament D[newkey]=value
a['a'] = 16                               # {'x':42, 'y':3.14, 'a':16}

del D[97]                                 # del Statement del D[key]
print ('D=', D)                           # D={98: 'b', 99: 'c'}


# *** Dictionary methods *** - non-mutating
b = a.copy()              # {'y':3.14, 'x':42, 'a':16}
c = b.items()             # [('y', 3.14), ('x', 42), ('a', 16)]
d = b.keys()              # ['y', 'x', 'a']
e = a.values()            # [3.14, 42, 16]
f = a.get('a')            # 16

# removed in python3
# g = b.has_key('m')      # False
# h = a.iteritems()       # <dictionary-itemiterator object at 0x7f7fbb46d208>
# i = b.iterkeys()        # <dictionary-keyiterator object at 0x7f7fbb46d260>
# j = b.itervalues()      # <dictionary-valueiterator object at 0x7f7fbb46d2b8>


# *** Dictionary methods *** - mutating
a.clear()                 # {}
k = b.copy()              # {y':3.14, 'x':42, 'a':16}
for key in k:
    k[key] += 0.02        # {y':3.16, 'x':42.02, 'a':16.02}
b.update(k)               # {y':3.16, 'x':42.02, 'a':16.02}

print ("a.copy    =", b)  # {'y': 3.16, 'x': 42.02, 'a': 16.02}
print ("b.items   =", c)  # dict_items([('y', 3.16), ('x', 42.02), ('a', ...
print ("b.keys    =", d)  # dict_keys(['y', 'x', 'a'])
print ("a.values  =", e)  # dict_values([])  -> see line 60: a.clear()
print ("b.values  =", b.values())  # dict_values([3.16, 42.02, 16.02])
print ("a.get('a')=", f)  # 16

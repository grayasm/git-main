#
# Dictionary Operations
#
#    the dictionary:
#    * is an arbitrary collections of items as (key:value) pairs
#    * mutable, not ordered
#    * 1 built-in type, the dictionary
#    * library and extension modules provide other mapping types
#    * keys must be hashable, values can be arbitrary types
#    * see: https://docs.python.org/2/library/stdtypes.html#dict

a = {'x': 42, 'y': 3.14, 'z': 7}
print "d['x']=", a['x']                   # 42
print "d['z']=", a['z']                   # 7

try:
    print "d['a']=", a['a']               # raises KeyError exception
except:
    print "no d['a'], stupid"

a = {'x': 42, 'y': 3.14}
a['a'] = 16                               # {'x':42, 'y':3.14, 'a':16}


# Dictionary object methods - non-mutating
b = a.copy()              # {'y':3.14, 'x':42, 'a':16}
c = b.has_key('m')        # False
d = b.items()             # [('y', 3.14), ('x', 42), ('a', 16)]
e = b.keys()              # ['y', 'x', 'a']
f = a.values()            # [3.14, 42, 16]
g = a.iteritems()         # <dictionary-itemiterator object at 0x7f7fbb46d208>
h = b.iterkeys()          # <dictionary-keyiterator object at 0x7f7fbb46d260>
i = b.itervalues()        # <dictionary-valueiterator object at 0x7f7fbb46d2b8>
j = a.get('a')            # 16

# Dictionary object methods - mutating
a.clear()                 # {}
k = b.copy()              # {y':3.14, 'x':42, 'a':16}
for key in k:
    k[key] += 0.02        # {y':3.16, 'x':42.02, 'a':16.02}
b.update(k)               # {y':3.16, 'x':42.02, 'a':16.02}

print "d=", d
print "e=", e
print "f=", f
print "g=", g
print "h=", h
print "i=", i
print "j=", j

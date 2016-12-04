#!/usr/bin/env python
# -*- coding: utf-8 -*-

# pag. 38, Data Types
#          All data values in Python are objects, and each object, or value
#          has a type. An object's type determines which operations the object
#          supports, or in other words, which operations you can perform on
#          the data value. The type also determines the object's attributes
#          and items (if any) and whether the object can be altered.
#          An object that can be altered is known as a mutable object, while
#          one that cannot be altered is an immutable object.
#          The built-in type(obj) accepts any object as its argument and
#          returns the type object that is the type of obj.
#          The built-in function isinstance(obj, type) returns True if object
#          obj has type type (or any subclass thereof); otherwise returns False
#          Python has built-in types for fundamental data types such as
#          numbers, strings, tuples, lists and dictionaries. You can also
#          create user-defined types known as classes.


# *** Integer numbers ***

1,   23,   3493    # Decimal
01,  027,  06645   # Octal
0x1, 0x17, 0xDA5   # Hexadecimal

1L,   23L,   99999333493L     # Long decimal integers
01L,  027L,  01351033136165L  # Long octal integers
0x1L, 0x17L, 0x17486CBC75L    # Long hexadecimal integers

# *** Floating-point numbers ***
0., 0.0, .0, 1., 1.0, 1e0, 1.e0, 1.0e0

# *** Complex numbers ***
0j, 0.j, 0.0j, .0j, 1j, 1.j, 1.0j, 1e0j, 1.e0j, 1.0e0j


# *** Sequences ***
#    - ordered container of items, indexed by nonnegative integers
#    - String, Tuple and List  (built-in sequences)

'this is a sequence'        # String
[42, 2, 4]                  # List
(100, 200, 300)             # Tuple


# Strings
print 'This is a literal string'

print "This is another literal string"

print 'A quote\' can be escaped but'

print "This way' is more readable"

print "A not very long string \
that spans two lines"

print "A not very long string\n\
that prints on two lines"

print """An even bigger
string that spans
three lines"""


# Tuples:
#   * immutable ordered sequence of items enclosed in (..)
#   * arbitrary objects that may be of different types

print (100, 200, 300)           # tuple with 3 items
print (3.14, )                  # tuple with 1 item
print ()                        # tuple empty (parantheses NOT optional!)
print tuple('wow')              # tuple built-in type, prints ('w','o','w')


# Lists:
#   * mutable ordered sequence of items enclosed in [ ...]
#   * The items of a list are arbitrary objects and may be of different types.

print [42, 3.14, 'hello']       # list with 3 items
print [100]                     # list with 1 item
print []                        # list empty
print list('wow')               # list built-in type, prints ['w','o','w']



# *** Sets ***
#    - arbitrarily unordered collections of unique items
#    - set
#    - frozenset
#      are built-in types equivalent with classes Set and ImmutableSet from
#      Python standard library "sets"
#    - see https://docs.python.org/2/library/sets.html#sets.Set

x = set(['ana', 'are', 'mere'])
y = set(['dan', 'are', 'pere'])
print len(x)            # number of elements in x
print 'ana' in x        # test 'ana' membership in x
print 'dan' not in y    # test 'dan' for non-membership in y
print x <= y            # test whether every element in x is in y
print x >= y            # test whether every lemenet in y is in x
print x | y             # union, new set with elements from both x and y
print x & y             # intersection, new set with elem. common to x and y
print x - y             # difference, new set with elem. in x but not in y
print x ^ y             # symmetric different, in one of them but not in both

# same as above but using set member functions
lte = x.issubset(y)
gte = x.issuperset(y)
uni = x.union(y)
int = x.intersection(y)
dif = x.difference(y)
sdf = x.symmetric_difference(y)
print "lte: %s" % lte
print "gte: %s" % gte
print "uni: %s" % uni
print "int: %s" % int
print "dif: %s" % dif
print "sym: %s" % sdf

x = frozenset(['ana', 'are', 'mere', 'forever'])
# y = x - 'ana'  TypeError: unsupported operand type -: 'frozenset' and 'str'


# *** Dictionaries ***
#    - is an arbitrary collections of items as (key:value) pairs
#    - mutable, not ordered
#    - 1 built-in type, the dictionary
#    - library and extension modules provide other mapping types
#    - keys must be hashable, values can be arbitrary types
#    - see: https://docs.python.org/2/library/stdtypes.html#dict

{'x': 42, 'y': 3.14, 'z': 7}   # Dictionary with 3 items and string keys
{1: 2, 3: 4}                   # Dictionary with 2 items and integer keys
{}                             # Empty dictionary

dict(x=42, y=3.14, z=7)        # Dictionary with 3 items and string keys
dict([[1, 2], [3, 4]])         # Dictionary with 2 items and integer keys
dict()                         # Empty dictionary

# more examples
a = dict(one=1, two=2, three=3)
b = {'one': 1, 'two': 2, 'three': 3}
c = dict(zip(['one', 'two', 'three'], [1, 2, 3]))
d = dict([('two', 2), ('one', 1), ('three', 3)])
e = dict({'three': 3, 'one': 1, 'two': 2})
print "a == b == c == d == e is %s" % (a == b == c == d == e)


# *** None ***
#     - built-in null object


# *** Callable ***
#     - those whose instances support the function call operation


# *** Boolean Values ***
#    - true:  any non-zero member or non-empty container
#    - false: 0, None and empty containers
#    - built-in bool class is of type int, don't use it with float numbers
#    - True, False: instances of type bool with string representations as
#      'True', 'False' but also numberical values 1 and 0

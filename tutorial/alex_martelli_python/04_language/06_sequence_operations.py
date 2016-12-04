#!/usr/bin/env python
# -*- coding: utf-8 -*-


#
# Sequence Operations
#    * operations on string "", tuple (), list []
#    * each class has member functions accessible


# String
a = "this is a string"
print a, " with length ", len(a)            # len(string)

# Tuple
a = (1, 2, 3, 4, 5)
print a, " with length ", len(a)            # len(tuple)

# List
a = [0, 1, 2, 3]

print a, " has len= ", len(a)               # len(list)
print a, " min:", min(a), " max:", max(a)   # min, max


def generator(a):
    for i in a:
        yield i
print a, " has sum= ", sum(generator(a))    # sum


# Concatenation and repetition
#    * can concatenate sequences of the same type with +
#    * can multiple a sequence S with an integer n.  S*n
b = [2, 3]
print a, "+", b, "=", a+b                    # [0, 1, 2, 3, 2, 3]
print a, "*", 2, "=", a*2                    # [0, 1, 2, 3, 0, 1, 2, 3]


# Membership testing
print 2, " in ", b, " is ", 2 in b           # 2 in [2, 3] is True

# Indexing a sequence
print "a = ", a               # a    = [0, 1, 2, 3]
print "a[0]= ", a[0]          # a[0] = 0
print "a[-1]=", a[-1]         # a[-1]= 3


# Slicing a sequence
print "a[0:2:1] = ", a[0:2:1]  # a[0:2:1] = [0, 1]

# Modifying a list
a[1] = 10
print "modified a= ", a        # a = [0, 10, 2, 3]
a[3:4] = [30, 40]
print "new a = ", a            # a = [0, 10, 2, 30, 40]


# List methods
a[-1] = 30                     # a = [0, 10, 2, 30, 30]
print "how many 30 are in ", a, " = ", a.count(30)  # 2


# Sorting a list
a = [-1, 100, 4, -5]
b = a
b.sort()
print a, " and sorted ", b

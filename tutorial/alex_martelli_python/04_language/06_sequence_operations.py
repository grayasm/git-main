#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# pag. 53, Sequence Operations.
#          Python supports a variety of operations applicable to all sequences,
#          including strings, lists and tuples. Some sequence operations apply
#          to all containers (including, for example sets and dictionaries,
#          which are not sequences) and some apply to all iterables, meaning
#          "any object on which you can loop", as covered in "Iterables";
#          all containers, be they sequences or otherwise, are iterable, and
#          so are many objects that are not containers, such as files, covered
#          in "File Objects" and generators convered in "Generators".
#          In the following, I use the terms sequence, container and iterable
#          quite precisely and specifically to indicate exactly which
#          operations apply to each category.


# *** Sequences in General ***
# String
a = "this is a string"
print (a, " with length ", len(a))            # len(string)

# Tuple
a = (1, 2, 3, 4, 5)
print (a, " with length ", len(a))            # len(tuple)

# List
a = [0, 1, 2, 3]

print (a, " has len= ", len(a))               # len(list)
print (a, " min:", min(a), " max:", max(a))   # min, max


def generator(a):
    for i in a:
        yield i
print (a, " has sum= ", sum(generator(a)))    # sum


# Concatenation and repetition
#    * can concatenate sequences of the same type with +
#    * can multiple a sequence S with an integer n.  S*n
b = [2, 3]
print (a, "+", b, "=", a+b)                   # [0, 1, 2, 3, 2, 3]
print (a, "*", 2, "=", a*2)                   # [0, 1, 2, 3, 0, 1, 2, 3]


# Membership testing
print (2, " in ", b, " is ", 2 in b)          # 2 in [2, 3] is True

# Indexing a sequence
print ("a = ", a)                 # a    = [0, 1, 2, 3]
print ("a[0]= ", a[0])            # a[0] = 0
print ("a[-1]=", a[-1])           # a[-1]= 3


# Slicing a sequence
print ("a[0:2:1] = ", a[0:2:1])   # a[0:2:1] = [0, 1]

# Modifying a list
a[1] = 10
print ("modified a= ", a)         # a = [0, 10, 2, 3]
a[3:4] = [30, 40]
print ("new a = ", a)             # a = [0, 10, 2, 30, 40]


# In-place operations on a list (+= , *=)
l1 = ['a', 'b', 'c']
l2 = [0, 1, 2]
l2 += l1                      # in place version of + operator
print ("l2 = ", l2)           # l2 = [0, 1, 2, 'a', 'b', 'c']
c = 2
l1 *= c                       # in place version of * operator
print ("l1 = ", l1)           # l1 = ['a', 'b', 'c', 'a', 'b', 'c']

c = 0
l1 *= c                       # for any multiplier <= 0 l1 is emptied
print ("l1 = ", l1)           # l1 = []


# List methods
a[-1] = 30                    # a = [0, 10, 2, 30, 30]
print ("how many 30 are in ", a, " = ", a.count(30))  # 2


# Sorting a list
a = [-1, 100, 4, -5]
b = a
b.sort()
print (a, " and sorted ", b)  # b = [-5, -1, 4, 100]

#!/usr/bin/env python
# -*- coding: utf-8 -*-


#
# Control Flow Statement

# The 'if' Statement
a = 100
b = 20

if a > b:
    print a, " > ", b
elif a == b:
    print a, " == ", b
else:
    print a, " < ", b


if a < 0: print a, "< 0"
elif a % 2: print a, " is positive and odd"
else: print a, " is even and non-negative"


# correct
if a: print a, " is evaluated to True"

# do not use any of the following
if a is True: print a, " is True"
if a == True: print a, " == True"
if bool(a): print "bool(", a, ") evaluates to True"


# The 'while' Statement
a = 0
while a < 5:
    print "while", a, "<= 5"
    a += 1

# The 'for' Statement
# for over a string
for letter in "ciao":
    print "give me a", letter, "..."


# 'for' over a dictionary
# dict.items() return a list of pairs [('a', 42), ('b', 3.14)...]

a = {'a': 42, 'b': 3.14, 'z': 101}
for key, value in a.items():
    if key and value:
        print "in for: key=", key, "value=", value

# Iterators
# an iterator is an object i such that you can call i.next() with no args.
# i.next() returns the next item of iterator i.
# when i has no more items raises a StopIteration exception
a = (1, 2, 3, 4)
for i in a:
    print i

# equivalent with
_temporary_iterator = iter(a)
while True:
    try:
        i = _temporary_iterator.next()
    except StopIteration:
        break
    print i


# 'range'
# 'xrange'
for i in range(1, 4):
    print i

# List comprehension idiom
#    * let's you code the common use of a for loop that inspects each item
#      in an iterable and builds a new list by appending the results of an
#      expression, computed on some or all of the items
#
#    syntax: [ expr for target in iterable lc-clauses]

b = [i for i in a if i > 2]          # [3, 4]
c = [i for i in a]                   # [1, 2, 3, 4]

# or clasic
d = []
for i in a:
    if i > 2:
        d.append(i)                  # [3, 4]
print b, c, d


# The 'break' Statement
i = 0
while True:
    global i                         # local by default
    i += 1
    if i > 3:
        break
    else:
        print i                      # 1, 2, 3

# The 'continue' Statement
i = 0
while True:
    global i                         # local by default
    i += 1
    if i < 3:
        continue
    elif i > 5:
        break
    print i                          # 3, 4, 5


# The 'else' Clause on Loop Statements
#    * executed when for/while ends naturally, not from break,return,exception
#    * suited when you want to search and element in a container
for elem in a:
    if elem > 100:
        break
else:
    print "Warning: no satisfactory item was found in container"


# The 'pass' Statement
#    * the body of a compund statement cannot be empty
#      it must always contain at least one statement
for i in range(4):
    if i == 0:
        pass       # nothing to be done in this case
    else:
        print i

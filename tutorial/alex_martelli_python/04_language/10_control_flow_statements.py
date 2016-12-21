#!/usr/bin/env python
# -*- coding: utf-8 -*-

# pag. 62, Control Flow Statements
#          A program's control flow is the order in which the program's code
#          executes. The control flow of a Python program is regulated by
#          conditional statements, loops, and function calls.
#          This section covers the "if" statement and "for" and "while" loops.
#          Functions are covered in "Functions" section. Raising and handling
#          exceptions also affects control flow. Exceptions are covered
#          in Chapter 6.



# *** The 'if' Statement ***
a = 100
b = 20

if a > b:
    print "%d > %d" % (a, b)      # 100 > 20
elif a == b:
    print "%d == %d" % (a, b)
else:
    print "%d < %d" % (a, b)


if a < 0: print a, "< 0"
elif a % 2: print a, " is positive and odd"
else: print a, " is even and non-negative"  # 100 is even and non-negative


if a: print a, " is evaluated to True"      # 100 is evaluated to True

if a is True: print a, " is True"                    # a is not True
if a == True: print a, " == True"                    # a is not == True
if bool(a): print "bool(", a, ") evaluates to True"  # bool(100) evaluates to True


# *** The 'while' Statement ***
a = 0
while a < 5:
    print "while", a, "<= 5"         # while 0 <= 5
    a += 1                           # while 1 <= 5
                                     # while 2 <= 5
                                     # while 3 <= 5
                                     # while 4 <= 5


# *** The 'for' Statement ***

# 'for' over a string
for letter in "ciao":
    print "give me a", letter, "..."


# 'for' over a dictionary
# dict.items() return a list of pairs [('a', 42), ('b', 3.14)...]

a = {'a': 42, 'b': 3.14, 'z': 101}
for key, value in a.items():
    if key and value:
        print "in for: key=", key, "value=", value


# 'for' over an Iterator
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


# 'for' over range and xrange

for i in range(1, 4):
    print i

# 'for' with list comprehension idiom
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
print "b=%s c=%s d=%s" % (b, c, d)


# *** The 'break' Statement ***
j = 0
while True:
    global j                         # local by default
    j += 1
    if j > 3:
        break
    else:
        print 'j=%d ' % (j,),        # 1, 2, 3

# *** The 'continue' Statement ***
print "\n",
k = 0
while True:
    global k                         # local by default
    k += 1
    if k < 3:
        continue
    elif k > 5:
        break
    print "k=%d " % (k,),            # 3, 4, 5


# *** The 'else' Clause on Loop Statements ***
#    * executed when for/while ends naturally, not from break,return,exception
#    * suited when you want to search and element in a container
for elem in a:
    if elem > 100:
        break
else:
    print "\nNo item > 100 was found in %s" % (a,)  # No item > 100 was ...


# *** The 'pass' Statement ***
#    * the body of a compund statement cannot be empty
#      it must always contain at least one statement
for m in range(4):
    if m == 0:
        pass                     # nothing to be done in this case
    else:
        print "m=%d " % (m,),    # 1, 2, 3

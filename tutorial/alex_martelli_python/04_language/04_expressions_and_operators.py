#!/usr/bin/env python
# -*- coding: utf-8 -*-

# pag. 50, Expressions and Operators
#          An expression is a phrase of code that Python evaluates to produce
#          a value. The simplest expressions are literals and identifiers.
#          You build other expressions by joining subexpressions with the
#          operators and/or delimiters in next Table 4-2. This table lists
#          operators in decreasing order of precedence, higher precedence
#          before lower. Operators listed together have the same precedence.
#          The third column lists the associativity of the operator:
#          L (left-to-right), R (right-to-left), or NA (nonassociative).

'''
  `expr,...`                 String conversion                       NA
  {key:expr,...}             Dictionary creation                     NA
  [expr,...]                 List creation                           NA
  (expr,...)                 Tuple creation or just parantheses      NA
  f(expr,...)                Function call                           L
  x[index:index]             Slicing                                 L
  x[index]                   Indexing                                L
  x.attr                     Attribute reference                     L
  x**y                       Exponentiation (x to yth power)         R
  ~x                         Bitwise NOT                             NA
  +x,-x                      Unary plus and minus                    NA
  x*y, x/y, x//y, x%y        Mutiplication, division, truncating     L
                             division, remainder
  x+y, x-y                   Addition, subtraction                   L
  x<<y, x>>y                 Left-shift, right-shift                 L
  x&y                        Bitwise AND                             L
  x^y                        Bitwise XOR                             L
  x|y                        Bitwise OR                              L
  x<y, x<=y, x>y x>=y        Comparisons (less than, less than or    NA
  x<>y, x!=y, x==y           equal, greater than, greater than or
                             equal, inequality, equality)
  x is y, x is not y         Identity tests                          NA
  x in y, x not in y         Membership tests                        NA
  not x                      Boolean NOT                             NA
  x and y                    Boolean AND                             L
  x or y                     Boolean OR                              L
  lambda arg,...:expr        Anonymous simple function               NA
'''

# *** Expressions and other Operators ***
a = `222, str`          # string conversion: a= (222, <type 'str'>)
print "string conversion a=", a

a = {1: 3.14, 2: 4.14}  # dictionary creation
a = [3.14, 4.14]        # list creation
a = (3.14, 4.14)        # tuple creation

def func(a):
    print a
func("show this")       # funcion call
b = a[0:1]              # slicing
print "slicing a[0:1]= ", b
b = a[1]                # indexing
print "indexing a[1]= ", b

# attributes
# exponentiation
# bitwise NOT
# unary plus
# unary minus
# multiplication
# division
# truncating division
# remainder
# addition
# subtraction
# left-shift
# right-shift
# bitwise AND
# bitwise XOR
# bitwise OR
# less than
# less than or equal
# greater than
# greater than or equal
# inequality
# equality

# Comparison chaining
a = 5
b = 15
c = 20
d = 21
e = a < b <= c < d
print "a < b <= c < d is ", e  # prints: ... is True

# Short-Circuiting Operators
#      if expr1 and expr2:   -> if expr1 is False, expr2 is not executed
def expr2():
    print "If you see this then it is an error"
    return True

if a == 200 and expr2():
    print "If you see this then it is an error"

# identity test
# membership test
# boolean NOT
# boolean AND
# boolean OR
# anonymous function

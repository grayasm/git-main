#!/usr/bin/env python
# -*- coding: utf-8 -*-

# -----------------------------------------------------------------------------
# Expressions and other Operators
a = `222, str`          # string conversion
print a

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

''' I will shortly mention all the other as they look trivial:

x.attr
x**y
~x
+x, -x
x*y, x/y, x//y, x%y
x+y, x-y
x<<y, x>>y
x&y
x^y
x|y
x<y, x<=y, x>y, x>=y, x<>y, x!=y, x==y
x is y, x is not y
not x
x and y
x or y
lambda arg, ...:expr
'''

# Comparison chaining
a = 5
b = 15
c = 20
d = 21
e = a < b <= c < d
print "a < b <= c < d is ", e

# Short-Circuiting Operators
#      if expr1 and expr2:   -> if expr1 is False, expr2 is not executed
def expr2():
    print "If you see this is an error"
    return True

if a == 200 and expr2():
    print "If you see this is an error"


# Numeric Operations
a = 1j                  # imaginary part
b = 2j                  # imaginary part
c = a * b
print "1j * 2j = ", c

a = 2 + 4j              # real + imaginary part
b = complex(2, 4)
print "a.real = ", a.real
print "a.imag = ", a.imag
print "a.conjugate() = ", a.conjugate()
print "abs(2+4j)= ", abs(a)
print "2 + 4j == complex(2, 4) is ", a == b


# Numeric Conversion
a = "545.2222"
print "float(", a, ")= ", float(a)
print "int(float(", a, ")=", int(float(a))

# http://stackoverflow.com/questions/379906/parse-string-to-float-or-int
def isfloat(val):
    try:
        float(val)
        return True
    except:
        return False

# Command to parse                   isFloat?   Note
# --------------------------------  --------   ---------------------------
print isfloat("")                   # False      Blank string
print isfloat("127")                # True       Passed string
print isfloat(True)                 # True       Pure sweet Truth
print isfloat("True")               # False      Vile contemptible lie
print isfloat(False)                # True       So false it becomes true
print isfloat("123.456")            # True       Decimal
print isfloat("      -127    ")     # True       Spaces trimmed
print isfloat("\t\n12\r\n")         # True       whitespace ignored
print isfloat("NaN")                # True       Not a number
print isfloat("NaNanananaBATMAN")   # False      I am Batman
print isfloat("-iNF")               # True       Negative infinity
print isfloat("123.E4")             # True       Exponential notation
print isfloat(".1")                 # True       mantissa only
print isfloat("1,234")              # False      Commas gtfo
print isfloat(u'\x30')              # True       Unicode is fine.
print isfloat("NULL")               # False      Null is not special
print isfloat(0x3fade)              # True       Hexidecimal
print isfloat("6e7777777777777")    # True       Shrunk to infinity
print isfloat("1.797693e+308")      # True       This is max value
print isfloat("infinity")           # True       Same as inf
print isfloat("infinityandBEYOND")  # False      Extra characters wreck it
print isfloat("12.34.56")           # False      Only one dot allowed
print isfloat(u'四')                # False      Japanese '4' is not a float.
print isfloat("#56")                # False      Pound sign
print isfloat("56%")                # False      Percent of what?
print isfloat("0E0")                # True       Exponential, move dot 0 places
print isfloat(0**0)                 # True       0___0  Exponentiation
print isfloat("-5e-5")              # True       Raise to a negative number
print isfloat("+1e1")               # True       Plus is OK with exponent
print isfloat("+1e1^5")             # False      Fancy exponent not interpreted
print isfloat("+1e1.3")             # False      No decimals in exponent
print isfloat("-+1")                # False      Make up your mind
print isfloat("(1)")                # False      Parenthesis is bad

# Sequence Operations
#    * operations on string "", tuple (), list []
a = [0, 1, 2, 3]

print a, " has len= ", len(a)               # len
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

#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# pag. 33, Lexical Structure
#          The lexical structure of a programming langugage is the set of
#          basic rules that govern how to write programs in that language.
#          It is the lowest-level syntax of the language and specifies
#          such things as what variable names look like and which characters
#          denote comments. Python is very particular about program layout
#          especially with regard to lines and identation, so you'll want
#          to pay attention to this information if you are coming to Python
#          from another language.

from __future__ import division  # see the Operators section.


# *** Lines and Identation ***

# this is a comment

print ("followed by a comment")  # all after are part of the comment

    # 'blank-line' (spaces followed by a comment) is ignored

print ("this statement is too long \
to fit into a single line")

print ("( or { or [ join adjacent physical lines %s <-> %s" % ("line",
                                                              "another line"))

str = '''tripple-quoted string literals
can also span physical lines'''
print ("str=%s" % str)

var1 = 1 + 2 + \
       3 + 1 + \
       2 + 1
print ("continuation lines with var1= %d" % var1)


def f():
    print ("Python uses identation to express the block structure")
    var2 = 2 + 1 + \
           3 + 1
    print ("of a program, here var2 = %d" % var2)
    f()


# *** Character Sets ***
# see the second line after shebang

# Identifiers: variable, function, Class, module or other object.
#              [A-Za-z_] + [0-9][A-Za-z_]


# *** Keywords ***
#    see http://www.programiz.com/python-programming/keyword-list
#
#         and        del       for      is         raise
#         assert     elif      from     lambda     return
#         break      else      global   not        try
#         class      except    if       or         while
#         continue   exec      import   pass       with (2.5)
#         def        finally   in       print      yield
#         as         False     True     None       nonlocal (3.0)


# 'True' 'False' 'None' which represents the null value (absence value)
print (" 1 == 1 %s" % (1 == 1))
print (" 10 < 1 %s" % (10 < 1))
var2 = None
print (" var2 = %s" % var2)


def a_void_function():
    a = 1
    b = 2
    c = a + b
    var3 = a_void_function()
    print (" var3 = %s" % var3)         # return 'None' (default)


def improper_return_function(a):
    if (a % 2) == 0:
        return True

var4 = improper_return_function(3)
print (" var4 = %s" % var4)             # programming error

print (" True and False is %s" % (True and False))
print (" True or False  is %s" % (True or False))
print (" not True       is %s" % (not True))


# 'as'
import math as myAlias
print ("cos(pi) is %.2f" % myAlias.cos(myAlias.pi))

# 'assert'
assert 10 < 11, "my error message"


# 'for' 'if' 'break' 'continue'
for i in range(1, 11):
    if i == 5:
        break
    if i == 3:
        continue
    print (i)


# 'class' 'def' user defined function
class ExampleClass:
    def function1(parameter):
        None

    def function2(parameter):
        None

# 'del' - delete a reference to an object
var5 = var6 = 5
del var5

# everything in python is an object
# var5 does not exist anymore
# NameError: name 'var5' is not defined


# this is a list, don't know why it's here :)
var7 = ['x', 'y', 'z']
del var7[1]
print (var7)         # prints: ['x', 'z']


# 'if' 'elif' 'else'
def if_example(a):
    if a == 1:
        print ("One")
    elif a == 2:
        print ("Two")
    else:
        print ("> than Two")

if_example(2)
if_example(4)
if_example(1)


# 'try' 'except'
def reciprocal(num):
    try:
        r = 1/num
    except:
        print ('Exception caught')
        return
    return r

print (reciprocal(10))
print (reciprocal(0))


# 'finally' - gets executed even if there is an exception
def with_finally(a):
    try:
        r = 1/a
    except SyntaxError:
        print ("except SyntaxError:")
    except NameError:
        print ("except NameError:")
    finally:
        print ("finally")
    return r

print (with_finally(1))


# 'for'
var8 = ['John', 'Monica', 'Steven', 'Robin']
for i in var8:
    print ('Hello ' + i)


# 'from'
from math import cos


# 'global'
# A variable declared global inside a function refers to a variable
# defined outside; If not declared global, Python will create a local
# variable instead.
var9 = 10


def read1():
    print (var9)


def write1():
    global var9
    var9 = 5


def write2():
    var9 = 15

read1()   # prints: 10
write1()
read1()   # prints: 5
write2()
read1()   # prints: 5


# 'in'
# Used to test if a sequence (list, tuple, string etc) contains a value
var10 = [1, 2, 3, 4, 5]
print ("5 in %s is %s" % (var10, 5 in var10))


# 'is'
# Used to test if 2 variables refer to the same object, where == operator
# is used to test if 2 variables are equal or not.
# It returns True if objects are identical and False if not.

print ("True is True = %s" % (True is True))  # True is one instance in Python
print ("False is False = %s" % (False is False))
print ("None is None = %s" % (None is None))
print ("[] == [] =  %s" % ([] == []))         # Equal
print ("[] is [] =  %s" % ([] is []))         # but not identical
print ("{} == {} =  %s" % ({} == {}))         # Equal
print ("{} is {} =  %s" % ({} is {}))         # but not identical

print ("'' == '' =  %s" % ('' == ''))         # unlike list and dict, string
print ("'' is '' =  %s" % ('' is ''))         # and tuple are immutable
print ("() == () =  %s" % (() == ()))
print ("() is () =  %s" % (() is ()))


# 'lambda'
# Used to create an anonymous function (function with no name)
# It is an inline function that does not contain a return statement.
func11 = lambda x: x*2
for i in range(1, 6):
    print ("lambda(%d)= %d" % (i, func11(i)))


# 'nonlocal'
# Used to declare that a variable inside a nested function (function
# inside a function) is not local to it, meaning it lies in the
# outer inclosing function. Does not work in python-2.7

'''def outer_function():
    a = 5

    def inner_function():
        nonlocal a
        a = 10
        print "Inner function: %d " % a
    inner_function()
    print "Outer function: %d" % a

outer_function()'''


# 'pass'
# A null statement (placeholder).
# Nothing happens when executed.
def function(args):
    pass


# 'return'
# Used inside a function to exit it and return a value. If no value
# is return explicitly, None is returned automatically.

def func_return():
    a = 10
    return a


def no_return():
    a = 10

print (func_return())
print (no_return())


# 'while'
# Used for looping until False or a break is encountered.
var12 = 5
while (var12):                   # 0 evaluated to False
    print (var12)
    var12 = var12 - 1


# 'with'
#  Used to wrap the execution of a block of code within methods defined
#  by the context manager which implements __enter__ and __exit__

with open('/tmp/test_python_can_delete_this.txt', 'w') as my_file:
    my_file.write('Hello world!')


# 'yield'
# Used inside a function like a return statement.
# It returns a generator, which is an iterator that generates one item at
# a time. It generates one value at a time instead of storing all the values
# in memory.
def generator():
    for i in range(6):
        yield i*i

var13 = generator()
for i in var13:
    print (i)


# -----------------------------------------------------------------------------
# Operators  (see http://www.programiz.com/python-programming/operators)
#
#                +   -   *   /    %    **   //   <<   >>   &
#                |   ^   ~   <    <=   >    >=   <>   !=   ==

# arithmetic operators: +  -  *  /  %  //  **
x = 15
y = 4

print ("%d + %d = %d" % (x, y, x+y))
print ("%d - %d = %d" % (x, y, x-y))
print ("%d * %d = %d" % (x, y, x*y))

# In python-2.7  / is integer division if inputs are integers.
# For float must use special import:
#
# from __future__ import division
#
print ("%d / %d = %f" % (x, y, x/y))
print ("%d modulo %d = %d" % (x, y, x % y))
print ("%d // %d = %f" % (x, y, x//y))  # floor division, adjusted to the left
print ("%d ** %d = %f" % (x, y, x**y))  # left rised to the power of right


# comparison operators: >  <  ==  !=  >=  <=
x = 10
y = 12
print ("%d > %d is %s" % (x, y, x > y))
print ("%d < %d is %s" % (x, y, x < y))
print ("%d == %d is %s" % (x, y, x == y))
print ("%d != %d is %s" % (x, y, x != y))
print ("%d >= %d is %s" % (x, y, x >= y))
print ("%d <= %d is %s" % (x, y, x <= y))


# logical operators: and, or, not
x = True
y = False
print ("%s and %s is %s" % (x, y, x and y))
print ("%s or %s is %s" % (x, y, x or y))
print ("not %s is %s" % (x, not x))


# bitwise operators
x = 0b00001010 # 0000 1010 = 10 decimal
y = 0b00000100 # 0000 0100 =  4 decimal

print ("%d & %d = %d" % (x, y, x & y))    # bitwise AND
print ("%d | %d = %d" % (x, y, x | y))    # bitwise OR
print ("~ %d    = %d" % (x, ~x))          # bitwise NOT
print ("%d ^ %d = %d" % (x, y, x ^ y))    # bitwise XOR
print ("%d >> 2 = %d" % (x, x >> 2))      # bitwise right shift
print ("%d << 2 = %d" % (x, x << 2))      # bitwise left shit


# assignament operators
x = 100   # 100
x += 50   # 150
x -= 5    # 145
x *= 2    # 290
x /= 10   # 29
x %= 19   # 10
x //= 3   # 3
x **= 4   # 81
print ("81 must be %d" % x)

x = 0b01010001
x &= 5
x |= 5
x ^= 5
x >>= 5
x <<= 5
print ("x = %d" % x)


# identity operators: is, is not
x1 = 5
y1 = 5
x2 = 'Hello'
y2 = 'Hello'
x3 = [1, 2, 3]
y3 = [1, 2, 3]
print ("%d is not %d = %s" % (x1, y1, x1 is not y1))
print ("%s is %s = %s" % (x2, y2, x2 is y2))
print ("%s is %s = %s" % (x3, y3, x3 is y3))


# membership operators
x = 'Hello world'
y = {1: 'a', 2: 'b'}

print ("'H' in %s = %s" % (x, ('H' in x)))
print ("'hello' not in %s = %s" % (x, 'hello' not in x))
print ("1 in %s = %s" % (y, (1 in y)))
print ("'a' in %s = %s" % (y, ('a' in y)))


# *** Literals***
# Is a number or string that appears directly in a program


42                          # Integral literal
3.14                        # Floating-point literal
1.0j                        # Imaginary literal
'hello'                     # String literal
"world"                     # Another string literal
"""Good
night"""

[42, 3.14, 'hello']         # List
(100, 200, 300)             # Tuple
{'x': 42, 'y': 3.14}        # Dictionary

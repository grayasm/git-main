#!/usr/bin/env python
# -*- coding: utf-8 -*-


# pag. 70, Functions
#          A function is a group of statements that execute upon request.
#          In Python, a function always returns a result value, either None
#          or a value that represents the result of the computation.
#          Functions defined within class statement are also known as methods.
#          In Python, functions are objects (values) that are handled like
#          other objects. Thus, you can pass a function as an argument in a
#          call to another function. Similarly, a function can return another
#          function as the result of a call. A function, just like any other
#          object, can be bound to a variable, an item in a container, or an
#          attribute of an object.Functions can also be keys into a dictionary.
#          The fact that functions are ordinary objects in Python is often
#          expressed by saying that functions are first-class objects.


# *** The 'def' Statement ***
def double(x):
    return x*2


# *** Parameters ***
#    * mandatory and optional parameters
def f(x, y=[]):
    y.append(x)
    return y
print f(23)          # prints: [23]
print f(42)          # prints: [23, 42]


def f(x, y=None):
    if y is None:
        y = []
    y.append(x)
    return y
print f(23)          # prints: [23]
print f(42)          # prints: [23]


# *** Attributes of Function Objects ***
def power(x, y):
    return x**y

# function attribute: func_name
print power.func_name               # power

# function attribute: __name__
print power.__name__                # power


# function attribute: func_doc or __doc__
def sum_args(*numbers):
    '''Accept arbitrary numerical arguments and return their sum.
    The arguments are zero or more numbers. The result is their sum.'''
    return sum(numbers)

print sum_args(1, 2, 3)             # 6
print sum_args.func_doc             # Accept arbitrary numerical ...
print sum_args.__doc__              # Accept arbitrary numerical ...


# custom attributes
def counter():
    counter.count += 1
    return counter.count
counter.count = 0           # count how many times the function is called
counter()
counter()
print counter.count         # 2


# *** The 'return' Statement ***
def no_return():
    '''Implicit return value is None'''

print no_return()           # None

def Fun001(x):
    return x

print Fun001(100.1)         # 100.1


# *** Calling Functions ***

# The semantic argument passing
#    - there are 2 concepts related to passing parameters to a function
#    1) rebinding the caller's variables (immutable objects, like numbers)
#    2) mutating the caller's variables (mutable objects, like lists)
# example:
def f(x, y):
    x = 23
    y.append(42)
a = 77
b = [99]
f(a, b)
print a, b                  # prints: 77 [99, 42]


# Kind of arguments
#    * can pass any expression (positional arguments)
def divide(divisor, dividend):
    return dividend // divisor
print divide(12, 94)                   # prints: 7
print divide(dividend=94, divisor=12)  # prints: 7 (see the flip)


# *** Namespaces ***
#    A function's parameters, plus any variables that are bound (by assignment
#    or by other binding statements, such as def) in the function body, make
#    up the function's local namespace, also known as local scope. Each of
#    these variables is known as a local variable of the function.
#    Variables that are not local are known as global variables (in the absence
#    of nested function definitions, which we'll discuss shortly). Global
#    variables are attributes of the module object, as covered in
#    *** Attributes of module objects ***. Whenever a function's local variable
#    has the same name as a global variable, that name, within the function
#    body, refers to the local variable, not the global one. We express this by
#    saying that the local variable hides the global variable of the same name
#    throughout the function body.


# The 'global' Statement
_count = 0
def counter():
    global _count
    _count += 1
    return _count

print "_count=", counter()              # _count= 1
print "_count=", counter()              # _count= 2

# Nested functions and nested scope

# ex: nested function with optional argument
def percent1(a, b, c):
    def pc(x, total=a+b+c):
        return (x*100.0) / total
    print "Percentages are:", pc(a), pc(b), pc(c)

percent1(1, 3, 6)                       # Percentages are: 10.0 30.0 60.0


# ex: nested function with nested scope
def percent2(a, b, c):
    def pc(x):
        return (x*100.0) / (a+b+c)
    print "Percentages are:", pc(a), pc(b), pc(c)

percent2(1, 3, 6)                       # Percentages are: 10.0 30.0 60.0


# - a function that accesses values from outer local variables is also known as
#   a closure.
def outer2(a):
    def inner2(b):
        return a + b
    return inner2

add1 = outer2(1)
print "add1(4)=", add1(4)               # add1(4)= 5
print "add1(5)=", add1(5)               # add1(5)= 6

add2 = outer2(2)
print "add2(4)=", add2(4)               # add2(4)= 6
print "add2(5)=", add2(5)               # add2(5)= 7

# *** 'lambda' Expressions ***
#   - if a function body is a single return statement, you may choose to
#     replace the function with a special lambda expression form:
#   syntax:  lambda parameters: expression
def f(x): return x**2
print "f(x)= ", f(8)                    # 64

g = lambda x: x**2
print "g(x)= ", g(8)                    # 64

def make_incrementor(n): return lambda x: x + n
f = make_incrementor(2)
g = make_incrementor(6)
print "f(42)= %d , g(42)= %d" % (f(42), g(42))  # f(42)= 44 , g(42)= 48
print "make_incrementor(22)(33)= ", make_incrementor(22)(33)  # 55


#    - lambda with built-in filter function
#      (see https://docs.python.org/2/library/functions.html#filter)
aList = [1, 2, 3, 4, 5, 6, 7, 8, 9]
low = 3
high = 7
filter(lambda x, l=low, h=high: h > x > l, aList)  # returns: [4, 5, 6]

# or as normal function:
aList = [1, 2, 3, 4, 5, 6, 7, 8, 9]
low = 3
high = 7

def within_bounds(value, l=low, h=high):
    return h > value > l

filter(within_bounds, aList)                       # return: [4, 5, 6]


# *** Generators ***
#    When a body of a function contains one or more occurences of the keyword
#    yield, the function is known as a generator. When you call a generator,
#    the function body does not execute. Instead, calling the generator returns
#    a special iterator object that wraps the function body, its local
#    variables (including its paramters), and the current point of execution,
#    which is initially the start of the function.
#    When the next method of this iterator object is called, the function body
#    executes up to the next yield statement, which takes the form:
#        yield expression
#
#    When a yield statement executes, the function execution is "frozen" with
#    current point of execution and local variables intact, and the expression
#    following yield is returned as the result of the next method. When next
#    is called again, execution of the function body resumes where it left off,
#    again up to the next yield statement. If the function body ends, or
#    executes a return statement, the iterator raises a StopIteration exception
#    to indicate that the iteration is finished. return statements in a
#    generator cannot contain expressions.
#
#    syntax: yield expression

def updown(N):
    for x in xrange(1, N):
        yield x
    for x in xrange(N, 0, -1):
        yield x

for i in updown(3):
    print i               # prints: 1 2 3 2 1

# another generator that works like built-in xrange function
def frange(start, stop, step=1.0):
    while start < stop:
        yield start
        start += step

for i in frange(1, 4):
    print i,              # prints: 1 2.0 3.0


# Generator expressions
#    - as example is given the list comprehension idiom

b = [i for i in range(10) if i > 2 and i < 8]   # [3, 4, 5, 6, 7]
print "\ngenerator expression, b=", b

# *** Recursion ***
#    - a limit of 1000 recursive calls, raises MaximRecursionDepthExceeded
#    - can be changed with setrecursionlimit of module sys

def recurse(x):
    if x > 0:
        return x + recurse(x-1)
    return x

print "recurse(5)=", recurse(5)                 # recurse(3)= 15

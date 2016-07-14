# -----------------------------------------------------------------------------
# Functions
#
#    * a function always returns a value or None
#    * functions are objects that are handled like other objects
#    * can pass a function as argument to another function


# The def Statement
def double(x):
    return x*2


# Parameters
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


# Attributes of Function Objects
def power(x, y):
    return x**y

# function attribute: func_name
print power.func_name

# function attribute: __name__
print power.__name__


# function attribute: func_doc or __doc__
def sum_args(*numbers):
    '''Accept arbitrary numerical arguments and return their sum.
    The arguments are zero or more numbers. The result is their sum.'''
    return sum(numbers)

print sum_args(1, 2, 3)
print sum_args.func_doc
print sum_args.__doc__


# custom attributes
def counter():
    counter.count += 1
    return counter.count
counter.count = 0           # count how many times the function is called
counter()
counter()
print counter.count         # 2


# The return Statement

# The semantic argument passing
#    - there are 2 concepts related to passing parameters to a function
#    1) rebinding the caller's variables (immutable objects, like numbers)
#    2) mutating the caller's variables (mutable objects)
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


# Namespaces
#    * def = function body = local namespace = local scope
#    * variables that are not local are global (when not nested)


# The global Statement
_count = 0


def counter():
    global _count
    _count += 1
    return _count


# Nested functions and nested scope

# ex: nested function with optional argument
def percent1(a, b, c):
    def pc(x, total=a+b+c):
        return (x*100.0) / total
    print "Percentages are:", pc(a), pc(b), pc(c)

percent1(1, 3, 6)


# ex: nested function with nested scope
def percent2(a, b, c):
    def pc(x): return (x*100.0) / (a+b+c)
    print "Percentages are:", pc(a), pc(b), pc(c)

percent2(1, 3, 6)


# nested function known as closure
def decorate(f):
    def wrapped_function():
        print "Function is begin called"
        f()
        print "Function call is finished"
    return wrapped_function


@decorate
def f1():
    print "Hello world!"

f1()


# lambda Expressions
#   - if a function body is a single return statement, you may choose to
#     replace the function with a special lambda expression form:
#   syntax:  lambda parameters: expression

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


# Generators
#    - when a function contains one or more yield keyword is a generator
#    - it returns a special iterator that wraps the function body
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
    print i               # prints: 1 2.0 3.0


# Generator expressions
#    - as example is given the list comprehension idiom

b = [i for i in range(10) if i > 2 and i < 8]   # [3, 4, 5, 6, 7]


# Recursion
#    - a limit of 1000 recursive calls, raises MaximRecursionDepthExceeded
#    - can be changed with setrecursionlimit of module sys

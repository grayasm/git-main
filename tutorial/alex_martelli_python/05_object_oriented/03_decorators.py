#!/usr/bin/env python3
# -*- coding: utf-8 -*-

#
# pag. 115, Decorators
#           Due to the existance of descriptor types such as
#           staticmethod and classmethod, covered in "Class-Level Methods" on
#           page 99, which takes their argument a function object, Python
#           somewhat frequently uses, within class bodies, idioms such as:
#           def f(cls, ...):
#               ...definition of f snipped...
#           f = classmethod(f)
#
#           Having the call to classmethod occur textually after the def
#           statement may decrease code readability because, while reading
#           f's definition, the reader of the code is not yet aware that f
#           is destined to become a class method rather than an ordinary
#           instance method. The code would be more readable if the mention
#           of classmethod could be placed right before, rather than after
#           the def. Python 2.4 allows such placement, through the new syntax
#           known as decoration:
#           @classmethod
#           def f(cls, ...):
#               ...definition of f snipped...
#
#           The @classmethod decoration must be immediately followed by a def
#           statement and means that f=classmethod(f) executes right after
#           the def statement (for whatever name f the def defines). More
#           generally, @expression evaluates the expression (which must be a
#           name, possibly qualified, or a call) and binds the result to an
#           internal temporary name (say, __aux); any such decoration must
#           be immediately followed by a def statement and means that f=__aux(f)
#           executes right after the def statement. The object bound to __aux
#           is known as a decorator, and it's said to decorate function f.


# Example for 'classmethod' or 'staticmethod'

class Classic(object):
    def double(x):
        return x*2
    double = classmethod(double)

# a decorator calls a function with the same name right after the decorated
# block.

class Decorated(object):
    @classmethod
    def double(x):
        return x*2


# or this example:
def showdoc(f):
    if f.__doc__:
        print '%s: %s' % (f.__name__, f.__doc__)
    else:
        print '%s: No docstring!' % f.__name__
    return f


@showdoc
def f1(): "a docstring"      # prints: f1: a docstring

@showdoc
def f2(): pass               # prints: f2: No docstring!

#!/usr/bin/env python3
# -*- coding: utf-8 -*-

#
# pag. 134, Error-Checking Strategies
#           Most programming languages that support exceptions are geared to
#           raise exceptions only in rare cases. Python's emphasis is
#           different. In Python, exceptions are considered appropriate
#           whenever they make a program simpler and more robust, even if that
#           means that exceptions are raised rather frequently.


# *** LBYL Versus EAFP ***
# A common idiom in other languages, sometimes known as "look before you leap"
# (LBYL) is to check in advance, before attempting an operation, for all
# circumstances that might make the operation invalid.
# The preffered idiom in Python is generally to attempt the operation in a
# try clause and handle the exceptions that may result in except clauses.
# This idiom is known as "it's easier to ask for forgiveness than permission"
# (EAFP)


def save_divide_1(x, y):
    if y == 0:
        return None
    else:
        return x / y


def safe_divide_2(x, y):
    try:
        return x / y
    except ZeroDivisionError:
        return None


# Proper usage of EAFP
def trycalling(obj, attrib, default, *args, **kwds):
    try:
        method = getattr(obj, attrib)
    except AttributeError:
        return default
    else:
        return method(*args, **kwds)


# *** Handling Errors in Large Programs ***
# *** Logging Errors ***

import logging
import sys
logging.basicConfig(stream=sys.stdout, level=logging.DEBUG)


try:
    1 / 0
except Exception, e:
    logging.exception("message")

# ERROR:root:message
# Traceback (most recent call last):
#   File "06_error_checking.py", line 39, in <module>
#     1 / 0
# ZeroDivisionError: integer division or modulo by zero



# *** The 'assert' Statement ***
# If condition is True, does nothing.
# If condition is False then rises AssertionError with expression as arg.
'''
assert condition[,expression]
'''

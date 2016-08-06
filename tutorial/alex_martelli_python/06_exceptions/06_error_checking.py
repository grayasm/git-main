#
# *** Error-Checking Strategies ***
#
# 1) Check first for error condition (LBYL look bef you leap) or
# 2) Execute and cach exception (EAFP easier to ask forgivenss than permis)
#


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

# Logging Errors
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


# The 'assert' Statement
#
# If condition is True, does nothing.
# If condition is False then rises AssertionError with expression as arg.
'''
assert condition[,expression]
'''

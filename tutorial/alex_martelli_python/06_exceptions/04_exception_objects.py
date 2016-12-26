#!/usr/bin/env python3
# -*- coding: utf-8 -*-

#
# pag. 129, Exception Objects
#           Exceptions are instances of subclasses of the built-in,
#           legacy-style Exception class. An instance of any subclass of
#           Exception has an attribute args, the tuple of arguments used
#           to create the instance. args holds error-specific information,
#           usable for diagnostic or recovery purposes.


# *** The Hierarchy of Standard Exceptions ***
# *** Standard Exception Classes ***

# Subclases of the legacy-style 'Exception' class.
# Since 2.5 Exception derives from 'BaseException' new-style exceptions.
#
# Hierarchy in 2.7 (stable)
# https://docs.python.org/2.7/library/exceptions.html#exception-hierarchy
#
'''
BaseException
 +-- SystemExit
 +-- KeyboardInterrupt
 +-- GeneratorExit
 +-- Exception
      +-- StopIteration
      +-- StandardError
      |    +-- BufferError
      |    +-- ArithmeticError
      |    |    +-- FloatingPointError
      |    |    +-- OverflowError
      |    |    +-- ZeroDivisionError
      |    +-- AssertionError
      |    +-- AttributeError
      |    +-- EnvironmentError
      |    |    +-- IOError
      |    |    +-- OSError
      |    |         +-- WindowsError (Windows)
      |    |         +-- VMSError (VMS)
      |    +-- EOFError
      |    +-- ImportError
      |    +-- LookupError
      |    |    +-- IndexError
      |    |    +-- KeyError
      |    +-- MemoryError
      |    +-- NameError
      |    |    +-- UnboundLocalError
      |    +-- ReferenceError
      |    +-- RuntimeError
      |    |    +-- NotImplementedError
      |    +-- SyntaxError
      |    |    +-- IndentationError
      |    |         +-- TabError
      |    +-- SystemError
      |    +-- TypeError
      |    +-- ValueError
      |         +-- UnicodeError
      |              +-- UnicodeDecodeError
      |              +-- UnicodeEncodeError
      |              +-- UnicodeTranslateError
      +-- Warning
           +-- DeprecationWarning
           +-- PendingDeprecationWarning
           +-- RuntimeWarning
           +-- SyntaxWarning
           +-- UserWarning
           +-- FutureWarning
           +-- ImportWarning
           +-- UnicodeWarning
           +-- BytesWarning
'''

try:
    l = []
    assert isinstance(l, tuple)
except AssertionError:
    print "AssertionError"    # prints: AssertionError

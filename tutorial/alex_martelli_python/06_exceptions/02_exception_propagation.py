#!/usr/bin/env python3
# -*- coding: utf-8 -*-

#
# pag. 126, Exception Propagation
#           When an exception is raised, the exception-propagation mechanism
#           takes control. The normal control flow of the program stops, and
#           Python looks for a suitable exception handler. Python's try
#           statement establishes exception handlers via its except clauses.
#           The handler deal with exceptions raised in the body of the try
#           clause, as well as exceptions propagating from any of the functions
#           called by that code, directly or indirectly. If an exception is
#           raised within a try clause that has an applicable except handler,
#           the try clause terminates and the hanlder executes. When the
#           handler finishes, execution continues with the statement after
#           the try statement.
#           If the statement raising the exception is not within a try clause
#           that has an applicable handler, the function containing the
#           statement terminates, and the exception propagates "upward" along
#           the stack of functin calls to the statement that called the
#           function. The propagation process repeats, unwinding the stack
#           of function calls until and applicable handler is found.
#           If no hanlder is found the program prints an error to the standard
#           error stream and goes back to the interactive session if any, or
#           terminates.


def c():
    print "in c, before 1/0"
    1 / 0
    print "in c, after  1/0"


def b():
    print "in b, before c()"
    c()
    print "in b, after  c()"


def a():
    print "in a, before b()"
    try:
        b()
        print "in a, after b()"
    except ZeroDivisionError:
        print "ZD exception caught"
    print "function a ends"


a()       # in a, before b()
          # in b, before c()
          # in c, before 1/0
          # ZD exception caught
          # function a ends

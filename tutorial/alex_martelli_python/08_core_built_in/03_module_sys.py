#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# pag. 168, The sys Module
#           The attributes of the sys module are bound to data and functions
#           that provide information on the state of the Python interpreter
#           or affect the interpreter directly. This section documents the
#           most frequently used attributes of sys, in alphabetical order.

import sys


# The sys Module
#
class A(object):
    pass


a = A()

sys.argv[0]
sys.displayhook(a)
# sys.excepthook(type, value, traceback)
sys.exc_info()
sys.exit()
sys.getdefaultencoding()
sys.getrefcount(a)
sys.getrecursionlimit()
sys._getframe(0)
sys.modules
sys.path
sys.platform
sys.ps1
sys.ps2
# sys.setdefaultencoding(name)
# sys.setprofile(profilefunc)
sys.setrecursionlimit(500)
# sys.settrace(tracefunc)
sys.stdin
sys.stdout
sys.stderr
sys.version

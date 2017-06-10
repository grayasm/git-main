#!/usr/bin/env python3
# -*- coding: utf-8 -*-


'''
The frame Type.
Function _getframe in module sys returns a frame object from Python’s call
stack. A frame object has attributes that supply information about the code
executing in the frame and the execution state. Modules traceback and inspect
help you access and display information, particularly when an exception is
being handled.
'''


# there are a lot of examples here:
# http://www.programcreek.com/python/example/283/sys._getframe

import sys
import os


x = sys._getframe().f_code.co_filename
modpath = os.path.join(os.path.dirname(x), "modules")
print("modpath=", modpath)

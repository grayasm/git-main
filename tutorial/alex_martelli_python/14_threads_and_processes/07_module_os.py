#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import os

print("I will call this other program called 04_module_threading.py")
os.system("python 04_module_threading.py")

cmdpipe = os.popen("uname -a", mode='r')
if cmdpipe is not None:
    str = cmdpipe.readline()
    print('cmdpipe.readline:', str)

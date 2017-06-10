#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# pag. 258, The getpass Module
#           Occasionally, you want the user to input a line of text in such a
#           way that somebody looking at the screen cannot see what the user is
#           typing. This often occurs when you’re asking the user for a
#           password. The getpass module provides the following functions.

'''
getpass    getpass(prompt='Password: ')
getuser    getuser( )
'''

# Using getpass WITH or WITHOUT a terminal.
# run with: python3 script.py  or
#           echo "parola03" | python3 script.py

import getpass
import sys

try:
    if sys.stdin.isatty():
        p = getpass.getpass('Using getpass: ')
    else:
        print('Using readline')
        p = sys.stdin.readline().rstrip()
except Exception as err:
    print('ERROR:', err)
else:
    print('You entered:', p)

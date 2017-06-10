#!/usr/bin/env python3
# -*- coding: utf-8 -*-

'''
Outside of interactive interpreter sessions, there is no automatic per-user
customization. To request per-user customization, a Python main script can
explicitly import user . Standard library module user , when loaded, first
determines the user’s home directory, as indicated by environment variable
HOME (or, failing that, HOMEPATH , possibly preceded by HOMEDRIVE on Windows
systems only). If the environment does not indicate a home directory, user uses
the current directory. If module user finds a file named .pythonrc.py in the
indicated directory, user executes that file, with built-in function execfile,
in module user’s own global namespace.
'''

# better to use a custom script for each application
import os


homedir = os.environ.get('HOME')
if homedir is not None:
    userscript = os.path.join(homedir, '.myapprc.py')
    if os.path.isfile(userscript):
        execfile(userscript)

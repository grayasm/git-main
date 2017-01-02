#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# pag. 259, The readline Module
#           The readline module wraps the GNU Readline Library. GNU Readline
#           lets the user edit text lines during interactive input, and recall
#           previous lines for editing and reentry. When readline is available,
#           Python uses it for all line-oriented input, such as raw_input.
#           The interactive Python interpreter always tries to load readline to
#           enable line editing and recall for interactive sessions.
#           Some readline functions control advanced functionality,
#           particularly history, for recalling lines entered in previous
#           sessions, and completion, for context-sensitive completion of the
#           word being entered.

'''
readline.add_history(s)
readline.clear_history(s)
readline.get_completer()
readline.get_history_length()
readline.parse_and_bind(readline_cmd)
readline.read_history_file(filename='~/.history')
readline.read_init_file(filename=None)
readline.set_completer(f=None)
readline.set_history_length(x)
readline.write_history_file(filename='~/.history')
'''

import atexit
import os
import readline

histfile = os.path.join(os.path.expanduser("~"), ".python_history")
try:
    readline.read_history_file(histfile)
    # default history len is -1 (infinite), which may grow unruly
    readline.set_history_length(1000)
except FileNotFoundError:
    pass

atexit.register(readline.write_history_file, histfile)

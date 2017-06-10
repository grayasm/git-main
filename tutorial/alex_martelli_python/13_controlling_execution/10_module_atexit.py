#!/usr/bin/env python3
# -*- coding: utf-8 -*-


# https://docs.python.org/3/library/atexit.html
'''
The atexit module defines functions to register and unregister cleanup
functions. Functions thus registered are automatically executed upon normal
interpreter termination. atexit runs these functions in the reverse order in
which they were registered; if you register A, B, and C, at interpreter
termination time they will be run in the order C, B, A.
'''


def goodbye(name, adjective):
    print('Goodbye, %s, it was %s to meet you.' % (name, adjective))

import atexit
atexit.register(goodbye, 'Donny', 'nice')

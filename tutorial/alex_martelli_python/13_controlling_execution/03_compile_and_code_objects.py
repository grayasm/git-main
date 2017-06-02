#!/usr/bin/env python3
# -*- coding: utf-8 -*-


# http://stackoverflow.com/questions/22443939/python-built-in-function-compile-what-is-it-used-for

codeobj = compile('x = 2\nprint("X is", x)', 'os', 'exec')
exec(codeobj)

#!/usr/bin/env python3
# -*- coding: utf-8 -*-


'''
As well as by using built-in function compile , you can get a code object via
the func_code attribute of a function or method object. (For the attributes of
code objects, see “Compile and Code Objects” on page 329.) Code objects are not
callable, but you can rebind the func_code attribute of a function object with
the correct number of parameters in order to wrap a code object into callable
form.
'''


def g(x): print('g', x)
code_object = g.__code__  # func_code in python2
def f(x): pass
f.__code__ = code_object
f(23)
# emits g 23

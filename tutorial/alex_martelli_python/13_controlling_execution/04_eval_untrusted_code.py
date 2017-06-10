#!/usr/bin/env python3
# -*- coding: utf-8 -*-


def safe_eval(s):
    code = compile(s, '<user-entered string>', 'eval')
    if code.co_names:
        raise ValueError('No names (%r) allowed in expression (%r)' %
                         (code.co_names, s))
    return eval(code)


'''
A code object has a read-only attribute co_names , which is the tuple of the
names used in the code. For example, say that you want the user to enter an
expression that contains only literal constants and operators-no function calls
nor other names. Before evaluating the expression, you can check that the
string the user entered satisfies these constraints:
'''

code = '22 / 7'
safe_eval(code)

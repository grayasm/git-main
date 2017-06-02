#!/usr/bin/env python3
# -*- coding: utf-8 -*-


code = """
print(type({}))
print(type(1.3))
print(type(list()))
"""
codeobj = compile(code, filename='os', mode='exec')
exec(codeobj)

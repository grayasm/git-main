#!/usr/bin/env python3
# -*- coding: utf-8 -*-


import pdb


def f():
    for i in range(1000):
        g(i)


def g(i):
    print(i)


pdb.run('f()')

# pdb interactive commands: next, continue

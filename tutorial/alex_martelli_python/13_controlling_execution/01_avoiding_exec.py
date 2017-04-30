#!/usr/bin/env python3
# -*- coding: utf-8 -*-


# http://stackoverflow.com/questions/1463306/how-does-exec-work-with-locals

def f():
    a = 1
    exec("a = 3")
    print(a)


f()  # prints a:1 not 3


def g():
    a = 1
    ldict = locals()
    print(ldict)                    # prints {a:1,}
    exec("a=3", globals(), ldict)
    print(a)                        # prints a:1
    a = ldict['a']
    print(a)                        # prints a:3


g()

'''exec pries loose your control on your code’s namespace, damages your
program’s performance, and exposes you to numerous, hard-to-find bugs.'''

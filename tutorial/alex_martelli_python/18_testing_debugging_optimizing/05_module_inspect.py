#!/usr/bin/env python3
# -*- coding: utf-8 -*-


from inspect import signature


def foo(a, *, b: int, **kwargs):
    pass


sig = signature(foo)

print(str(sig))
print(str(sig.parameters['b']))
print(sig.parameters['b'].annotation)

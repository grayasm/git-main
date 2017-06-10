#!/usr/bin/env python3
# -*- coding: utf-8 -*-


'''
The gc module exposes the functionality of Python’s garbage collector.
gc deals only with objects that are unreachable in a subtle way, being part of
mutual reference loops. In such a loop, each object in the loop refers to
others, keeping the reference counts of all objects positive. However, no
outside references to any one of the set of mutually referencing objects exist
any longer. Therefore, the whole group, also known as cyclic garbage, is
unreachable, and therefore garbage-collectable.
'''

import gc


gc_was_enabled = gc.isenabled()
if gc_was_enabled:
    gc.collect()
    gc.disable()

# insert some time-critical code here
s = "some time critical code"
print(s)

if gc_was_enabled:
    gc.enable()

#!/usr/bin/env python3
# -*- coding: utf-8 -*-

'''
MA supports masked arrays (i.e., arrays that can have missing or invalid
values). MA supplies a large subset of Numeric ’s functionality, albeit
sometimes at reduced speed. MA also lets you associate to each array an
optional mask, which is an auxiliary array of Booleans, where True indicates
array elements that are missing, unknown, or invalid. Computations propagate
masks; you can turn masked arrays into plain Numeric ones by supplying a
fill-in value for invalid elements. MA is widely applicable because
experimental data often has missing or inapplicable elements. Should you need
to extend or specialize some aspect of Numeric ’s behavior for your
application’s purposes, it may be simplest and most effective to start with
MA ’s sources rather than with Numeric ’s. The latter are often quite hard to
understand and modify due to the degree of optimization applied to them over
the years.
'''

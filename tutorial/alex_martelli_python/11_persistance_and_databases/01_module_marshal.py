#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# pag. 278, The marshal Module
#           The marshal module supports the specific serialization tasks needed
#           to save and reload compiled Python files (.pyc and .pyo).
#           marshal handles only fundamental built-in data types: None,
#           numbers (int, long, float, complex), strings (plain and Unicode),
#           code objects, and built-in containers (tuple, list, dict) whose
#           items are instances of elementary types.
#           marshal does not handle sets nor user-defined types and classes.
#           marshal is faster than other serialization modules, and is the one
#           such module that supports code objects.

#    https://docs.python.org/3/library/marshal.html
#    Warning: The marshal module is not intended to be secure against erroneous
#             or maliciously constructed data. Never unmarshal data received
#             from an untrusted or unauthenticated source.

import marshal

value = (
    "this is a string",
    [1, 2, 3, 4],
    ("more tuples", 1.0, 2.3, 4.5),
    "this is yet another string"
    )

data = marshal.dumps(value)

# intermediate format
print (type(data), len(data))

print ("-"*50)
print (repr(data))
print ("-"*50)

print (marshal.loads(data))

#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# pag. 197, The pprint Module
#           The pprint module pretty-prints complicated data structures, with
#           formatting that may be more readable than that supplied by built-in
#           function repr (covered in repr on page 166).
#           To fine-tune the formatting, you can instantiate the PrettyPrinter
#           class supplied by module pprint and apply detailed control, helped
#           by auxiliary functions also supplied by module pprint.
#           Most of the time, however, one of the two main functions exposed by
#           module pprint suffices.


#    Data pretty printer
#    https://docs.python.org/3.6/library/pprint.html#module-pprint

import pprint

l = ['michigan', 'detroit', 'chicago', 'sidney']
l.insert(0, ['new-york', 'mississippi', 'atlanta'])
l.insert(-1, ['baghdad', 'ankara', 'teheran'])
pp = pprint.PrettyPrinter(indent=4)  # to spot nesting easier
pp.pprint(l)

#[   ['new-york', 'mississippi', 'atlanta'],
#    'michigan',
#    'detroit',
#    'chicago',
#    ['baghdad', 'ankara', 'teheran'],
#    'sidney']

'''
pprint.pformat(obj)
pprint.pprint(obj, stream=sys.stdout)
'''

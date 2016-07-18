#!/usr/bin/python -tt
# -*- coding: utf-8 -*-

#
# The pprint Module
#
# https://docs.python.org/2/library/pprint.html#module-pprint

import pprint

l = ['michigan', 'detroit', 'chicago', 'sidney']
l.insert(0, ['new-york', 'mississippi', 'atlanta'])
l.insert(-1, ['baghdad', 'ankara', 'teheran'])
pp = pprint.PrettyPrinter(indent=4)  # to spot nesting easier
pp.pprint(l)

'''
pprint.pformat(obj)
pprint.pprint(obj, stream=sys.stdout)
'''

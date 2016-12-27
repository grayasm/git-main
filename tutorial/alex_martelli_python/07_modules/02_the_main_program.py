#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# *** The Main Program ***
#
'''
__main__
'''
# However, it can get executed multiple times if imported as a module.
# To avoid this use this idiom:
'''
if __name__=='__main__':
'''

# Circular imports are possible between modules a.py and b.py as long
# as during loading the modules do not attempt to execute code from
# each other.

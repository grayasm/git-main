#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# pag. 145, The Main Program
#           Execution of a Python application normally starts with a top-level
#           script, the main program. It executes like a module being loaded,
#           except that Python keeps the bytecode in memory without saving it
#           to disk. The module name for the main program is always __main__,
#           both as the __name__ global variable and as the key in sys.modules
#           Not advisable but if loaded multiple times, it will execute each
#           time a different __name__. To avoid this use the idiom:

'''
if __name__=='__main__':
'''

# Circular imports are possible between modules a.py and b.py as long
# as during loading the modules do not attempt to execute code from
# each other.


if __name__ == '__main__':
    print ("Inside __main__")
    exit()

#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# pag 149, Packages
#          A package is a module that contains other modules. Some or all of
#          the modules in a package may be subpackages, resulting in a
#          hierarchical tree-like structure. The package parent directory must
#          be in sys.path for the import to find it. Packages can live also in
#          ZIP files having the same hierarchical concept.
#          Module body must contain a (even empty) __init__.py


'''
application-directory

    package-directory
        __init__.py
        module1.py
        module2.py

        subpackage-directory
            __init__.py
            module3.py
            moudle4.py
'''

#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# pag. 198, The repr Module
#           The repr module supplies an alternative to the built-in function
#           repr (covered in repr on page 166), with limits on length for the
#           representation string. To fine-tune the length limits, you can
#           instantiate or subclass the Repr class supplied by module repr and
#           apply detailed control. Most of the time, however, the main
#           function exposed by module repr suffices.


#    The repr module has been renamed reprlib in Python 3.
#    https://docs.python.org/3.6/library/reprlib.html?highlight=reprlib#module-reprlib

import reprlib
import sys


class MyRepr (reprlib.Repr):

    def repr_TextIOWrapper(self, obj, level):
        if obj.name in {'<stdin>', '<stdout>', '<stderr>'}:
            return obj.name
        return repr(obj)


aRepr = MyRepr()
print (aRepr.repr(sys.stdin))    # prints '<stdin>'

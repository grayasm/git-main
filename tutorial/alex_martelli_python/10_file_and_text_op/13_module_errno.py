#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# pag. 240, The errno Module
#           The errno module supplies symbolic names for error code numbers.
#           To handle possible system errors selectively, based on error codes,
#           use errno to enhance your program’s portability and readability.

import sys

try:
    f = open('integers.txt')
    s = f.readline()
    i = int(s.strip())
except IOError as e:
    errno, strerror = e.args
    print ("I/O error({0}): {1}".format(errno, strerror))  # I/O error(2): No
    # e can be printed directly without using .args:       # such file or
    # print(e)                                             # directory
except ValueError:
    print("No valid integer in line.")
except:
    print("Unexpected error:", sys.exc_info()[0])
    raise

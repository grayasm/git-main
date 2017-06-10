#!/usr/bin/env python3
# -*- coding: utf-8 -*-


# https://docs.python.org/3/library/mmap.html

import mmap


with open("09_module_mmap.py", "r+b") as f:
    # memory-map the file, size 0 means whole file
    mm = mmap.mmap(f.fileno(), 0)
    # read content via standard file methods
    print(mm.readline())
    # read content via slice notation
    print(mm[:5])
    mm.seek(0)
    print(mm.readline())
    # close the map
    mm.close()

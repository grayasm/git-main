#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# pag. 252, The shutil Module
#           The shutil module (an abbreviation for shell utilities) supplies
#           functions to copy and move files, and to remove an entire directory
#           tree. In addition to offering functions that are directly useful,
#           the source file shutil.py in the standard Python library is an
#           excellent example of how to use many os functions.


#    https://pymotw.com/3/shutil/#copying-files
#    Copying files
import glob
import shutil
import os
import io
import sys


print('BEFORE:', glob.glob('99_hello.*'))  # ['99_hello.txt']

shutil.copyfile('99_hello.txt', '99_hello.txt.copy')

print('AFTER:', glob.glob('99_hello.*'))   # ['99_hello.txt.copy',
                                           #  '99_hello.txt']


#    The implementation of copyfile() uses the lower-level function
#    copyfileobj(). While the arguments to copyfile() are filenames, the
#    arguments to copyfileobj() are open file handles. The optional third
#    argument is a buffer length to use for reading in blocks.


class VerboseStringIO(io.StringIO):

    def read(self, n=-1):
        next = io.StringIO.read(self, n)
        print('read({}) got {} bytes'.format(n, len(next)))
        return next


lorem_ipsum = '''Lorem ipsum dolor sit amet, consectetuer
adipiscing elit.  Vestibulum aliquam mollis dolor. Donec
vulputate nunc ut diam. Ut rutrum mi vel sem. Vestibulum
ante ipsum.'''

print('Default:')
input = VerboseStringIO(lorem_ipsum)
output = io.StringIO()
shutil.copyfileobj(input, output)  # read(16384) got 166 bytes
                                   # read(16384) got 0 bytes
print()

print('All at once:')
input = VerboseStringIO(lorem_ipsum)
output = io.StringIO()
shutil.copyfileobj(input, output, -1)  # read(-1) got 166 bytes
                                       # read(-1) got 0 bytes

print()

print('Blocks of 256:')
input = VerboseStringIO(lorem_ipsum)
output = io.StringIO()
shutil.copyfileobj(input, output, 256)  # read(256) got 166 bytes
                                        # read(256) got 0 bytes

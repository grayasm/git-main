#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# pag. 229, The StringIO and cStringIO Modules supply a factory that is
#           callable to create in-memory file-like objects.
#           The difference betwee the two is that StringIO
#           - can be inherited
#           - can operate on both input and output
#           - does support Unicode
#           On the other side cStringIO has better performance.
#
#    http://stackoverflow.com/questions/11914472/stringio-in-python3
#      The StringIO and cStringIO modules are gone.
#      Instead, import the io module and use io.StringIO or io.BytesIO for text
#      and data respectively.

'''
class StringIO.StringIO([buffer])
StringIO.getvalue()
StringIO.close()
'''

# https://docs.python.org/2/library/stringio.html
from io import StringIO

# StringIO example usage
output = StringIO()
output.write('First line.\n')


# Retrieve file contents -- this will be 'First line.\nSecond line.\n'
contents = output.getvalue()
print ('StringIO.getvalue()=%s' % contents)

# Close object and discard memory buffer --
# .getvalue() will not raise an exception.
output.close()

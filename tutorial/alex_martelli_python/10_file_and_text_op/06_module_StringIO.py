#!/usr/bin/python -tt
# -*- coding: utf-8 -*-

# pag. 229, The StringIO and cStringIO Modules supply a factory that is
#           callable to create in-memory file-like objects.
#           The difference betwee the two is that StringIO
#           - can be inherited
#           - can operate on both input and output
#           - does support Unicode
#           On the other side cStringIO has better performance.

'''
class StringIO.StringIO([buffer])
StringIO.getvalue()
StringIO.close()
'''

# https://docs.python.org/2/library/stringio.html
import StringIO
import cStringIO

# StringIO example usage
output = StringIO.StringIO()
output.write('First line.\n')
print >> output, 'Second line.'

# Retrieve file contents -- this will be 'First line.\nSecond line.\n'
contents = output.getvalue()
print 'StringIO.getvalue()=%s' % contents

# Close object and discard memory buffer --
# .getvalue() will not raise an exception.
output.close()

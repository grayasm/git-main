#!/usr/bin/python -tt
# -*- coding: utf-8 -*-

# pag.223, The tempfile Module lets you create temporary files and directories
#          in the most secure manner afforded by your platform.
#          Temporary files are often excellent for an amount of data that
#          might not confortably fit in memory, or when your program writes
#          data that another process will use.

# 2.7.12 doc: https://docs.python.org/2/library/tempfile.html#module-tempfile

'''
tempfile.TemporaryFile     ([mode='w+b' [,bufsize=-1 [,suffix='' [,prefix='tmp' [,dir=None]]]]])
tempfile.NamedTemporaryFile([mode='w+b' [,bufsize=-1 [,suffix='' [,prefix='tmp' [,dir=None [,delete=True]]]]]])
tempfile.SpooledTemporaryFile([max_size=0 [,mode='w+b' [,bufsize=-1 [,prefix='tmp' [,dir=None]]]]])
tempfile.mkstemp([suffix='' [,prefix='tmp' [,dir=None [,text=False]]]])
tempfile.mkdtemp([suffix='' [,prefix='tmp' [,dir=None]]])
tempfile.tempdir
tempfile.gettempdir()
tempfile.gettempprefix()
'''

import tempfile
import os

fd, path = tempfile.mkstemp(suffix='.txt', text=True)
try:
	print "content of file: %s" % path
	os.write(fd, "header\nline 2\nend of file")
	os.close(fd)
	f = open(path, 'r')
	s = f.read()
	print s
	f.close()
finally:
	os.unlink(path)

'''
content of file: /tmp/tmpFiGpaF.txt
header
line 2
end of file
'''


#!/usr/bin/python -tt
# -*- coding: utf-8 -*-

# pag.224, The fileinput Module lets you loop over all the lines in a list
#          of text files. Performance is good, comparable to the performance
#          of direct iteration of each file, since fileinput uses buffering
#          to minimize I/O.
#          The input function is the key function of module fileinput, and
#          the module also provides a FileInput class whose method supports
#          the same functionality as the module's functions.

'''
fileinput.input(files=None, inplace=False, backup='', bufsize=0)
fileinput.filename()
fileinput.fileno()
fileinput.lineno()
fileinput.filelineno()
fileinput.isfirstline()
fileinput.isstdin()
fileinput.nextfile()
fileinput.close()
fileinput.hook_compressed(filename, mode)
fileinput.hook_encoded(encoding)
fileinput.FileInput([files [,inplace [,backup [,bufsize [,mode [,openhook]]]]]])
'''

# https://docs.python.org/3/library/fileinput.html
import fileinput

f = fileinput.input(files=('99_spam.txt', '99_eggs.txt'))
for line in f:
    print "%s:%d:%s" % (f.filename(), f.filelineno(), line),
f.close()

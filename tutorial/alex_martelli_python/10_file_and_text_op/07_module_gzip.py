#!/usr/bin/python -tt
# -*- coding: utf-8 -*-

# pag. 230, The gzip Module lets you read and write files compatible with those
#           handled by the powerful GNU compression programs gzip and gunzip.
#           The GNU programs support many compression formats, but module
#           gzip supports only the highly effective native gzip format,
#           normally denoted by appending the extension .gz to a filename.
#           Module gzip supplies GzipFile class and an open factory function.

'''
class GzipFile(filename=None, mode=None, compresslevel=9, fileobj=None)
gzip.open(filename [,mode [,compressionlevel]])
'''

# https://docs.python.org/2/library/gzip.html
import gzip
import shutil

# example of how to create a compressed file
content = "Lots of content here"
with gzip.open('file.txt.gz', 'wb') as f:
    f.write(content)

# example of how to read a compressed file
with gzip.open('file.txt.gz', 'rb') as f:
    file_content = f.read()
    print "file.txt.gz: %s" % file_content

# example of how to gzip compress an existing file
with open('99_hello.txt', 'rb') as f_in:
    with gzip.open('file.txt.gz', 'wb') as f_out:
        shutil.copyfileobj(f_in, f_out)

# another exmple from the book pag. 231
zipped_f = open('file.txt.gz', 'rb')
unzipped_f = gzip.GzipFile(fileobj=zipped_f, mode='rt')
print 'file.txt.gz: ',
for line in unzipped_f:
    print line,

unzipped_f.close()
zipped_f.close()

#!/usr/bin/python -tt
# -*- coding: utf-8 -*-

# pag.216, file is a built-in type in Python and the single most common way
#          for you Python programs to read or write data.
#          Python reacts to any I/O error related to a file object by raising
#          an instance fo built-in exception class IOError.

# Create a File Object with open
filename = '99_hello.txt'
mode = 'r'
bufsize = -1

f = open(filename, mode, bufsize)
for line in f:
        print line,

# mode possible values= 'r' 'w' 'a' 'r+' 'w+' 'a+'
# for binary or text modes append= 'b' or 't'  ex= 'rb' 'rt'
# bufsize can be >0 or -1 for default internal buffer size

# another example: https://docs.python.org/2/library/stdtypes.html#file-objects
print('----------------------')
with open('99_hello.txt') as f:
        for line in f:
                print line,

print('----------------------')
f = open('99_hello.txt')
try:
        for line in f:
                print line,
finally:
        f.close()

# pag.218,  Attributes and Methods of File Objects.
'''
file.close()
file.closed
file.encoding
file.flush()
file.isatty()
file.fileno()
file.mode
file.name
file.newlines
file.read(size=-1)
file.readline(size=-1)
file.readlines(size=-1)
file.seek(pos, how=0)
file.softspace
file.tell()
file.truncate([size])
file.write(s)
file.writelines(lst)
'''

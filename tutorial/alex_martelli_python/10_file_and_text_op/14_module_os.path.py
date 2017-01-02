#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# pag. 246, The os.path Module
#           The os.path module supplies functions to analyze and transform path
#           strings. To use this module, you can import os.path ; however, if
#           you just import os , you can also access module os.path and all of
#           its attributes.


#    https://docs.python.org/3/library/os.path.html
#    Common pathname manipulations
'''
os.path.abspath(path)
os.path.basename(path)
os.path.commonpath(paths)
os.path.commonprefix(list)
os.path.dirname(path)
os.path.exists(path)
os.path.lexists(path)
os.path.expanduser(path)
os.path.expandvars(path)
os.path.getatime(path)
os.path.getmtime(path)
os.path.getctime(path)
os.path.getsize(path)
os.path.isabs(path)
os.path.isfile(path)
os.path.isdir(path)
os.path.islink(path)
os.path.ismount(path)
os.path.join(path, *paths)
os.path.normcase(path)
os.path.normpath(path)
os.path.realpath(path)
os.path.relpath(path, start=os.curdir)
os.path.samefile(path1, path2)
os.path.sameopenfile(fp1, fp2)
os.path.samestat(stat1, stat2)
os.path.split(path)
os.path.splitdrive(path)
os.path.splitext(path)
os.path.splitunc(path)
os.path.supports_unicode_filenames
'''


#    few examples to satify my curiosity
#    https://pymotw.com/2/ospath/

import os.path

for path in ['/path/to/filename.txt',
             '/path/to/unknown',
             '/path/to/dir/',
             '.',
             '']:
    print ("path    : %s" % path)
    print ("dirname : %s" % os.path.dirname(path))
    print ("basename: %s" % os.path.basename(path))
    print ("split   :", os.path.split(path))
    print ("splitext:", os.path.splitext(path))

# path    : /path/to/filename.txt
# dirname : /path/to
# basename: filename.txt
# split   : ('/path/to', 'filename.txt')
# splitext: ('/path/to/filename', '.txt')

# path    : /path/to/unknown
# dirname : /path/to
# basename: unknown
# split   : ('/path/to', 'unknown')
# splitext: ('/path/to/unknown', '')

# path    : /path/to/dir/
# dirname : /path/to/dir
# basename:
# split   : ('/path/to/dir', '')
# splitext: ('/path/to/dir/', '')

# path    : .
# dirname :
# basename: .
# split   : ('', '.')
# splitext: ('.', '')

# path    :
# dirname :
# basename:
# split   : ('', '')
# splitext: ('', '')

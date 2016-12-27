#!/usr/bin/env python3
# -*- coding: utf-8 -*-

#
# Module Loading
#
# __import__ (...)  searches in sys.modules first.

import sys
print ('sys.modules=\n', sys.modules)
# sys.modules=
# {'reprlib': <module 'reprlib' from '/usr/lib64/python3.3/reprlib.py'>,
# '__main__': <module '__main__' from '02_module_loading.py'>,
# 'encodings.utf_8': <module 'encodings.utf_8' from
#     '/usr/lib64/python3.3/encodings/utf_8.py'>,
# 'collections': <module 'collections' from
#     '/usr/lib64/python3.3/collections/__init__.py'>,
# 'os.path': <module 'posixpath' from '/usr/lib64/python3.3/posixpath.py'>,
# 'weakref': <module 'weakref' from '/usr/lib64/python3.3/weakref.py'>,
# 'site': <module 'site' from '/usr/lib64/python3.3/site.py'>,
# 'errno': <module 'errno' (built-in)>,
# '_weakref': <module '_weakref' (built-in)>,
# 'collections.abc': <module 'collections.abc' from
#     '/usr/lib64/python3.3/collections/abc.py'>,
# '_sre': <module '_sre' (built-in)>,
# 'os': <module 'os' from '/usr/lib64/python3.3/os.py'>,
# '_thread': <module '_thread' (built-in)>,
# 'abc': <module 'abc' from '/usr/lib64/python3.3/abc.py'>,
# 'operator': <module 'operator' (built-in)>,
# 'posixpath': <module 'posixpath' from '/usr/lib64/python3.3/posixpath.py'>,
# 'codecs': <module 'codecs' from '/usr/lib64/python3.3/codecs.py'>,
# '_codecs': <module '_codecs' (built-in)>,
# '_frozen_importlib': <module '_frozen_importlib' (frozen)>,
# 'keyword': <module 'keyword' from '/usr/lib64/python3.3/keyword.py'>,
# '_warnings': <module '_warnings' (built-in)>,
# 'sys': <module 'sys' (built-in)>,
# 'sre_constants': <module 'sre_constants' from
#     '/usr/lib64/python3.3/sre_constants.py'>,
# 'io': <module 'io' from '/usr/lib64/python3.3/io.py'>,
# '_collections': <module '_collections' (built-in)>,
# '_imp': <module '_imp' (built-in)>,
# 'sre_compile': <module 'sre_compile' from
#     '/usr/lib64/python3.3/sre_compile.py'>,
# 'posix': <module 'posix' (built-in)>,
# '_sysconfigdata': <module '_sysconfigdata' from
#     '/usr/lib64/python3.3/_sysconfigdata.py'>,
# 'stat': <module 'stat' from '/usr/lib64/python3.3/stat.py'>,
# 're': <module 're' from '/usr/lib64/python3.3/re.py'>,
# 'encodings': <module 'encodings' from
#     '/usr/lib64/python3.3/encodings/__init__.py'>,
# 'functools': <module 'functools' from '/usr/lib64/python3.3/functools.py'>,
# 'sysconfig': <module 'sysconfig' from '/usr/lib64/python3.3/sysconfig.py'>,
# 'sre_parse': <module 'sre_parse' from '/usr/lib64/python3.3/sre_parse.py'>,
# 'copyreg': <module 'copyreg' from '/usr/lib64/python3.3/copyreg.py'>,
# 'zipimport': <module 'zipimport' (built-in)>,
# 'marshal': <module 'marshal' (built-in)>,
# '_io': <module 'io' (built-in)>,
# 'itertools': <module 'itertools' (built-in)>,
# 'encodings.aliases': <module 'encodings.aliases' from
#     '/usr/lib64/python3.3/encodings/aliases.py'>,
# '_heapq': <module '_heapq' from
#     '/usr/lib64/python3.3/lib-dynload/_heapq.cpython-33m.so'>,
# 'genericpath': <module 'genericpath' from
#    '/usr/lib64/python3.3/genericpath.py'>,
# 'builtins': <module 'builtins' (built-in)>,
# '_weakrefset': <module '_weakrefset' from
#    '/usr/lib64/python3.3/_weakrefset.py'>,
# 'signal': <module 'signal' (built-in)>,
# 'encodings.latin_1': <module 'encodings.latin_1' from
#     '/usr/lib64/python3.3/encodings/latin_1.py'>,
# '_functools': <module '_functools' (built-in)>,
# 'heapq': <module 'heapq' from '/usr/lib64/python3.3/heapq.py'>}


# if not a built-in module
# __import__(...) search in the sys.path
print ('sys.path=\n', sys.path)


# sys.path=
# ['/home/mihai/Code/git-main/tutorial/alex_martelli_python/07_modules',
#  '/usr/lib64/python33.zip',
#  '/usr/lib64/python3.3',
#  '/usr/lib64/python3.3/plat-linux',
#  '/usr/lib64/python3.3/lib-dynload',
#  '/usr/lib64/python3.3/site-packages',
#  '/usr/lib/python3.3/site-packages']


# __import__(...) will execute .pth files in the PYTHONHOME directory.

# __import__(...) modules have priority by extension as follows:
# (1) .pyd (OSX) .dll (Windows) .so(Unix)  .sl(HP-UX)
# (2) .py
# (3) .pyc .pyo when run with -O

class TT(object):
    def __getattr__(self, name): return 23


sys.modules[__name__] = TT()

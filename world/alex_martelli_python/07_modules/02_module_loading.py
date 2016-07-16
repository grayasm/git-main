#
# Module Loading
#
# __import__ (...)  searches in sys.modules first.

import sys
print sys.modules

# {'copy_reg': <module 'copy_reg' from '/usr/lib64/python2.7/copy_reg.pyc'>,
# 'sre_compile': <module 'sre_compile' from '/usr/lib64/python2.7/sre_compile.pyc'>,
# '_sre': <module '_sre' (built-in)>,
# 'encodings': <module 'encodings' from '/usr/lib64/python2.7/encodings/__init__.pyc'>,
# 'site': <module 'site' from '/usr/lib64/python2.7/site.pyc'>,
# '__builtin__': <module '__builtin__' (built-in)>,
# 'sysconfig': <module 'sysconfig' from '/usr/lib64/python2.7/sysconfig.pyc'>,
# '__main__': <module '__main__' from '02_module_loading.py'>,
# 'encodings.encodings': None,
# 'abc': <module 'abc' from '/usr/lib64/python2.7/abc.pyc'>,
# 'posixpath': <module 'posixpath' from '/usr/lib64/python2.7/posixpath.pyc'>,
# '_weakrefset': <module '_weakrefset' from '/usr/lib64/python2.7/_weakrefset.pyc'>,
# 'errno': <module 'errno' (built-in)>,
# 'encodings.codecs': None,
# 'sre_constants': <module 'sre_constants' from '/usr/lib64/python2.7/sre_constants.pyc'>,
# 're': <module 're' from '/usr/lib64/python2.7/re.pyc'>,
# '_abcoll': <module '_abcoll' from '/usr/lib64/python2.7/_abcoll.pyc'>,
# 'types': <module 'types' from '/usr/lib64/python2.7/types.pyc'>,
# '_codecs': <module '_codecs' (built-in)>,
# 'encodings.__builtin__': None,
# '_warnings': <module '_warnings' (built-in)>,
# 'genericpath': <module 'genericpath' from '/usr/lib64/python2.7/genericpath.pyc'>,
# 'stat': <module 'stat' from '/usr/lib64/python2.7/stat.pyc'>,
# 'zipimport': <module 'zipimport' (built-in)>,
# '_sysconfigdata': <module '_sysconfigdata' from '/usr/lib64/python2.7/_sysconfigdata.pyc'>,
# 'warnings': <module 'warnings' from '/usr/lib64/python2.7/warnings.pyc'>,
# 'UserDict': <module 'UserDict' from '/usr/lib64/python2.7/UserDict.pyc'>,
# 'encodings.utf_8': <module 'encodings.utf_8' from '/usr/lib64/python2.7/encodings/utf_8.pyc'>,
# 'sys': <module 'sys' (built-in)>, 'codecs': <module 'codecs' from '/usr/lib64/python2.7/codecs.pyc'>,
# 'os.path': <module 'posixpath' from '/usr/lib64/python2.7/posixpath.pyc'>,
# 'signal': <module 'signal' (built-in)>,
# 'traceback': <module 'traceback' from '/usr/lib64/python2.7/traceback.pyc'>,
# 'linecache': <module 'linecache' from '/usr/lib64/python2.7/linecache.pyc'>,
# 'posix': <module 'posix' (built-in)>,
# 'encodings.aliases': <module 'encodings.aliases' from '/usr/lib64/python2.7/encodings/aliases.pyc'>,
# 'exceptions': <module 'exceptions' (built-in)>,
# 'sre_parse': <module 'sre_parse' from '/usr/lib64/python2.7/sre_parse.pyc'>,
# 'abrt_exception_handler': <module 'abrt_exception_handler' from '/usr/lib64/python2.7/site-packages/abrt_exception_handler.pyc'>,
# 'os': <module 'os' from '/usr/lib64/python2.7/os.pyc'>,
# '_weakref': <module '_weakref' (built-in)>}



# if not a built-in module
# __import__(...) search in the sys.path
print sys.path

# ['/home/mihai/Code/git-main/world/alex_martelli_python/07_modules',
#  '/usr/lib64/python27.zip',
#  '/usr/lib64/python2.7',
#  '/usr/lib64/python2.7/plat-linux2',
#  '/usr/lib64/python2.7/lib-tk',
#  '/usr/lib64/python2.7/lib-old',
#  '/usr/lib64/python2.7/lib-dynload',
#  '/usr/lib64/python2.7/site-packages',
#  '/usr/lib64/python2.7/site-packages/gtk-2.0',
#  '/usr/lib/python2.7/site-packages']


# __import__(...) will execute .pth files in the PYTHONHOME directory.

# __import__(...) modules have priority by extension as follows:
# (1) .pyd (OSX) .dll (Windows) .so(Unix)  .sl(HP-UX)
# (2) .py
# (3) .pyc .pyo when run with -O

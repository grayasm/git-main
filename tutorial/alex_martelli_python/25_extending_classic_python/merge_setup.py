from distutils.core import setup, Extension

modname = 'merge'
modfile = 'merge.c'
setup(name=modname, ext_modules=[Extension(modname, sources=[modfile])])

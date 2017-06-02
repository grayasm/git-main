from distutils.core import setup, Extension

modname = 'x'
modfile = 'x.c'
setup(name=modname, ext_modules=[Extension(modname, sources=[modfile])])

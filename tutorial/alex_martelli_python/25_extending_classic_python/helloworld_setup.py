from distutils.core import setup, Extension

modname = 'helloworld'
modfile = 'helloworld.c'
setup(name=modname, ext_modules=[Extension(modname, sources=[modfile])])

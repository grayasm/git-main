from distutils.core import setup, Extension

modname = '01_module_x'
modfile = '01_module_x.c'
setup(name=modname, ext_modules=[Extension(modname, sources=[modfile])])

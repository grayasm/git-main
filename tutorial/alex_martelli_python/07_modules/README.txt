#
# pag. 139, Chapter 7. Modules
#
#           A typical Python program is made up of several source files. Each
#           source file corresponds to a module, grouping program code and data
#           for reuse. Modules are normally independent of each other so that
#           other programs can reuse the specific modules they need. A module
#           explicitly establishes dependencies upon another module by using
#           import or from statements. In some other programming languages,
#           global variables can provide hidden conduit for coupling between
#           modules. In Python, however, global variables are not global to all
#           modules, but rather attributes of a single module object.
#           Python also supports extensions, which are components written in
#           ohter languages such as C, C++, Java or C#. Extensions are seen
#           as modules by the Python code that uses them (known as client code).
#           From the client code viewpoint it does not matter whether a module
#           is 100 percent pure Python or an extension. You can always start
#           by coding a module in Python. Later, should you need better
#           performance, you can recode some modules in lower-level languages
#           without changing the client code that uses the modules.
#           Chapter 25 and 26 discuss writing extensions in C and Java.

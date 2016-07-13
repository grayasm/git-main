*
  Chapter 1 - Introduction to Python

  Standard Python library and other extension modules.
  ----------------------------------------------------
  A. Standard Python library includes modules for:
     data, string, text processing, sys, filesystem, web programming.
     written in Python and work on every operating system.

  B. Extension Modules:
     access functionality supplied by the underlying OS and other software
     components: GUI, DB, networks, XML parsing, numeric array computations.
     not written in Python - not cross platform.

  Python Implementations.
  -----------------------
  3 production-quality implementations: CPython, Jython, IronPython.
  experimental implementations: PyPy.

  This book is about CPython, referred as Python for simplicity.

  CPython: Classis Python, fastest most up-to-date, solid, complete Python.
           compiler, interpreter, set of built-in and optional extension
           modules, all coded in standard C (ISO/IEC 9899:1990)

  Jython:  implementation for any Java Virtual Machine (JVM), Java1.2 complient
           or better. Java specific, require tools for .jar files and signing
           applets.

  IronPython: Python implementation for Microsoft-designed Common Language
           Runtime (CLR), most commonly known as .NET. Cross platform Mono
           CLR works with other OSes. Documentation touches C# extesively.

  PyPy: and other experimental version, are not yet suitable for production use.
           Pirate Python implementation runs on top of Parrot virtual machine,
           supports Perl 6 and other VHL.
           PyPy is a fast,flexible implementation written in Python itself.

  Licenses:
  ---------
  Implementations are free (e.g. CPython, Jython, IronPtyon).
  Non-free licenses exists for third-party Python sources, tools, extension
           modules. Commercially developed modules and tools require a fee.

  Development of Pyhton.
  ----------------------
  Python author Guido van Rossum is inventor, architect and Benevolent
           Dictator For Life (BDFL). He has final say on what becomes part
           of language and standard libraries.

  Python Software Foundation is non-profit org. devoted to promoting Python.

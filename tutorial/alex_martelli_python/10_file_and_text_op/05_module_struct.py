#!/usr/bin/python -tt
# -*- coding: utf-8 -*-

# pag.227, The struct Module lets you pack binary data into a string, and
#          unpack the bytes of such a string back into the data they represent.
#          Such operations are useful for many kinds of low-level programming.
#          Most often, you use module struct to interpret data records from
#          binary files that have some specified format, or to prepare records
#          to write to such binary files.
#          The modulename's name comes from C's keyword struct, which is usable
#          for related purposes. Function of struct module raise exceptions
#          of class struct.error

'''
exception struct.error
struct.pack(fmt, v1, v2, ...)
struct.pack_into(fmt, buffer, offset, v1, v2, ...)
struct.unpack(fmt, string)
struct.unpack_from(fmt, buffer [,ofset=0])
struct.calcsize(fmt)
'''

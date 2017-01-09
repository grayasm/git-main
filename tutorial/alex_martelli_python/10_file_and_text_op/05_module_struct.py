#!/usr/bin/env python3
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

# The fmt format specifies 3 characters for: byte order, size and alignament.
'''
  @    native byte order, native data size and native alignament for the
       the current platform.

  =    native byte order for the current platform but standard size and
       alignament

  <    little-endian byte oder (like Intel platforms), standard size and
       alignament

  >,!  big-endian byte order (network standard); standard size and
       alignament
'''

# Also in fmt after the byte specification follows the packing format.
'''
  B    unsigned char     int             1 byte
  b    signed char       int             1 byte
  c    char              str(length1)    1 byte
  d    double            float           8 bytes
  f    float             float           4 bytes
  H    unsigned short    int             2 bytes
  h    signed short      int             2 bytes
  I    unsigned int      long            4 bytes
  i    signed int        int             4 bytes
  L    unsigned long     long            4 bytes
  l    signed long       int             4 bytes
  P    void*             int             N/A
  p    char[]            String          N/A
  s    char[]            String          N/A
  x    padding byte      no value        1 byte
'''

# https://docs.python.org/2/library/struct.html#examples
import struct

# a basic exmple of packing/unpacking three integers
packed_str = struct.pack('hhl', 1, 2, 3)
print ("hhl=%s" % packed_str)

unpacked_tuple = struct.unpack('hhl', packed_str)
print ("unpacked_tupple=", unpacked_tuple)

# unpacked fields can be named by assigning them to variables or by wrapping
# the result in a named tuple
record = bytes('raymond   \x32\x12\x08\x01\x08', 'UTF-8')
name, serialnum, school, gradelevel = struct.unpack('<10sHHb', record)

print ("name=%s serialnum=%d school=%d gradelevel=%d" % (name, serialnum,
                                                         school, gradelevel))

# the ordering of format characters may have an impact on size since the
# padding needed to satisfy alignament requirements is different.
print ("struct.calcsize('ci')=%d" % struct.calcsize('ci'))
print ("struct.calcsize('ic')=%d" % struct.calcsize('ic'))

# the following format 'llh0l' specifies two pad bytes at the end, assuming
# longs are aligned on 4-bytes boundaries.
print ("struct.pack('llh0l', 1, 2, 3)=%s" % struct.pack('llh0l', 1, 2, 3))

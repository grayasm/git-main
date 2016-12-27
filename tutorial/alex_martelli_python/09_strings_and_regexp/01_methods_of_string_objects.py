#!/usr/bin/env python3
# -*- coding: utf-8 -*-

#
# Methods of String Objects
#
# https://docs.python.org/2/library/stdtypes.html#string-methods


#  capitalize()
print ("a complete sentence.".capitalize())  # A complete sentence.

#  center(n, fillchar=' ')
end = "-*-"
txt = "text"
print (end, txt, end)             # -*- text -*-
print (end, txt.center(8), end)   # -*-   text   -*-

#  count(sub, start=0, end=sys.maxint)
#  decode(codec=None, errors='strict')
#  encode(codec=None, errors='strict')
#  endswith(suffix, start=0, end=sys.maxint)
#  expandtabs(tabsize=8)
#  find(sub, start=0, end=sys.maxint)
s = "/tmp/autocomplete/etc/install.el"
print (s.find('install.el'))      # 22

#  index(sub, start=0, end=sys.maxint)
#  isalnum()
#  isalpha()
#  isdigit()
#  islower()
#  isspace()
#  istitle()
#  isupper()
#  join(seq)
#  ljust(n, fillchar=' ')
#  lower()
#  lstrip(x=string.whitespace)
#  replace(old, new, maxsplit=sys.maxint)
#  rfind(sub, start=0, end=sys.maxint)
#  rindex(sub, start=0, end=sys.maxint)
#  rjust(n, fillchar=' ')
#  rstrip(x=string.whitespace)
#  split(sep=None, maxsplit=sys.maxint)
#  splitlines(keepends=False)
#  startswith(prefix, start=0, end=sys.maxint)
#  strip(x=string.whitespace)
#  swapcase()
#  title()
#  translate(table, deletechars='')
#  translate(table)
#  upper()

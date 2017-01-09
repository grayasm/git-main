#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# pag. 186, Methods of String Objects
#           Plain and Unicode strings are immutable sequences. All immutable
#           sequence operations (repetition, concatenation, indexing, slicing)
#           apply to strings. A string object s also supplies several
#           nonmutating methods, as documented in this section.
#           Unless otherwise noted, each method returns a plain string when s
#           is a plain string, or a Unicode string when s is a Unicode string.
#           Terms such as “letters,” “whitespace,” and so on, refer to the
#           corresponding attributes of the string module.


#    String Methods
#    https://docs.python.org/2/library/stdtypes.html#string-methods
'''
str.capitalize()
str.casefold(()
str.center(width [, fillchar])
str.count(sub [, start [, end]])
str.encode(encoding="utf-8", errors="strict")
str.endswith(suffix [, start [, end]])
str.expandtabs(tabsize=8)
str.find(sub [, start [, end]])
str.format(*args, **kwargs)
str.format_map(mapping)
str.index(sub [, start [, end]])
str.isalnum()
str.isalpha()
str.isdecimal()
str.isdigit()
str.isidentifier()
str.islower()
str.isnumeric()
str.isprintable()
str.isspace()
str.istitle()
str.isupper()
str.join(iterable)
str.ljust(width [, fillchar])
str.lower()
str.lstrip([chars])
static str.maketrans(x [, y [, z]])
str.partition(sep)
str.replace(old, new [, count])
str.rfind(sub [, start [, end]])
str.rindex(sub [, start [, end]])
str.rjust(width [, fillchar])
str.rpartition(sep)
str.rsplit(sep=None, maxsplit=-1)
str.rstrip([chars])
str.split(sep=None, maxsplit=-1)
str.splitlines([keepends])
str.startswith(prefix [, start [, end]])
str.strip([chars])
str.swapcase()
str.title()
str.tranlate(table)
str.upper()
str.zfill()
'''


print ("a complete sentence.".capitalize())  # A complete sentence.

end = "-*-"
txt = "text"
print (end, txt, end)             # -*- text -*-
print (end, txt.center(8), end)   # -*-   text   -*-

s = "/tmp/autocomplete/etc/install.el"
print (s.find('install.el'))      # 22

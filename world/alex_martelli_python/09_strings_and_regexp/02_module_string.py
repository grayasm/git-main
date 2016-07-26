#!/usr/bin/python -tt
# -*- coding: utf-8 -*-

#
# The string Module
#
# https://docs.python.org/2/library/string.html#module-string

import string

string.ascii_letters
string.ascii_lowercase   # 'abcdefghijklmnopqrstuvwxyz'
string.ascii_uppercase   # 'ABCDEFGHIJKLMNOPQRSTUVWXYZ'
string.digits            # '0123456789'
string.hexdigits         # '0123456789abcdefABCDEF'
string.letters
string.lowercase         # 'abcdefghijklmnopqrstuvwxyz'
string.octdigits         # '01234567'
string.punctuation
string.printable
string.uppercase         # 'ABCDEFGHIJKLMNOPQRSTUVWXYZ'
string.whitespace
# maketrans(from, onto)

# 'maketrans(from, onto) returns a translation table, a plain string of length
#                        256 that provides mapping from chars. in ascending
#                        ASCII to another set of characters

identity = string.maketrans('','')
print 'some string'.translate(identity, 'aeiou')  # sm strng

# the Unicode equivalent would be:
no_vowels = dict.fromkeys(ord(x) for x in 'aeiou')
print u'some string'.translate(no_vowels)         # sm strng

# example of turning all other vowels into 'a' and delete 's'
intoa = string.maketrans('eiou', 'aaaa')
print 'some string'.translate(intoa)              # sama strang
print 'some string'.translate(intoa, 's')         # ama trang

#!/usr/bin/env python3
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
string.ascii_letters
string.ascii_lowercase   # 'abcdefghijklmnopqrstuvwxyz'
string.octdigits         # '01234567'
string.punctuation
string.printable
string.ascii_uppercase   # 'ABCDEFGHIJKLMNOPQRSTUVWXYZ'
string.whitespace

# the Unicode equivalent would be:
no_vowels = dict.fromkeys(ord(x) for x in 'aeiou')
print(('some string'.translate(no_vowels)))         # sm strng

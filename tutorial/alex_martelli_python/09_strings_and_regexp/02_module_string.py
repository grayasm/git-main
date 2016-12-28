#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# pag 191, The string Module
#          The string module supplies functions that duplicate each method of
#          string objects, as covered in “Methods of String Objects” pag. 186
#          Each function takes the (plain or Unicode) string object as its
#          first argument. Module string also supplies several useful
#          plain-string attributes.


#    Module string
#    https://docs.python.org/3.6/library/string.html#module-string

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

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

string.ascii_letters     # 'abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ'
string.ascii_lowercase   # 'abcdefghijklmnopqrstuvwxyz'
string.ascii_uppercase   # 'ABCDEFGHIJKLMNOPQRSTUVWXYZ'
string.digits            # '0123456789'
string.hexdigits         # '0123456789abcdefABCDEF'
string.octdigits         # '01234567'
string.punctuation       # '!"#$%&\'()*+,-./:;<=>?@[\\]^_`{|}~'
string.printable         # '0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!"#$%&\'()*+,-./:;<=>?@[\\]^_`{|}~ \t\n\r\x0b\x0c'
string.ascii_uppercase   # 'ABCDEFGHIJKLMNOPQRSTUVWXYZ'
string.whitespace        # ' \t\n\r\x0b\x0c'

# the Unicode equivalent would be:
no_vowels = dict.fromkeys(ord(x) for x in 'aeiou')
print(('some string'.translate(no_vowels)))         # sm strng

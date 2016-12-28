#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# pag. 198, Unicode
#           Plain strings are converted into Unicode strings either explicitly,
#           with the unicode built-in, or implicitly, when you pass a plain
#           string to a function that expects Unicode. In either case, the
#           conversion is done by an auxiliary object known as a codec (for
#           coder-decoder).
#           To identify a codec, pass the codec name to unicode or encode.
#           When you pass no codec name, and for implicit conversion, Python
#           uses a default encoding, normally 'ascii'
#           Every conversion has a parameter errors , a string specifying how
#           conversion errors are to be handled. The default is 'strict' ,
#           meaning any error raises an exception. When errors is 'replace' ,
#           the conversion replaces each character that causes an error
#           with '?' in a plain-string result and with u'\ufffd' in a Unicode
#           result. When errors is 'ignore' , the conversion silently skips
#           characters that cause errors. When errors is 'xmlcharrefreplace' ,
#           the conversion replaces each character that causes an error with
#           the XML character reference representation of that character in the
#           result.


# *** The 'codecs' Module
'''
codecs.encode(obj [,encoding [,errors]])
codecs.decode(obj [,encoding [,errors]])
codecs.register(search_function)
codecs.lookup(encoding)
codecs.getencoder(encoding)
codecs.getdecoder(encoding)
codecs.getincrementalencoder(encoding)
codecs.getincrementaldecoder(encoding)
codecs.getreader(encoding)
codecs.getwriter(encoding)
codecs.register_error(name, error_handle)
codecs.lookup_error(name)
codecs.strict_errors(exception)
codecs.replace_errors(exception)
codecs.ignore_errors(exception)
codecs.xmlcharrefreplace_errors(exception)
codecs.backslashreplace_errors(exception)
codecs.open(filename, mode [,encoding [,errors [,buffering]]])
codecs.EncodedFile(file, input [,output [,errors]])
codecs.interencode(iterable, encoding [,errors])
codecs.interdecode(iterable, encoding [,errors])
'''

#    some independent research ...

b1 = bytes("good morning(en)=早上好(ch)(Zǎoshang hǎo)", "utf-8")
t1 = str(b1, 'utf-8')
t2 = b'\xe6\x97\xa9\xe4\xb8\x8a\xe5\xa5\xbd'.decode("utf-8", "strict")

print ("b1:", b1)  # b'good morning(en)=\xe6\x97\xa9\xe4\xb8\x8a\xe5\xa5\xbd(ch)(Z\xc7\x8eoshang h\xc7\x8eo)'
print ("t1:", t1)  # good morning(en)=早上好(ch)(Zǎoshang hǎo)
print ("t2:", t2)  # 早上好

#    Diving In
#    http://www.diveintopython3.net/strings.html#divingin
#    In Python 3, all strings are sequences of Unicode characters. There is no
#    such thing as a Python string encoded in utf-8, or a Python string encoded
#    as CP-1252. “Is this string utf-8?” is an invalid question.
#    utf-8 is a way of encoding characters as a sequence of bytes. If you want
#    to take a string and turn it into a sequence of bytes in a particular
#    character encoding, Python 3 can help you with that. If you want to take a
#    sequence of bytes and turn it into a string, Python 3 can help you with
#    that too. Bytes are not characters; bytes are bytes. Characters are an
#    abstraction. A string is a sequence of those abstractions.
t3 = '深入 Python'
i3 = len(t3)
t4 = t3[0]
t5 = t3 + ' 3'

print ("t3:", t3)       # 深入 Python
print ("len(t3)=", i3)  # 9
print ("t4:", t4)       # 深
print ("t5:", t5)       # 深入 Python 3

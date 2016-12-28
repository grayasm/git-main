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

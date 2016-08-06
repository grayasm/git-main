#!/usr/bin/python -tt
# -*- coding: utf-8 -*-

#
# Unicode
#
# python uses a codec to encode/decode plain string to Unicode strings
# to identify the codec pass its name to 'unicode' or 'encode'
# by default python uses 'ascii'


# *** The 'codecs' Module
'''
import codecs
import sys
'''


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

# Inconsistent treatement of output
# https://pythonhosted.org/kitchen/unicode-frustrations.html#frustration-3-inconsistent-treatment-of-output
'''
str = unicode('météo tempête\n', 'utf8')
string_for_output = str.encode('utf8', 'replace')
log = open('/tmp/python_debug_can_delete.log', 'w')
log.write(string_for_output)
'''

# the StreamWriter converts from unicode and sends byte string to output
'''
str = u'météo tempête'
utf8writer = codecs.getwriter('utf8')  # StreamWriter type
sys.stdout = utf8writer(sys.stdout)
print str
'''

# https://pythonhosted.org/kitchen/unicode-frustrations.html#frustration-4-now-it-doesn-t-take-byte-strings
# now the StreamWriter fails when input is byte string instead of unicode
'''
import sys
from kitchen.text.converters import getwriter
str = 'météo tempête'
ustr = u'météo tempête'
utf8writer = getwriter('utf8')  # improved StreamWriter type
sys.stdout = utf8writer(sys.stdout)
print str, '\n', ustr
'''

# https://pythonhosted.org/kitchen/unicode-frustrations.html#frustration-5-exceptions
# now, I cannot rise exceptions with a unicode string

'''
from kitchen.text.converters import to_bytes

class myexception(Exception):
    pass
raise myexception(to_bytes(u'Cannot do this while at a café'))
'''


# https://pythonhosted.org/kitchen/unicode-frustrations.html#example-putting-this-all-together-with-kitchen
# short example with kitchen function that work with unicode

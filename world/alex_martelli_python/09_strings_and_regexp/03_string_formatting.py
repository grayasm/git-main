#!/usr/bin/python -tt
# -*- coding: utf-8 -*-

#
# String Formatting
#
# https://docs.python.org/2/library/string.html#custom-string-formatting

# format % values
import string


'''
d,i     signed decimal
u       unsigned decimal
o       unsigned octal
x       unsigned hexadecimal lowercase
X       unsigned hexadecimal uppercase
e       floating point lowercase exp
E       floating point uppercase exp
f,F     floating point decimal form
g,G     exp>=4 is e,E otherwise f,F
c       single character
r       string
s       string
%       literal % character

#       conversion uses an alternate form
0       zero padded
-       left-justified
space   space before positive number
+       numeric sign + or - before number
digits or *       width for next item in values
.digits or *      precision for next item in values
'''

# formatting idom
'''
'%s + %s is %s'%(23, 45, 23+45)
oneway = 'x' + str(j) + 'y' + str(j) + 'z'
another= 'x%sy%sz' % (j, j)
'%.2f' % (1/3.0)  #: 0.33
'%s' % (1/3.0)    #: 0.3333333..
'''


#
# Template Strings
#
# https://docs.python.org/2/library/string.html#template-strings
from string import Template
t = Template('$who likes $what')
t.substitute(who='tim', what='kung pao')


# t.safe_substitute(mapping, **k)
# t.substitute(mapping, **k)


#
# Text Wrapping and Filling
#
# https://docs.python.org/2/library/textwrap.html#module-textwrap

import textwrap

s = "This is a long text I want wrapped at 10 column. Thank you!"
print textwrap.wrap(s, 10)

# ['This is a', 'long text', 'I want', 'wrapped at', '10 column.',
#  'Thank you!']

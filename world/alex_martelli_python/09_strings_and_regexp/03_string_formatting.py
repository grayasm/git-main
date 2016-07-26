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


x = 42
y = 3.14
z = "george"
print 'result = %d' % x                 # result = 42
print 'answers are: %d %f' % (x,y)      # answers are: 42 3.14
print 'hello %s' % z                    # hello george


# https://docs.python.org/3/library/string.html#format-string-syntax
# Format String Syntax
# str.format() method and the Formatter class

print "who is {0}".format(100)                    # who is 100
print "who is {} ".format(100,200)                # who is 100
print "from {} to {}".format('A', 'Z')            # from A to Z
print "my guest is {name}".format(name='MJ')      # my guest is MJ

class Man(object):
    def __init__(self):
        self.weight = 121
m = Man()
print "normal weigth {0.weight}".format(m, 'ignored')  # normal weight 121

p=('Vava', 'Roni', 'Ménez')
print "from AC Milan {players[2]}".format(players=p)   # from AC Milan Ménez

# 3 conversion flags !s is str(arg), !r is repr(arg)

print "Harold's a clever {0!s}".format('boy', 'horse') # Harold's a clever boy
print "Bring out the holy {name!r}".format(name1='', name='grail')
                                                   # Bring out the holy 'grail'


# https://docs.python.org/2.7/library/string.html#format-examples
print '{0}, {1}, {2}'.format('a', 'b', 'c')        # a, b, c
print '{}, {}, {}'.format('a', 'b', 'c')           # a, b, c
print '{2}, {1}, {0}'.format('a', 'b', 'c')        # c, b, a

# unpacking arument sequence;
print '{2}, {1}, {0}'.format(*'abc')               # c, b, a
print '{0}{1}{0}'.format('abra', 'cad')            # abracadabra


# accessing arguments by name
print 'Coordinates: {latitude}, {longitude}'.format(
    latitude='37.24N',
    longitude='-115.81W')  # Coordinates: 37.24N, -115.81W

coord = {'latitude': '37.24N', 'longitude': '-115.81W'}
print 'Coordinates: {latitude}, {longitude}'.format(**coord)
                           # Coordinates: 37.24N, -115.81W

# accessing arguments attributes
c = 3-5j
print "Complex number {0} is formed from the real part {0.real} and\
 the imaginary part {0.imag}".format(c)
# Complex number (3-5j) is ... the real part 3.0 and ... the imaginary part -5.0

class Point(object):
    def __init__(self, x, y):
        self.x, self.y = x, y
    def __str__(self):
        return 'Point({self.x}, {self.y})'.format(self=self)

print str(Point(4, 2))        # Point(4, 2)


# Accessing arguments' items
coord = (3, 5)
print 'X: {0[0]}; Y: {0[1]}'.format(coord)        # X: 3; Y: 5


# Replacing %s and %r
print "repr() shows quotes: {!r}; str() doesn't: {!s}".format('test1', 'test2')
                         # repr() shows quotes: 'test1'; str() doesn't: test2


# Aligning the text and specifying a width
print '{:<30}'.format('left aligned')   #left aligned
print '{:>30}'.format('right aligned')  #                 right aligned
print '{:^30}'.format('centered')       #           centered

# use '*' as a fill char
print '{:*^30}'.format('centered')      #***********centered***********


# Replacing %+f, %-f and % f and specifying a sign
print '{:+f}; {:+f}'.format(3.14, -3.14)     #+3.140000; -3.140000
print '{: f}; {: f}'.format(3.14, -3.14)     # 3.140000; -3.140000
print '{:-f}; {:-f}'.format(3.14, -3.14)     #3.140000; -3.140000


# Replacing %x and %o and converting the values to different bases
print 'int: {0:d}  hex: {0:x}  oct: {0:o}  bin: {0:b}'.format(42)
                               # int: 42  hex: 2a  oct: 52  bin: 101010
print 'int: {0:d}  hex: {0:#x}  oct: {0:#o}  bin: {0:#b}'.format(42)
                               # int: 42  hex: 0x2a  oct: 0o52  bin: 0b101010

# Using comma as a thousands separator
print '{:,}'.format(1234567890)  # 1,234,567,890


# Expressing a percentage
points = 19.5
total = 22
print 'Correct answer: {:.2%}'.format(points/total) # Correct answer: 88.64%


# Using type-specific formatting
import datetime
d = datetime.datetime(2010, 7, 4, 12, 15, 58)
print '{:%Y-%m-%d %H:%M:%S}'.format(d) # 2010-07-04 12:15:58


# Nesting arguments and more complex examples
for align, text in zip('<^>', ['left', 'center', 'right']):
    print '{0:{fill}{align}16}'.format(text, fill=align, align=align)

'''
left<<<<<<<<<<<<
^^^^^center^^^^^
>>>>>>>>>>>right
'''
octets = [192, 168, 0, 1]
print '{:02X}{:02X}{:02X}{:02X}'.format(*octets)  # C0A80001


width = 5
for num in range(5, 12):
    for base in 'dXob':
        print '{0:{width}{base}}'.format(num, base=base, width=width),
    print
'''
    5     5     5   101
    6     6     6   110
    7     7     7   111
    8     8    10  1000
    9     9    11  1001
   10     A    12  1010
   11     B    13  1011
'''

# https://docs.python.org/2.7/library/string.html#template-strings
# to continue....

#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# pag. 61, The print Statement
#          A print statement si denoted by the keyword "print" followed by zero
#          or more expressions separated by commas. "print" is handy, simple
#          way to output values in text form, mostly for debugging purposes.
#          "print" outputs each expression x as a string that's just like
#          the result of calling str(x).
#          "print" implicitly outputs a space between expressions, and
#          implicitly outputs \n after the last expression, unless the last
#          expression is followed by a trailing comma (,)
#
#          see also: 09_strings_and_regexp/03_string_formatting.py

letter = 'c'
print ("give me a", letter, "...")  # prints: give me a c ...
answer = 42
print "the answer is:", answer  # prints: the answer is: 42

print ("line begin", end=" ")   # replaces end line '\n' with " "
print ("and line end")


# https://pyformat.info/
# Basic formatting
print '%s %s' % ('one', 'two')          # old style: one two
print '{} {}'.format('one', 'two')      # new style: one two

print '%d %d' % (1, 2)                  # old style: 1 2
print '{} {}'.format(1, 2)              # new style: 1 2

print '{1} {0}'.format('one', 'two')    # two one , not possible with old-style


# Value conversion
class Data(object):
    def __str__(self):
        return 'str'

    def __repr__(self):
        return 'repr'


print '%s %r' % (Data(), Data())        # str repr
print '{0!s} {0!r}'.format(Data())      # str repr

# Padding and aligning strings
# align right
print '%10s' % ('test',)                #      test
print '{:>10}'.format('test')           #      test

# align left
print '%-10s' % ('test',)               #test
print '{:10}'.format('test')            #test

print '{:_<10}'.format('test')          #test______
print '{:^10}'.format('test')           #   test

# Truncating long strings
print '%.5s' % ('xylophone',)           # xylop
print '{:.5}'.format('xylophone')       # xylop

# Combining truncating and padding
print '%-10.5s' % ('xylophone',)        # xylop
print '{:10.5}'.format('xylophone')     # xylop

# Numbers - integers
print '%d' % (42,)
print '{:d}'.format(42)

# Numbers - floats
print '%f' % (3.141592653589793,)       # 3.141593
print '{:f}'.format(3.141592653589793)  # 3.141593

# Padding Numbers
print '%4d' % (42,)                     #  42
print '{:4d}'.format(42)                #  42

print '%06.2f' % (3.141592653589793,)       # 003.14
print '{:06.2f}'.format(3.141592653589793)  # 003.14

# Signed Numbers
print '%+d' % (42,)                    # +42
print '{:+d}'.format(42)               # +42

print '% d' % ((- 23),)                # -23
print '{: d}'.format((- 23))           # -23

print '% d' % (42,)                    # 42
print '{: d}'.format(42)               # 42

print '{:=5d}'.format((- 23))          #-  23 , not possible with old-style

# Named placeholders
data = {'first': 'Hodor', 'last': 'Hodor!'}
print '%(first)s %(last)s' % data      # Hodor Hodor!
print '{first} {last}'.format(**data)  # Hodor Hodor!

print '{first} {last}'.format(first='Hodor', last='Hodor!')  # Hodor Hodor!


# Getitem with containers that support __getitem__
person = {'first': 'Jean-Luc', 'last': 'Picard'}
print '{p[first]} {p[last]}'.format(p=person)  # Jean-Luc Picard

data = [4, 8, 15, 16, 23, 42]
print '{d[4]} {d[5]}'.format(d=data)    # 23 42


# Getattr with containers that support accessing attributes via getattr()
class Plant(object):
    type = 'tree'


print '{p.type}'.format(p=Plant())      # tree


# Datetime
from datetime import datetime

print '{:%Y-%m-%d %H:%M}'.format(datetime(2001, 2, 3, 4, 5)) # 2001-02-03 04:05

# Parameterized formats, nested expressions in braces anywhere after colon.
print '{:{align}{width}}'.format('test', align='^', width='10')  #   test


# Parameterized precision
print '%.*s = %.*f' % (3, 'Gibberish', 3, 2.7182)                     # Gib = 2.718
print '{:.{prec}} = {:.{prec}f}'.format('Gibberish', 2.7182, prec=3)  # Gib = 2.718

# Parameterized width and precision
print '%*.*f' % (5, 2, 2.7182)                               # 2.72
print '{:{width}.{prec}f}'.format(2.7182, width=5, prec=2)   # 2.72

# - rewritten with nested format
print '{:{prec}} = {:{prec}}'.format('Gibberish', 2.7182, prec='.3')  # Gib = 2.72


# - rewritten with date and time separately
from datetime import datetime
dt = datetime(2001, 2, 3, 4, 5)
print '{:{dfmt} {tfmt}}'.format(dt, dfmt='%Y-%m-%d', tfmt='%H:%M')  # 2001-02-03 04:05

# - with nested formats as positional arguments
print '{:{}{}{}.{}}'.format(2.7182818284, '>', '+', 10, 3)  #     +2.72


# Custom objects, working through the __format__() magic method.
class HAL9000(object):
    def __format__(self, format):
        if (format == 'open-the-pod-bay-doors'):
            return "I'm afraid I can't do that."
        return 'HAL 9000'


print '{:open-the-pod-bay-doors}'.format(HAL9000())  # I'm afraid I can't do that. 

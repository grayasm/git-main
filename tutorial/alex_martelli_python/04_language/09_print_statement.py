#!/usr/bin/env python
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

letter = 'c'
print "give me a", letter, "..."  # prints: give me a c ...
answer = 42
print "the answer is:", answer  # prints: the answer is: 42


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

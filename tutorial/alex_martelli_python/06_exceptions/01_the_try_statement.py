#!/usr/bin/env python3
# -*- coding: utf-8 -*-

#
# pag. 121, The 'try' Statement.
#           The 'try' statement provided by Python's exception-handling
#           mechanism it is a compound statement that can take one of two
#           different forms:
#           - a try clause followed by one or more except clauses and
#             optionally an else clause
#           - a try clause followed by exactly one finally clause

# *** try/except ***
'''
try:
    statement(s)
except: [expression [, target]]:
    statement(s)
[else:
    statement(s)]
'''


try:
    1 / 0                               # print 'caught divide-by-0 attempt'
except ZeroDivisionError:
    print ("caught divide-by-0 attempt")


try:
    1 / 0                               # print: Second argument to a division
except Exception as e:                  # or modulo operation was zero.
    print (e.__doc__)


try:
    try:
        1 / 0                           # print: caught an exception
    except:
        print ("caught an exception")
except ZeroDivisionError:
    print ("caught divide-by-0 attempt")


value = ['s']
print (repr(value), "is ", end=" ")
try:
    value + 0                 # ['s'] is neighter a number nor a string
except TypeError:
    try:
        value + ''
    except TypeError:
        print ("neigther a number nor a string")
    else:
        print ("a string or string-like value")
else:
    print ("some kind of number")


# *** try/finally ***
#    - has exacly 1 finally and cannot have an else clause
#    - finally is a clean-up handler
#    - code always execute after try terminates in any way
#    - if exception happend, after finally executes, exc. is propagated further
'''
try:
    statement(s)
finally:
    statement(s)
'''

f = open("/tmp/test_try.txt", "w")
try:
    print ("do_something_with_file(f)")   # do_something_with_file(f)
finally:
    f.close()


# *** Python 2.5 Exception-Related Enhancements ***

# The 'with' statement
#
# Implements C++ RAII concept
# The 'with' statement simplifies exception handling by encapsulating common
# preparation and cleanup tasks in so-called "context managers"
'''
with expression [as varname]
    statement(s)
'''

# which is translated to, or equivalent with:
'''
_normal_exit = True
_temporary = expression
varname = _temporary._ _enter_ _( )
try:
    statement(s)
except:
    _normal_exit = False
    if not _temporary._ _exit_ _(*sys.exc_info( )):
        raise
    # exception does not propagate if _ _exit_ _ returns a true value
finally:
    if _normal_exit:
        _temporary._ _exit_ _(None, None, None)
'''
class sendmsg(object):
    def __init__(self, channel, id):
        self.channel = channel
        self.id = id

    def text(self, txt):
        print ("send:", txt)

    def __enter__(self):
        print ("Open:", self.channel)
        print ("Contact:", self.id)
        return self

    def __exit__(self, etyp, einst, etb):
        print ("Say Bye:", self.id)
        print ("Close:", self.channel)
        print ("Exit")
        return True


with sendmsg('freenode', 'michael44') as sm:              # Open: freenode
    sm.text('Hello Michael.')                             # Contact: michael44
    sm.text('You are invited tonight at the reception')   # send: Hello Michael
    sm.text('Bring Michele also. See you there. Bye!')    # send: Bring ...
                                                          # Say Bye: michael44
                                                          # Close: freenode
                                                          # Exit


# Generator Enhancements
#
# Since 2.7 the generator has 2 more methods (throw & close)
'''
g.throw(exc_type, exc_value=None, exc_traceback=None)
g.close()
'''


def item_generator(lst=[]):
    for i, elem in enumerate(lst):
        try:
            yield elem
        except Exception:
            raise Exception("error during index: %d" % i)


try:
    lst = list([1, 2, 3, 0, -100])
    gen = item_generator(lst)
    for i in gen:
        if i < 0:
            gen.throw(ValueError, "vad value")
except:
    print ("don't know yet how to print the message")  # don't know yet ...

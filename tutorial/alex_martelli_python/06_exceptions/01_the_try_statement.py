#
# The 'try' statement
#
'''
try:
    statement(s)
except: [expression [, target]]:
    statement(s)
[else:
    statement(s)]
'''


# simplistic
try:
    1 / 0
except ZeroDivisionError:
    print "caught divide-by-0 attempt"


# more generic
# prints: Second argument to a division or modulo operation was zero.
try:
    1 / 0
except Exception, e:
    print e.__doc__


try:
    try:
        1 / 0
    except:
        print "caught an exception"
except ZeroDivisionError:
    print "caught divide-by-0 attempt"
# prints: caught an exception


value = ['s']
print repr(value), "is ",
try:
    value + 0
except TypeError:
    # not a number, maybe a string, Unicode, UserString...?
    try:
        value + ''
    except TypeError:
        print "neigther a number nor a string"
    else:
        print "a string or string-like value"
else:
    print "some kind of number"


# try/finally
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
    print "do_something_with_file(f)"
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
        print "send:", txt

    def __enter__(self):
        print "Open:", self.channel
        print "Contact:", self.id
        return self

    def __exit__(self, etyp, einst, etb):
        print "Say Bye:", self.id
        print "Close:", self.channel
        print "Exit"
        return True


with sendmsg('freenode', 'michael44') as sm:
    sm.text('Hello Michael.')
    sm.text('You are invited tonight at the reception')
    sm.text('Bring Michele also. See you there. Bye!')


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
            raise Exception, "error during index: %d"%i

try:
    lst = list([1, 2, 3, 0, -100])
    gen = item_generator(lst)
    for i in gen:
        if i < 0:
            gen.throw(ValueError, "vad value")
except:
    print "don't know yet how to print the message" # :(

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

try:
    1 / 0
except ZeroDivisionError:
    print "caught divide-by-0 attempt"


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
'''
with expression [as varname]
    statement(s)
'''
with x = [0, 1, 2, 3, 4]:
    for i in x:
        print i

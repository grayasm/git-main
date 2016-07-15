#
# Decorators
#
# A handy notation to decorate a function A with a notation @B
# A call of the form A = B(A) will be placed at the end of the decorated
# function. This is exactly the syntax used for class-level methods like
# staticmethod and classmethod.

# Example for 'classmethod' or 'staticmethod'

class Classic(object):
    def double(x):
        return x*2
    double = classmethod(double)

# a decorator calls a function with the same name right after the decorated
# block.

class Decorated(object):
    @classmethod
    def double(x):
        return x*2


# or this example:
def showdoc(f):
    if f.__doc__:
        print '%s: %s' % (f.__name__, f.__doc__)
    else:
        print '%s: No docstring!' % f.__name__
    return f


@showdoc
def f1(): "a docstring"      # prints: f1: a docstring

@showdoc
def f2(): pass               # prints: f2: No docstring!

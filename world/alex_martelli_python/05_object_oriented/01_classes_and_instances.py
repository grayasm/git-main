# -----------------------------------------------------------------------------
# Python Classes
#
# syntax: class classname(base-classes):
#               statement(s)


# *** Attributes of class objects ***

class C1(object):
    x = 23            # attribute
print C1.x            # prints: 23


class C2(object):
    pass
C2.x = 23             # bind attribute from outside
print C2.x            # prints: 23


print C1.__name__     # prints: C1
print C1.__bases__    # prints: (<type 'object'>,)
print C1.__dict__

# prints: {'__dict__': <attribute '__dict__' of 'C1' objects>,
#          'x': 23,
#          '__module__': '__main__',
#          '__weakref__': <attribute '__weakref__' of 'C1' objects>,
#          '__doc__': None}

C1.y = 45
C1.z = 67
z = C1.__dict__['z']
print C1.x, C1.y, z        # prints: 23, 45, 67


class C3(object):
    x = 23
    y = x + 22                # must use just x, not C3.x


class C4(object):
    x = 23

    def method(self):
        print C4.x            # must use C4.x, not just x


# *** Function definitions in a class body ***
class C5(object):

    def hello(self):
        print "Hello"


# *** Class-private variables ***
class A():
    __ident = 100
a = A()
print a._A__ident      # prints: 100


# *** Class documentation strings ***
class A():
    '''If the first statement in the class body is a
    string literal, the compiler binds that string as
    the documentation string attribute for the class.'''
    pass
a = A()
print a.__doc__   # prints: '''If the first ....


# *** Descriptors ***
# non-overriding descriptor: class has only __get__
# overriding descriptor    : class has __set__
# example:
class A(object):
    '''Strange: accessing class object through derived class from outside,
    either setting a new value or retrieving the value will call automatically
    get and set'''

    def __init__(self, initval=None, name='var'):
        self.val = initval
        self.name = name

    def __get__(self, obj, objtype):
        print 'Retrieving', self.name
        return self.val

    def __set__(self, obj, val):
        print 'Updating', self.name
        self.val = val


class B(object):
    x = A(10, 'var "x"')
    y = 5

m = B()
print m.x       # prints: Retrieving var "x"  \n10
m.x = 20        # prints: Updating var "x"
print m.y       # prints: 5


# *** Instances ***
anInstance = C5()
print isinstance(anInstance, C5)  # prints: True


class C6(object):

    def __init__(self, n):        # __init__ parameters
        self.x = n
anotherInstance = C6(42)

anInstance.hello()        # prints: Hello
print anotherInstance.x   # prints: 42


class C7(object):
    pass
z = C7()
z.x = 23             # arbitrary attribute
print z.x            # prints: 23


print z.__class__.__name__, z.__dict__  # prints: C7 {'x': 23}
z.y = 45
z.__dict__['z'] = 67
print z.x, z.y, z.z  # prints: 23 45 67


# *** The factory-function idiom ***

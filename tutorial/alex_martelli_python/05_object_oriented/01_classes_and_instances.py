#
# pag. 82, Classes and Instances
#          If you're already familiar with object-oriented programming in
#          other languages such as C++ or Java, then you probably have a
#          good intuitive grasp of classes and instances: a class is a
#          user-defined type, which you can instantiate to obtain instances,
#          meaning objects of that type. Python supports these concepts through
#          its class and instance objects.


# *** Python Classes ***
# *** The class Statement ***

# *** The Class Body ***
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


class C5(object):
    def hello(self):          # function definition in a class body
        print "Hello"


class A():
    __ident = 100      # private variable starts with __
a = A()                # and its changed by compiler into _classname__variable
print a._A__ident      # prints: 100


# Class documentation strings
class A():
    '''If the first statement in the class body is a
    string literal, the compiler binds that string as
    the documentation string attribute for the class.'''
    pass


a = A()
print a.__doc__   # prints: If the first ....


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


# __init__
class C6(object):

    def __init__(self, n):
        self.x = n
anotherInstance = C6(42)


# attributes of instance objects
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


# The factory-function idiom
# similar with C++ singleton
class SpecialCase(object):
    def amethod(self): print "special"


class NormalCase(object):
    def amethod(self): print "normal"


def appropriateCase(isnormal=True):
    if isnormal: return NormalCase()
    else: return SpecialCase()

aninstance = appropriateCase(isnormal=False)
aninstance.amethod()     # prints: "special", as desired


# __new__
x = C6.__new__(C6, 23)
if isinstance(x, C6):
    type(x).__init__(x, 23)


# __new__ may choose to return an existing instance or make a new one,
# as appropriate.
# Example of how to override static method __new__ in order to implement
# a version of the Singleton desing pattern.

class Singleton(object):
    _singletons = {}

    def __new__(cls, *args, **kwds):
        if cls not in cls._singletons:
            cls._singletons[cls] = super(Singleton, cls).__new__(cls)
        return cls._singletons[cls]


# *** Attribute Reference Basics ***
#    - syntax: x.name

class B(object):
    a = 23
    b = 45

    def f(self):
        print "method f in class B"

    def g(self):
        print "method g in class B"


class C(B):
    b = 67
    c = 89
    d = 123

    def g(self):
        print "method g in class C"

    def h(self):
        print "method h in class C"


x = C()
x.d = 77
x.e = 88

print C.__name__   # prints: C
print C.__bases__  # prints: (<class '__main__.B'>,)
print x.__class__  # prints: <class '__main__.C'>
print x.__dict__   # prints: {'e': 88, 'd': 77}


# Getting an attribute from a class.
# Getting an attribute from an instance.
print x.e, x.d, x.c, x.b, x.a  # prints: 88 77 89 67 23



# *** Bound and Unbound Methods
# - bound method - associated with an instance
# - unbound method - not associated with a particular instance

print x.h, x.g, x.f, C.h, C.g, C.f

# prints: <bound method C.h of <__main__.C object at 0x23af150>>
#         <bound method C.g of <__main__.C object at 0x23af150>>
#         <bound method C.f of <__main__.C object at 0x23af150>>
#         <unbound method C.h> <unbound method C.g> <unbound method C.f>

x.h()   # prints: method h in class C

# call unbound method passing a specific instance as parameter
C.h(x)  # prints: method h in class C


# Unbound method details
# 'im_class' 'im_func' 'im_self'

print C.h.im_class   # prints: <class '__main__.C'>
print C.h.im_func    # prints: <function h at 0x21dbc08>
print C.h.im_self    # prints: None

print x.h.im_class   # prints: <class '__main__.C'>
print x.h.im_func    # prints: <function h at 0x1d90c08>
print x.h.im_self    # prints: <__main__.C object at 0x1d97150>


# low-level detail of the method call with the normal syntax: x.name(arg)
def f(a, b):
    print a, b


class C(object):
    name = f
x = C()
x.name(33)  # prints: <__main__.C object at 0x850210> 33

# x.name(33) can be written also as:
x.__class__.__dict__['name'](x, 33)


# closures concept
def make_adder_as_closure(augend):
    def add(addend, _augend=augend):
        return addend + _augend
    return add


# bound method concept
def make_adder_as_bound_method(augend):
    class Adder(object):
        def __init__(self, augend):
            self.augend = augend

        def add(self, addend):
            return addend + self.augend
    return Adder(augend).add


# callable instance concept
def make_adder_as_callable_instance(augend):
    class Adder(object):
        def __init__(self, augend):
            self.augend = augend

        def __call__(self, addend):
            return addend + self.augend
    return Adder(augend)


# add 5 + 6
fn_closure = make_adder_as_closure(0)
fn_bound = make_adder_as_bound_method(6)
fn_callable = make_adder_as_callable_instance(6)

a = fn_closure(5, 6)
b = fn_bound(5)
c = fn_callable(5)
print a, b, c    # prints: 11 11 11


# *** Inheritance ***

# Method resolution order
# The problem with purely left-right, depth-first search, in situations of
# multiple inheritance, example:

class Base1:
    def amethod(self): print "Base1"


class Base2(Base1):
    pass


class Base3(Base1):
    def amethod(self): print "Base3"


class Derived(Base2, Base3):
    pass

aninstance = Derived()
aninstance.amethod()  # prints: "Base1"


# Overriding attributes
class B(object):
    a = 23
    b = 45
    def f(self): print "method f in class B"
    def g(self): print "method g in class B"

class C(B):
    b = 67
    def g(self): print "method g in class C"


# Delegating to superclass methods
# C++ - calling the overriden method from base
class Base(object):
    def greet(self, name): print "Welcome ", name
class Sub(Base):
    def greet(self, name):
        print "Well Met and",
        Base.greet(self, name)

x = Sub()
x.greet('Alex')


# python != c++  the base class __init__ is not called when a derived
#                class instance get instantiated
# example:
class Base(object):
    def __init__(self):
        self.anattribute = 23
class Derived(Base):
    def __init__(self):
        Base.__init__(self)
        self.anotherattribute = 45


# Cooperative superclass method calling
class A(object):
    def met(self):
        print 'A.met'
class B(A):
    def met(self):
        print 'B.met'
        A.met(self)
class C(A):
    def met(self):
        print 'C.met'
        A.met(self)
class D(B,C):
    def met(self):
        print 'D.met'
        B.met(self)
        C.met(self)


d = D()
d.met()   # prints: D.met B.met A.met C.met A.met



# *** The Built-in object Type ***
# It is the ancestor of all built-in types and new style classes.
'''shortly mentioned here:
__new__
__init__
__delattr__
__getattribute__
__setattr__
__hash__
__repr__
__str__
'''


# *** Class-Level Methods ***

# Static methods
# can call a static method with or without an instance

class AClass(object):
    def astatic():
        print 'a static method'
    astatic = staticmethod(astatic)
aninstance = AClass()
AClass.astatic()       # prints: a static method
aninstance.astatic()   # prints: a static method


# Class methods
# create a class method with built-in 'classmethod'

class ABase(object):
    def aclassmet(cls):
        print 'a class method for', cls.__name__
    aclassmet = classmethod(aclassmet)


class ADeriv(ABase):
    pass

bInstance = ABase()
dInstance = ADeriv()
ABase.aclassmet()       # prints: a class method for ABase
bInstance.aclassmet()   # prints: a class method for ABase
ADeriv.aclassmet()      # prints: a class method for ADeriv
dInstance.aclassmet()   # prints: a class method for ADeriv


# *** Properties ***
# syntax: attrib = property(fget=None, fset=None, fdel=None, doc=None)

# It is an instance attribute with special functionality.
# Does not follow semantics of normal rules: referencing, binding, unbinding,
# as well as OO concepts of accessors and mutators but it follows the
# 'property' concept which may allow different get,set,del methods.


# Example of a read-only attribute 'area' calculated on-the-fly.
class Rectangle(object):
    def __init__(self, width, height):
        self.width = width
        self.height = height

    def getArea(self):
        return self.width * self.height
    area = property(getArea, doc='area of the rectangle')


# Properties and Inheritance
# Properties are not overriden in subclasses.
# Example:

class B(object):
    def f(self): return 23
    g = property(f)
class C(B):
    def f(self): return 42
c = C()
print c.g    # prints: 23


# Achieving to override a property by using an extra level of indirection
class B(object):
    def f(self): return 23
    def _f_getter(self): return self.f()
    g = property(_f_getter)
class C(B):
    def f(self): return 42
c = C()
print c.g    # prints: 42, as expected


# *** __slots__ ***
#
# Introduced to reduce memory on each class instance, it is a trade-off for
# code that has millions of instances of an object. __slots__ replaces the
# __dict__ attribute.

class OptimizedRectangle(Rectangle):
    __slots__ = 'width', 'height'



# *** __getattribute__ ***

#
# Method gets called for all instance attributes. Override this method to
# implement specific behavior.
class listNoAppend(list):
    def __getattribute__(self, name):
        if name == 'append': raise AttributeError, name
        return list.__getattribute__(self, name)

x = listNoAppend((1, 2, 3, 4, 5))
# x.append(6)      AttributeError: append



# *** Per-Instance Methods ***

#
# Old-Style-class vs New-Style-class in python with different binding behavior


class OldStyle:
    pass
class NewStyle(object):
    pass

def fakeGet(n):
    return n

c = OldStyle()
n = NewStyle()
c.__getitem__ = fakeGet
n.__getitem__ = fakeGet

print c[23]
# print n[23]  TypeError: 'NewStyle' object does not support indexing


# *** Inheritance from Built-in Types ***
class newdict(dict):
    pass

class newlist(list):
    pass

# cannot inherit from 2 non-compatible types
# class noway(dict, list):
#     pass
'''TypeError: Error when calling the metaclass bases
   multiple bases have instance lay-out conflict'''

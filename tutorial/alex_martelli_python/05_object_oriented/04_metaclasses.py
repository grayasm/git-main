#
# pag. 117, Metaclasses
#           Any object, even a class object, has a type. In Python, types and
#           classes are also first-class objects. The type of a class is also
#           known as the class's metaclass. An object's behavior is mostly
#           determined by the type of the object. This also holds for classes:
#           a class's behavior is mostly determined by the class's metaclass.


# *** How Python Determines a Class's Metaclass ***

# The 'type' class object is also known as the class's metaclass.
# Old-style and New-style classes have different metaclasses.

class Classic: pass
class Newstyle(object): pass
print type(Classic)       # prints: <type 'classobj'>
print type(Newstyle)      # prints: <type 'type'>



# *** How a Metaclass Creates a Class ***
# Defining and using your own metaclasses.
class MyMeta(type):
    def __str__(cls):
        return "Beautiful class '%s'"%cls.__name__

class MyClass:
    __metaclass__ = MyMeta

x = MyClass()
print type(x)         # prints: Beautiful class 'MyClass'


# A substantial custom metaclass example
# here a struct type like in C, initializing with a variable parameter list
class Bunch(object):
    def __init__(self, **fields):
        self.__dict__ = fields

p = Bunch(x=2.3, y=4.5)
print p               # prints: <__main__.Bunch object at 0x182de90>


# A very long and complex metaMetaBunch metaclass (book Example 5-1)
import warnings

class metaMetaBunch(type):
    def __new__(mcl, classname, bases, classdict):
        def __init__(self, **kw):
            for k in self.__dflts__:
                setattr(self, k, self.__dflts__[k])

            for k in kw:
                setattr(self, k, kw[k])

        def __repr__(self):
            rep = ['%s=%r' % (k, getattr(self, k)) for k in self.__dflts__
                   if getattr(self, k) != self.__dflts__[k]
            ]
            return '%s(%s)' % (classname, ', '.join(rep))

        newdict = {'__slots__':[ ], '__dflts__': { },
                   '__init__':__init__, '__repr__': __repr__, }
        for k in classdict:
            if k.startswith('__') and k.endswith('__'):
                if k in newdict:
                    warnings.warn("Can't set attr %r in bunch-class %r"
                                  % (k, classname))
                else:
                    newdict[k] = classdict[k]
            else:
                newdict['__slots__'].append(k)
                newdict['__dflts__'][k] = classdict[k]
        return super(metaMetaBunch, mcl).__new__(
            mcl, classname, bases, newdict)

class MetaBunch(object):
    __metaclass__ = metaMetaBunch


class Point(MetaBunch):
    """
    A point has x and y coordinates, defaulting to 0.0, and a color,
    defaulting to 'gray' -- and nothing more, except what Python and
    the metaclass conspire to add, such as __init__ and __repr__
    """
    x = 0.0
    y = 0.0
    color = 'gray'

# example uses of class Point
q = Point()
print q               # prints: Point
p = Point(x=1.2, y=3.4)
print p               # prints: Point(y=3.4, x=1.2)

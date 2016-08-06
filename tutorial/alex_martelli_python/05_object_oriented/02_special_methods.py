#
# Special Methods

# *** General-Purpose Special Methods ***
# Initialization and finalization
'''
__new__
__init__
__del__'''

# Representation as string
'''
__repr__
__str__
__unicode__'''

# Comparison, hashing and use in a Boolean context
'''
__lt__
__le__
__gt__
__ge__
__eq__
__ne__
__cmp__
__hash__
__nonzero__'''

# Attribute reference, binding and unbinding
'''
__getattribute__
__getattr__
__setattr__
__delattr__'''

# Callable instances
'''
__call__'''


# Examples: http://stackoverflow.com/questions/1061283/lt-instead-of-cmp
class A(object):
    def __init__(self, value):
        self.value = value
    def __cmp__(self, other):
        assert isinstance(other, A)
        return cmp(self.value, other.value)


print cmp(A(4), A(5))   # prints: -1
print cmp(A(7), A(7))   # prints: 0
print cmp(A(8), A(4))   # prints: 1


# override __eq__, __ne__, __gt__, __ge__, __le__
class A(object):
    def __init__(self, value):
        self.value = value

    def __eq__(self, other):
        assert isinstance(other, A)
        return self.value == other.value

    def __ne__(self, other):
        assert isinstance(other, A)
        return self.value != other.value

    def __gt__(self, other):
        assert isinstance(other, A)
        return self.value > other.value

    def __ge__(self, other):
        assert isinstance(other, A)
        return self.value >= other.value

    def __le__(self, other):
        assert isinstance(other, A)
        return self.value <= other.value

print A(5) <= A(8)  # prints: True
print A(2) >= A(8)  # prints: False


# *** Special Methods for Containers ***
#
# For usefullness containers should provide special and non-special methods.
# Special methods:
'''
__getitem__
__setitem__
__delitem__
__len__
__contains__
__iter__'''

# Non-special methods depend on container type.
# Sequences:
'''
__add__
__mul__
__radd__
__rmul__
__iadd__
__imul__
append
count
index
insert
extend
pop
remove
reverse
sort
'''

# Mappings:
'''
copy
get
has_key
items
keys
values
iteritems
iterkeys
itervalues
'''

# Sets
'''
copy
difference
intersection
issubset
issuperset
symatric_different
union
...etc
'''

# Container slicing
#
# Slicing a[1:3] uses a generator over the container or customer container.
# The generator uses __getitem__ special method to walk over items.

class A(object):
    def __init__(self, alist=[]):
        self.alist = alist

    def __getitem__(self, pos):
        if isinstance(pos, int):
            return self.alist[pos]
        else:
            raise TypeError, "Index should be integer!"

a = A([1e-3, 1e-2, 1e-1])
for i in a:
    print i  # prints: 0.001  0.01  0.1


# __getslice__ example
class C(tuple):
    def __getslice__(self, i, j): print 'getslice', i, j
    def __getitem___(self, index): print 'getitem', index

x = C()
x[12:34]      # prints: getslice 12 34
x[56:78:9]    # prints:


# My all in one example:
class M(list):
    def __init__(self, mylist=[]):
        self.mylist = mylist

    def __contains__(self, elem):
        for i in self.mylist:
            if i == elem:
                return True
        return False

    def __delitem__(self, pos):
        return self.mylist.__delitem__(pos)

    def __getitem__(self, pos):
        return self.mylist.__getitem__(pos)

    def __iter__(self):
        return self.mylist.__iter__()

    def __len__(self):
        return self.mylist.__len__()

    def __setitem__(self, pos, val):
        return self.mylist.__setitem__(pos, val)


a = M([-1, 0, 1, -5])    # [-1, 0, 1, -5]
del a[-1]                # [-1, 0, 1]
a[1] = 100               # [-1, 100, 1]
print -1 in a            # True
print len(a)             # 3

''' other methods like print a, or sort(a) do not work'''


# *** Special Methods for Numeric Objects ***
'''
__abs__, __invert__, __neg__, __pos__
__add__, __div__, __floordiv__, __mod__, __mul__, __sub__, __truediv__
__and__, __lshift__, __or__, __rfhit__, __xor__
__coerce__
__complex__, __float__, __int__, __long__, __divmod__
__hex__, __oct__
__iadd__, __idiv__, __ifloordiv__, __imod__, __imul__, __isub__, __itruediv__
__iand__, __ilshift__, __ior__, __irshift__, __ixor__
__index__
__ipow__
__pow__
__radd__, __rdiv__, __rmod__, __rmul__, __rsub__
__rand__, __rlshift__, __ror__, __rrshift__, __rxor__
__rdivmod__
__rpow__
'''


# http://stackoverflow.com/questions/4233628/override-mul-from-a-child-class-using-parent-implementation-leads-to-proble
from numbers import Number
class MyFloat(object):
    def __init__(self, a):
        self.a = a

    def __mul__(self, other):
        return type(self)(self.a * other.a)

    def __repr__(self):
        return str(self.a)

class MyFloatEx(MyFloat):
    def __init__(self, a):
        super(MyFloatEx, self).__init__(a)

    def __add__(self, other):
        return type(self)(self.a + other.a)

    def __mul__(self, other):
        if isinstance(other, Number):
            return type(self)(self.a * other)
        else:
            return super(MyFloatEx, self).__mul__(other)

a = MyFloatEx(0.5)
b = MyFloatEx(1.5)

c = a + b
print "c=", c      # prints: 2.0

d = a * b
print "d=", d      # prints: 0.75


e = d * c
print "e=", e      # prints: 1.5

print "e is MyFloat=", isinstance(e, MyFloat)  # prints: True

f = e * 0.5
print "f=", f      # pritns: 0.75

print map(type,[a, b, c, d, e, f]) == [MyFloatEx]*6   # prints: True

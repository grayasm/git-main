#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# pag. 158, Built-in Functions
#           This section documents the Python functions available in module
#           __builtin__ in alphabetical order. Note that the names of these
#           built-ins are not reserved words. Thus, your program can bind for
#           its own purposes, in local or global scope, an identifier that has
#           the same name as a built-in function. Names bound in local or
#           global scope have priority over names bound in built-in scope, so
#           local and global names hide built-in ones. Be very careful,
#           to avoid accidentally hiding built-ins that your code might need.
#           It’s tempting to use, for your own variables, natural names such as
#           file , input , list , filter , but don’t do it: these are all
#           names of built-in Python types or functions, and, unless you get
#           into the habit of never shadowing such built-in names with your
#           own, you’ll end up with some mysterious bug in your code


'''
__import__  __import__(module_name[,globals[,locals[,fromlist]]])
abs         abs(x)
all         all(seq)
any         any(seq)
callable    callable(obj)
chr         chr(code)
cmp         cmp(x,y)
coerce      coerce(x,y)
compile     compile(string,filename,kind)
delattr     delattr(obj,name)
dir         dir([obj])
divmod      divmod(dividend,divisor)
eval        eval(expr,[globals[,locals]])
execfile    execfile(filename,[globals[,locals]])
filter      filter(func,seq)
getattr     getattr(obj,name[,default])
globals     globals()
hasattr     hasattr(obj,name)
hash        hash(obj)
hex         hex(x)
id          id(obj)
input       input(prompt='')
intern      intern(string)
isinstance  isinstance(obj,cls)
issubclass  issubclass(cls1,cls2)
iter        iter(obj)
            iter(func,sentinel)
len         len(container)
locals      locals()
map         map(func,seq,*seqs)
max         max(s,*args)
min         min(s,*args)
oct         oct(x)
ord         ord(ch)
pow         pow(x,y[,z])
range       range([start,]stop[,step=1])
raw_input   raw_input(prompt='')
reduce      reduce(func, seq[,init])
reload      reload(module)
repr        repr(obj)
round       round(x,n=0)
setattr     setattr(obj,name,value)
sorted      sorted(seq,cmp=None,key=None,reverse=False)
sum         sum(seq,start=0)
unichr      unichr(code)
vars        vars([obj])
zip         zip(seq,*seqs)
'''

abs(-3.3)           # 3.3
all([-1, 0, True])  # False, not all elements are true
any([-1, 0])        # True, if any is true


# 'callable'
class A(object):
    def __call__(self):
        print ('Yes, it\'s callable')


callable(A())       # True
chr(65)             # ASCII 65='A' prints: A


# 'compile'
pycode = str("x=-5\n"
             "y=11\n"
             "l = [x, y, 0]\n"
             "print (l)\n")
codeobj = compile(pycode, 'fakefile', 'exec')
exec(codeobj)


# 'delattr'
class A(object):
    def __init__(self, v):
        self.value = v


class B(object):
    def __init__(self, v):
        self.value = v


a = A(10)
b = B(20)
del a.value
delattr(b, "value")
dir()

# ['A', 'B', '__builtins__', '__doc__', '__file__', '__name__', '__package__',
#  'a', 'b', 'codeobj', 'l', 'pycode', 'x', 'y']

dir(a)
# ['__class__', '__delattr__', '__dict__', '__doc__', '__format__',
#  '__getattribute__', '__hash__', '__init__', '__module__', '__new__',
#  '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__',
#  '__str__', '__subclasshook__', '__weakref__']

divmod(10, 3)   # (3, 1)  as (quotient, remainder)

# 'eval'  eval(expr, [globals[, locals]])
x = 100
eval('x - 1')   # 99


# 'filter' filter(func, seq)   ;func-functor,seq-container,filter-looping fn.
seq = ['a', 'k', 'l', 'm', 'u', 'w', 'z']


def func(i):
    if i > 'a' and i < 'u':
        return True
    else:
        return False


filter(func, seq)     # ['k', 'l', 'm']

# 'getattr' getattr(obj, name [,default])

l = ['Larry', 'Curly']              # ['Larry', 'Curly']
getattr(l, "append")("Moe")         # ['Larry', 'Curly', 'Moe']

# global() - returns the __dict__ of the calling module.

# {'A': <class '__main__.A'>,
#  'a': <__main__.A object at 0x7f5d5f656b50>,
#  'B': <class '__main__.B'>,
#  'seq': ['a', 'k', 'l', 'm', 'u', 'w', 'z'],
#  '__builtins__': <module '__builtin__' (built-in)>,
#  ... long dict.

# 'hasattr'  hasattr(obj,name)
a = A(100)
if hasattr(a, 'value'):
    a.value = 200

# hash(obj)
l = ['ana', 'maria-julia', 'ana-maria-francesca']
for name in l:
    hash(name)

# variable-length-string ->hash()->fixed length number
#  1453079729200098181
# -2576405097883951031
#  5336425957926601139

hex(20)   # 0x14
id(l)     # 140502640239680

# input(message) - prompts user with message and request input from stdin
# input(raw_input(message))

'''
message = 'introduce x:'
x = input(message)
'''

# intern(string)   - string is stored in (fast) internal memory
# in python3 intern is sys.intern
import sys
intern_is_faster = sys.intern("this string should be compared fast")
extern_is_clean = "this string should be compared fast"
intern_is_faster is extern_is_clean   # True


# isinstance(obj, cls)
l = []
isinstance(l, list)     # True


# issubclass(cls1, clas2)
class C1(object):
    pass


class C2(C1):
    pass


issubclass(C2, C1)      # True


# iter(obj)
# iter(func, sentinel)
l = ['daniel', 'maria-julia', 'ana-maria']
for name in iter(l):
    pass

len(l)   # 3
locals()
# {'A': <class '__main__.A'>,
#  'a': <__main__.A object at 0x7f3c15b1dcd0>,
#  'B': <class '__main__.B'>,
#  'name': 'ana-maria',
#  'seq': ['a', 'k', 'l', 'm', 'u', 'w', 'z'],
#  ... really huge dictionary.


# map(func, seq, **seqs)
# map(func, seq) is like:
#    [func(item) for item in seq]
seq = ['maria-julia', 'ana-maria', 'daniel']


def func(name):
    if name == 'daniel':
        return ''
    else:
        return name


map(func, seq)    # ['maria-julia', 'ana-maria', 'daniel']
seq               # ['maria-julia', 'ana-maria']

max(seq)          # maria-julia  (lexicographically '[m]aria-julia > [d]aniel)
min(seq)          # ana-maria    (lexicographically '[a]na-maria < [d]aniel)

oct(20)           # 024

ord('A')          # 65
ord(u'六')        # 20845 - japaneese digit 6
pow(3, 3)         # 27
range(10, 30, 5)  # 10, 15, 20, 25, 30

# 'raw_input'
'''
message="give x:"
x = raw_input(message)
'''

# reduce(func,seq[,init])     ; similar with:
'''
def reduce(func,seq,init=None):
    seq = iter(seq)
    if init is None: init = seq.next()
    for item in seq: init = func(init,item)
    return init
'''
# python3 moved reduce() to functools.reduce()
import functools
functools.reduce(list.__add__, [[1, 2, 3], [4, 5], [6, 7, 8]], [])
# prints: [1,2,3,4,5,6,7,8]


# reload(module)
# repr(obj)
class A(object):
    def __init__(self, v):
        self.value = v

    def __repr__(self):
        return str(self.value)


repr(A(1.33))          # 1.33
repr(A('some text'))   # some text
round(1.123456789, 3)  # 1.123


# setattr(obj,name,value)         ; binds obj's attribute name with the value
class A(object):
    pass


a = A()
setattr(a, 'value', 1.33)   # a.value = 1.33


# sorted(seq,cmp=None,key=None,reverse=False)   ; similar with:
'''
def sorted(seq,cmp=None,key=None,reverse=False):
    result = list(seq)
    result.sort(cmp,key,reverse)
    return result
'''
sorted([5, 2, 3, 1, 4])    # [1, 2, 3, 4, 5]
d = {1: 'D', 2: 'B', 3: 'B', 4: 'E', 5: 'A'}
sorted(d)                  # [1, 2, 3, 4, 5]

l = [1, 1, 1]
sum(l, 5)   # 8

# unichr(code)        ; returns a Unicode string for the [0, 65535] code
code = ord(u'六')


# vars()            ; returns a dict with all variables in current scope
# vars(obj)         ; returns a dict with all attributes bound to obj

x = 1.123456789
vars()['x']         # 1.123456789

# zip(seq,*seqs)    ; returns a list of tuples for the shortest length
alist = ['a1', 'a2', 'a3']
blist = ['b1', 'b2', 'b3', 'b4']

for a, b in zip(alist, blist):
    a, b

# a, b pairs:
'''
a1 b1
a2 b2
a3 b3
'''

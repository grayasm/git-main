#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# pag. 46, Variables and Other References
#          A Python program accesses data values through references.
#          A reference is a name that refers to the location in memory of
#          a value (object). References take the form of variables,
#          attributes and items. In Python, a variable or other reference
#          has no intrinsic type. The object to which a reference is bound
#          at a given time always has a type, but a given reference may be
#          bound to objects of various types during the program's execution.


# *** Variables ***
#    - everything in Pyton is an Object
#    - binding operation connects a Name with an Object (implicit)
#    - rebinding operation binds a reference that was already bound (implicit)
#    - object dissapears when nothing refers it (implicit)
#    - unbinding operation disconnects the Name from the Object
#      'del' statement unbinds the Name and deletes the Object (explicit)

name = [10, 99, 42, 22, 11]

# *** Assignament Statements ***
'''
  Plain assignament is how you createa a new variable or rebind an existing
  one to a new value:
    name = value
    x.attr = value
    x[k] = value
  Augmented assignament does not create new references.
  It can:
      (1) rebind a variable
      (2) ask an object to rebind one of its existing attributes or items
      (3) request the target object to modify itself (up to the object to
          honor the request of raise an exception.
    name += value
'''

# Attribute reference
class car():
    doors = 4

x = car()
x.doors = 10
print ("car.doors= %d" % x.doors)

# An indexing
x = {'a': 1, 'b': 2}
x['a'] = 200
print (x)

# A slicing
x = (10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)
y = x[0:8:2]                            # for(i=0; i<8; i+=2)
z = x[::3]                              # for(i=0; i<max; i+=3)
w = x[0:2]                              # for(i=0; i<2; i++)
print ("slicing x[0:8:2]= ", y)
print ("slicing x[::3]  = ", z)
print ("slicing x[0:2]  = ", w)


# Augmented assignament
x = 10
x *= -8
print ("x = ", x)  # -80


# *** del Statements ***
del x            # deleted object referenced by name 'x'
# print x        # NameError: name 'x' is not defined

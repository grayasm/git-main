# -----------------------------------------------------------------------------
# Variables
#    * everything in Pyton is an Object
#    * binding operation connects a Name with an Object (implicit)
#    * rebinding operation binds a reference that was already bound (implicit)
#    * object dissapears when nothing refers it (implicit)
#    * unbinding operation disconnects the Name from the Object
#      'del' statement unbinds the Name and deletes the Object (explicit)

name = [10, 99, 42, 22, 11]


# Attribute reference
class car():
    doors = 4

x = car()
x.doors = 10
print "car.doors= %d" % x.doors

# An indexing
x = {'a': 1, 'b': 2}
x['a'] = 200
print x

# A slicing
x = (10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)
y = x[0:8:2]                            # for(i=0; i<8; i+=2)
z = x[::3]                              # for(i=0; i<max; i+=3)
w = x[0:2]                              # for(i=0; i<2; i++)
print "slicing x[0:8:2]= ", y
print "slicing x[::3]  = ", z
print "slicing x[0:2]  = ", w


# Augmented assignament
x = 10
x *= -8
print "x = ", x  # -80

# del statement
del x            # deleted object referenced by name 'x'
# print x        # NameError: name 'x' is not defined

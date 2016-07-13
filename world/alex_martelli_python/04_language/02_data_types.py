# -----------------------------------------------------------------------------
# Integer numbers

1,   23,   3493    # Decimal
01,  027,  06645   # Octal
0x1, 0x17, 0xDA5   # Hexadecimal

1L,   23L,   99999333493L     # Long decimal integers
01L,  027L,  01351033136165L  # Long octal integers
0x1L, 0x17L, 0x17486CBC75L    # Long hexadecimal integers

# Floating-point numbers
0., 0.0, .0, 1., 1.0, 1e0, 1.e0, 1.0e0

# Complex numbers
0j, 0.j, 0.0j, .0j, 1j, 1.j, 1.0j, 1e0j, 1.e0j, 1.0e0j

# -----------------------------------------------------------------------------
# Sequences
#    * ordered container of items, indexed by nonnegative integers.
#    * String, Tuple and List  (built-in sequences)

'this is a sequence'        # String
[42, 2, 4]                  # List
(100, 200, 300)             # Tuple


# Strings
print 'This is a literal string'

print "This is another literal string"

print 'A quote\' can be escaped but'

print "This way' is more readable"

print "A not very long string \
that spans two lines"

print "A not very long string\n\
that prints on two lines"

print """An even bigger
string that spans
three lines"""


# Tuples:
#   * immutable ordered sequence of items enclosed in (..)
#   * arbitrary objects that may be of different types

print (100, 200, 300)           # tuple with 3 items
print (3.14, )                  # tuple with 1 item
print ()                        # tuple empty (parantheses NOT optional!)
print tuple('wow')              # tuple built-in type, prints ('w','o','w')


# Lists:
#   * mutable ordered sequence of items enclosed in [ ...]
#   * The items of a list are arbitrary objects and may be of different types.

print [42, 3.14, 'hello']       # list with 3 items
print [100]                     # list with 1 item
print []                        # list empty
print list('wow')               # list built-in type, prints ['w','o','w']

# -----------------------------------------------------------------------------
# Set Operations
#
#    set: arbitrarily unordered collections of unique items
#    frozenset:  similar but immutable

a = set((2, -3, 4, 4, -3))        # set([2, 4, -3]), unordered, but unique
b = a.copy()                      # reference to a, elements are not copied
c = b.difference(a)               # set([])
d = b.intersection(a)             # set([2, 4, -3])
e = b.issubset(a)                 # True
f = b.issuperset(a)               # True
g = b.symmetric_difference(a)     # set([])
h = b.union(a)                    # set([2, 4, -3])
b.add(11)                         # set([2, 11, 4, -3])
b.clear()                         # set([])
a.discard(-3)                     # set([2, 4])
i = a.pop()                       # 2 poped, a=set([4])
a.remove(4)                       # set([])

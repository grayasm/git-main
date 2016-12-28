#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# pag. 183, The intertools Module
#           The iterools module offers many powerful, high-performance building
#           blocks to build or manipulate iterator objects. Manipulating
#           iterators is often better than manipulating lists thanks to
#           iterators’ intrinsic “lazy evaluation” approach: items of an
#           iterator are produced one at a time, as needed, while all the items
#           of a list (or other sequence) must exist in memory at the same time
#           (this “lazy” approach even makes it feasible to build and
#           manipulate unbounded iterators, while all lists must always have
#           finite numbers of items).

'''
itertools.chain(*iterables)
itertools.count(firstval=0)
itertools.cycle(iterable)
itertools.ifilter(func, iterable)
itertools.map(func, *iterables)
itertools.islice(iterable[,start],stop[,step])
itertools.zip(*iterables)
itertools.repeat(items[,times])
itertools.tee(iterable, n=2)
'''

import itertools


#    Merging and splitting iterators
#    https://pymotw.com/2/itertools/#merging-and-splitting-iterators

for i in itertools.chain([1, 2, 3], ['a', 'b', 'c']):
    print (i)                               # iterator over a sequence
                                            # 1 2 3 a b c

for i in zip([1, 2, 3], ['a', 'b', 'c']):   # iterator over a tuple
    print (i)                               # (1, 'a')
                                            # (2, 'b')
                                            # (3, 'c')

print ('Stop at 5:')
for i in itertools.islice(itertools.count(), 5):
    print (i)                               # islice: input iterator/index
                                            # 0 1 2 3 4

print ('Start at 5, Stop at 10:')
for i in itertools.islice(itertools.count(), 5, 10):
    print (i)                               # 5 6 7 8 9


print ('By tens to 100:')
for i in itertools.islice(itertools.count(), 0, 100, 10):
    print (i)                               # 0 10 20 30 40 50 60 70 80 90


r = itertools.islice(itertools.count(), 5)
i1, i2 = itertools.tee(r)

for i in i1:
    print ("i1:", i)                        # i1:0 i1:1 i1:2 i1:3 i1:4
for i in i2:
    print ("i2:", i)                        # i2:0 i2:1 i2:2 i2:3 i2:4


#    Converting inputs
#    https://pymotw.com/2/itertools/#converting-inputs

print ('Doubles:')
for i in map(lambda x: 2*x, range(5)):      # map applies function to iterator
    print (i)                               # 0 2 4 6 8

print ('Multiples:')
for i in map(lambda x, y: (x, y, x*y), range(5), range(5, 10)):
    print ('%d * %d = %d' % i)              # 0 * 5 = 0
                                            # 1 * 6 = 6
                                            # 2 * 7 = 14
                                            # 3 * 8 = 24
                                            # 4 * 9 = 36

print ('with startmap')
values = [(0, 5), (1, 6), (2, 7), (3, 8), (4, 9)]
for i in itertools.starmap(lambda x, y: (x, y, x*y), values):
    print ('%d * %d = %d' % i)              # 0 * 5 = 0
                                            # 1 * 6 = 6
                                            # 2 * 7 = 14
                                            # 3 * 8 = 24
                                            # 4 * 9 = 36


#    Producing new values
#    https://pymotw.com/2/itertools/#producing-new-values
i = 0
for item in itertools.cycle(['a', 'b', 'c']):
    i += 1
    if i == 6:
        break
    print ((i, item))                       # (1, 'a')
                                            # (2, 'b')
                                            # (3, 'c')
                                            # (4, 'a')
                                            # (5, 'b')

for i in itertools.repeat('over-and-over', 4):
    print (i)                               # over-and-over
                                            # over-and-over
                                            # over-and-over
                                            # over-and-over

for i in map(lambda x, y: (x, y, x*y), itertools.repeat(2), range(5)):
    print ('%d * %d = %d' % i)


#    Filtering
#    https://pymotw.com/2/itertools/#filtering
def check_item(x):
    print ('Testing:', x)
    return (x < 1)


for i in filter(check_item, [3, 2, 1, 0, -1]):
    print ('Yielding:', i)                  # Testing: 3
                                            # Testing: 2
                                            # Testing: 1
                                            # Testing: 0
                                            # Yielding: 0
                                            # Testing: -1
                                            # Yielding: -1

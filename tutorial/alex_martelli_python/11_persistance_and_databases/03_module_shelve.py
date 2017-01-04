#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# pag. 284, The shelve Module
#           The shelve module orchestrates modules cPickle (or pickle, when
#           cPickle is not available in the current Python installation),
#           cStringIO (or StringIO, when cStringIO is not available in the
#           current Python installation), and anydbm (and its underlying
#           modules for access to DBM-like archive files, as discussed in “DBM
#           Modules” on page 285) in order to provide a simple, lightweight
#           persistence mechanism.

#    From https://docs.python.org/3.4/library/shelve.html :
#    A "shelf" is a persistent, dictionary-like object. The difference with
#    "dbm" databases is that the values (not the keys!) in a shelf can be
#    essentially arbitrary Python objects — anything that the pickle module can
#    handle. This includes most class instances, recursive data types, and
#    objects containing lots of shared sub-objects.
#    The keys are ordinary strings.


#    From: http://stackoverflow.com/questions/14668475/pickle-versus-shelve-storing-large-dictionaries-in-python
#    shelve is a sort of on disk dictionary
import shelve
import os

bigd = {'a': 1, 'b': 2,  # ...
        }
print ("dictionary beg:", bigd)   # {'a': 1, 'b': 2}

d1 = shelve.open('my.shelve')     # dictionary
d1.update(bigd)
d1.close()

d2 = shelve.open('my.shelve')
value = d2['a']                   # d2['a'] is mutable, copy to a value first
value += 1
d2['a'] = value                   # store the copy right back, to persist it
d2.close()

d3 = shelve.open('my.shelve')
print ("dictionary end:", d3)         # <shelve.DbfilenameShelf object at 0x7..
print ("keys in shelve:", d3.keys())  # KeysView(<shelve.DbfilenameShelf obj..
print ("iterate keys  :", end=" ")    # a b
for k in d3.keys():
    print (k, end=" ")
print ()
d3.close()

os.unlink('my.shelve')            # clean

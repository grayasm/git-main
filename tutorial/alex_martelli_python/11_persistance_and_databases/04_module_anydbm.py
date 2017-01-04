#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# pag. 286, The anydbm Module
#           The anydbm module is a generic interface to any other DBM module.
#           anydbm supplies a single factory function.
'''
open(filename, flag='r', mode=o666)
'''

#    According to http://python3porting.com/stdlib.html in python3 db modules
#    were renamed as follows:
#    anydbm    in  dbm
#    dbhash    in  dbm.bsd
#    dbm       in  dbm.ndbm
#    dumbdb    in  dbm.dumb
#    gdbm      in  dbm.gnu
#    whichdbm  in  dbm

#    https://pymotw.com/2/anydbm/
#    anydbm provides a generic dictionary-like interface to DBM-style,
#    string-keyed databases.
#    anydbm is a front-end for DBM-style databases that use simple string
#    values as keys to access records containing strings.
#    It uses the whichdb module to identify dbhash, gdbm, and dbm databases,
#    then opens them with the appropriate module. It is used as a backend
#    for shelve, which knows how to store objects using pickle.



import dbm
import os

#    https://pymotw.com/2/anydbm/
#    Creating a new database
db1 = dbm.open('anydbm.db', 'c')  # 'c' create a new database when necessary,
                                  # 'n' create always
db1['key'] = 'value'
db1['today'] = 'Sunday'
db1['author'] = 'Doug'
db1.close()

print (dbm.whichdb("anydbm.db"))  # dbm.gnu


#    Open an existing database
db2 = dbm.open('anydbm.db', 'r')
try:
    print ('keys():', db2.keys())     # keys(): [b'today', b'author', b'key']
    k = db2.firstkey()
    while k is not None:
        v = db2[k]
        print ('iterating:', k, v)    # iterating: b'today' b'Sunday'
        k = db2.nextkey(k)            # iterating: b'author' b'Doug'
                                      # iterating: b'key' b'value'

    print ('db["author"] =', db2['author'])  # db["author"] = b'Doug'
finally:
    db2.close()


#    Error cases.
db3 = dbm.open('anydbm.db', 'w')
try:
    db3[1] = 'one'
except TypeError as err:
    # TypeError: gdbm mappings have bytes or string indices only
    print ('%s: %s' % (err.__class__.__name__, err))
finally:
    db3.close()


#    Trying with string key
db4 = dbm.open('anydbm.db', 'w')
try:
    db4['one'] = 1
except TypeError as err:
    # TypeError: gdbm mappings have byte or string elements only
    print ('%s: %s' % (err.__class__.__name__, err))
finally:
    db4.close()

#    Clean
os.unlink('anydbm.db')

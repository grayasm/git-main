#!/usr/bin/env python3
# -*- coding: utf-8 -*-

#    According to http://python3porting.com/stdlib.html in python3 db modules
#    were renamed as follows:
#    anydbm    in  dbm
#    dbhash    in  dbm.bsd
#    dbm       in  dbm.ndbm
#    dumbdb    in  dbm.dumb
#    gdbm      in  dbm.gnu
#    whichdbm  in  dbm


# example: https://docs.python.org/3/library/dbm.html
import dbm

# Open database, creating it if necessary.
with dbm.open('cache', 'c') as db:

    # Record some values
    db[b'hello'] = b'there'
    db['www.python.org'] = 'Python Website'
    db['www.cnn.com'] = 'Cable News Network'

    # Note that the keys are considered bytes now.
    assert db[b'www.python.org'] == b'Python Website'
    # Notice how the value is now in bytes.
    assert db['www.cnn.com'] == b'Cable News Network'

    # Often-used methods of the dict interface work too.
    print(db.get('python.org', b'not present'))

    # Storing a non-string key or value will raise an exception (most
    # likely a TypeError).
    # db['www.yahoo.com'] = 4

    key = db.firstkey()
    while key != None:
        print(key)
        key = db.nextkey(key)

# db is automatically closed when leaving the with statement.

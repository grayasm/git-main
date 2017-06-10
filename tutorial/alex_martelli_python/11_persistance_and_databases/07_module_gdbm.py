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


# https://docs.python.org/3.1/library/dbm.html#module-dbm.gnu

import dbm.gnu

# Open database, creating it if necessary.
db = dbm.gnu.open('cache', 'c')

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
db['www.yahoo.com'] = bytes(4)

# Close when done.
db.close()

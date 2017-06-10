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


from dbm import dumb

db = dumb.open("dumbdbm", "c")
db["first"] = "fear"
db["second"] = "surprise"
db["third"] = "ruthless efficiency"
db["fourth"] = "an almost fanatical devotion to the Pope"
db["fifth"] = "nice red uniforms"
db.close()

db = dumb.open("dumbdbm", "r")
for key in db.keys():
    print(repr(key), repr(db[key]))

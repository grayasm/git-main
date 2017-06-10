#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# example copied from:
# https://docs.python.org/2/library/sqlite3.html
import sqlite3

con = sqlite3.connect(":memory:")
con.execute("create table person (id integer primary key, firstname varchar unique)")

# Successful, con.commit() is called automatically afterwards
with con:
    con.execute("insert into person(firstname) values (?)", ("Joe",))


print("sqlite3.threadsafety=", sqlite3.threadsafety)


# con.rollback() is called after the with block finishes with an exception, the
# exception is still raised and must be caught
try:
    with con:
        con.execute("insert into person(firstname) values (?)", ("Joe",))
except sqlite3.IntegrityError:
    print ("couldn't add Joe twice")


#
# pag. 277, Chapter 11. Persistance and Databases
#
#           Python supports a variety of ways of making data persistent. One
#           such way, known as serialization, involves viewing the data as a
#           collection of Python objects. These objects can be saved, or
#           serialized, to a byte stream, and later loaded and recreated, or
#           deserialized, back from the byte stream. Object persistence is
#           layered on top of serialization and adds such features as object
#           naming. This chapter covers the built-in Python modules that
#           support serialization and object persistence.
#           Another way to make data persistent is to store it in a database.
#           One simple type of database is just a file format that uses keyed
#           access to enable selective reading and updating of relevant parts
#           of the data. This chapter covers Python standard library modules
#           that support several variations of this file format, known as DBM.
#           A relational database management system (RDBMS), such as MySQL or
#           Oracle, provides a more powerful approach to storing, searching,
#           and retrieving persistent data. Relational databases rely on
#           dialects of Structured Query Language (SQL) to create and alter a
#           database’s schema, insert and update data in the database, and
#           query the database according to search criteria. (This chapter does
#           not provide reference material on SQL. For that purpose, I
#           recommend SQL in a Nutshell, by Kevin Kline [O’Reilly].)
#           Unfortunately, despite the existence of SQL standards, no two
#           RDBMSes implement exactly the same SQL dialect. The Python standard
#           library does not come with an RDBMS interface. However, many free
#           third-party modules let your Python programs access a specific RDBMS
#           Such modules mostly follow the Python Database API 2.0 standard,
#           also known as the DBAPI. This chapter covers the DBAPI standard and
#           mentions some of the third-party modules that implement it.

/*  Cap.8   Data Types
    8.19.   Object Identifier Types

    psql -d mytestdb -U pgmihai
    \i 8.19_oid.sql
    \?
    \qecho '\033[2J'
*/


/*      Object identifiers OIDs are used internally by PostgreSQL as primary
        keys for various system tables. OIDs are not added to user-created
        tables , unless WITH OIDS is specified when the table is created, or
        the default_with_oids configuration variable is enabled. Typs oid
        represents and object identifier.

        Table 8.24 Object Identifier Types
        Name            References    Description          Value Example
        --------------+-------------+---------------------+--------------------
        oid            any            numeric object       564182
                                      identifier

        regproc        pg_proc        function name        sum

        regprocedure   pg_proc        function with        sum(int4)
                                      argument types

        regoper        pg_operator    operator name        +

        regoperator    pg_operator    operator with        *(integer,integer) or
                                      argument types       -(NONE,integer)

        regclass       pg_class       relation name        pg_type
        regtype        pg_type        data type name       integer
        regrole        pg_authid      role name            smithee
        regnamespace   pg_namespace   namespace name       pg_catalog

        regconfig      pg_ts_config   text search          english
                                      configuration

        regdictionary  pg_ts_dict     text search          simple
                                      dictionary
        ------------------------------------------------------------------------

        The oid type is implemented as an unsigned four-byte integer. Therefore
        it is not large enough to provide database-wide uniqueness in large
        databases, or even in large individual tables. So, using a user-created
        talbe's OID column as a primary key is discouraged. OIDs are best used
        only for references to system tables.
*/

DROP TABLE IF EXISTS mytable CASCADE;
CREATE TABLE mytable (id SERIAL, name TEXT);
INSERT INTO mytable (name) VALUES ('Annaliese Kirk'),
                                  ('Warren Lang'),
                                  ('Alvin Mccann'),
                                  ('Pharrell Sawyer'),
                                  ('Cinar Perez'),
                                  ('Haydn Trejo'),
                                  ('Rosemarie Odling'),
                                  ('Abubakr Rees'),
                                  ('April Rice');

SELECT * FROM pg_attribute WHERE attrelid = 'mytable'::regclass;
/*
 attrelid | attname  | atttypid | attstattarget | attlen | attnum | attndims | attcacheoff | atttypmod | attbyval | attstorage | attalign | attnotnull | atthasdef | atthasmissing | attidentity | attisdropped | attislocal | attinhcount | attcollation | attacl | attoptions | attfdwoptions | attmissingval 
----------+----------+----------+---------------+--------+--------+----------+-------------+-----------+----------+------------+----------+------------+-----------+---------------+-------------+--------------+------------+-------------+--------------+--------+------------+---------------+---------------
    20506 | tableoid |       26 |             0 |      4 |     -7 |        0 |          -1 |        -1 | t        | p          | i        | t          | f         | f             |             | f            | t          |           0 |            0 |        |            |               | 
    20506 | cmax     |       29 |             0 |      4 |     -6 |        0 |          -1 |        -1 | t        | p          | i        | t          | f         | f             |             | f            | t          |           0 |            0 |        |            |               | 
    20506 | xmax     |       28 |             0 |      4 |     -5 |        0 |          -1 |        -1 | t        | p          | i        | t          | f         | f             |             | f            | t          |           0 |            0 |        |            |               | 
    20506 | cmin     |       29 |             0 |      4 |     -4 |        0 |          -1 |        -1 | t        | p          | i        | t          | f         | f             |             | f            | t          |           0 |            0 |        |            |               | 
    20506 | xmin     |       28 |             0 |      4 |     -3 |        0 |          -1 |        -1 | t        | p          | i        | t          | f         | f             |             | f            | t          |           0 |            0 |        |            |               | 
    20506 | ctid     |       27 |             0 |      6 |     -1 |        0 |          -1 |        -1 | f        | p          | s        | t          | f         | f             |             | f            | t          |           0 |            0 |        |            |               | 
    20506 | id       |       23 |            -1 |      4 |      1 |        0 |          -1 |        -1 | t        | p          | i        | t          | t         | f             |             | f            | t          |           0 |            0 |        |            |               | 
    20506 | name     |       25 |            -1 |     -1 |      2 |        0 |          -1 |        -1 | f        | x          | i        | f          | f         | f             |             | f            | t          |           0 |          100 |        |            |               | 
(8 rows)
*/

/*      An addition property of most of the OID alias types is the creation of
        dependencies. PostgreSQL understands that if an expression depends on
        a sequence the system will not let the sequence be dropped without first
        removing the expression.

        Another identifier type used by the system is xid, or transaction
        (abbreviated xact) identifier. This is the data type of the system
        columns xmin and xmax. Transaction identifiers are 32-bit quantities.

        A third identifier type used by the system is cid, or command identifier.
        This is the data type of the system columns cmin and cmax.
        Command identifiers are also 32-bit quantities.

        A final identifier type used by the system is tid, or tuple identifier
        (row identifier). This is the data type of the system column ctid.
        A tuple ID is a pair (block number, tuple index within block) that
        identifies the physical location of the row within its table.
*/

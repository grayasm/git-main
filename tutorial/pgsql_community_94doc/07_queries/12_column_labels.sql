/*  Cap.7   Queries
    7.3     Select Lists
    7.3.2   Column Labels

    psql -d mytestdb -U pgmihai
    \i 12_column_labels.sql
*/


/*      The entries in the select list can be assigned names for subsequent
        processing, such as for use in an ORDER BY clause or for display by
        the client application. */

DROP TABLE IF EXISTS t1 CASCADE;
CREATE TABLE t1 (id INTEGER, x NUMERIC, y NUMERIC, z NUMERIC);
INSERT INTO t1 VALUES (1, 10, 11, 12),
                      (2, 20, 21, 22),
                      (3, 30, 31, 32);

SELECT x, x + y + z AS sum FROM t1;

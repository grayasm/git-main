/*  Cap.7   Queries
    7.2     Table Expressions
    7.2.1   The FROM Clause

    psql -d mytestdb -U pgmihai
    \i 02_from.sql
*/

/*      FROM table_reference [,table_reference [, ...]]

        If more than one table reference is listed in the FROM clause,
        the tables are cross-joined (that is, the Cartesian product of
        their rows is formed).
*/

DROP TABLE IF EXISTS t1,t2,t3 CASCADE;
CREATE TABLE t1 (i1 numeric);
CREATE TABLE t2 (j1 numeric, j2 numeric);
CREATE TABLE t3 (k1 numeric, k2 numeric, k3 numeric);

INSERT INTO t1 VALUES (1);
INSERT INTO t2 VALUES (2.0, 2.1), (2.2, 2.3);
INSERT INTO t3 VALUES (3.0, 3.1, 3.2),
                      (3.3, 3.4, 3.5),
                      (3.6, 3.7, 3.8);

SELECT * FROM t1, t2, t3;

/*
 i1 | j1  | j2  | k1  | k2  | k3  
----+-----+-----+-----+-----+-----
  1 | 2.0 | 2.1 | 3.0 | 3.1 | 3.2
  1 | 2.0 | 2.1 | 3.3 | 3.4 | 3.5
  1 | 2.0 | 2.1 | 3.6 | 3.7 | 3.8
  1 | 2.2 | 2.3 | 3.0 | 3.1 | 3.2
  1 | 2.2 | 2.3 | 3.3 | 3.4 | 3.5
  1 | 2.2 | 2.3 | 3.6 | 3.7 | 3.8
(6 rows)
*/

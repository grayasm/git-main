/*  Cap.7   Queries
    7.2     Table Expressions
    7.2.1   The FROM Clause

    psql -d mytestdb -U pgmihai
    \i 02_from.sql
    \?
    \qecho '\033[2J'
*/


/*      FROM table_reference [,table_reference [, ...]]

        If more than one table reference is listed in the FROM clause,
        the tables are cross-joined (that is, the Cartesian product of
        their rows is formed).
*/

DROP TABLE IF EXISTS t1,t2 CASCADE;
CREATE TABLE t1 (num integer, name text);
CREATE TABLE t2 (num integer, value text);

INSERT INTO t1 VALUES (1,'a'), (2,'b'), (3,'c');
INSERT INTO t2 VALUES (1,'x'), (2,'y'), (3,'z');

SELECT * FROM t1, t2;
/*
 num | name | num | value
-----+------+-----+-------
   1 | a    |   1 | x
   1 | a    |   2 | y
   1 | a    |   3 | z
   2 | b    |   1 | x
   2 | b    |   2 | y
   2 | b    |   3 | z
   3 | c    |   1 | x
   3 | c    |   2 | y
   3 | c    |   3 | z
(9 rows)
*/

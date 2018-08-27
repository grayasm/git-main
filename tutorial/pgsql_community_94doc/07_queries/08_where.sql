/*  Cap.7   Queries
    7.2     Table Expressions
    7.2.2   The WHERE Clause

    psql -d mytestdb -U pgmihai
    \i 08_where.sql
*/


/*      The syntax of the WHERE is:

        WHERE search_condition

        where search_condition is any value expression that returns a value of
        type boolean. The WHERE clause is processed after the FROM clause.
        Each row of the derived virtual table is checked against the
        search_condition and if the result is true the row is kept
        in the output table, otherwise the result is false or null
        and the row is discarded.
*/

DROP TABLE IF EXISTS t1,t2 CASCADE;
CREATE TABLE t1 (id INTEGER, x NUMERIC, y NUMERIC, z NUMERIC);
CREATE TABLE t2 (id INTEGER, x NUMERIC, y NUMERIC, z NUMERIC);

INSERT INTO t1 VALUES (1, -10, 0, +10), (2, -20, 0, +20), (3, -30, 0, +30),
                      (4, +10, +20, +30), (5, 0, 0, +100), (6, +20, +30, +40),
                      (7, -15, 0, 0), (8, +30, +45, +50), (9, 22, 30, 0);
INSERT INTO t2(id, x, y, z) SELECT * FROM t1 WHERE x > 0 AND y > 0 AND z > 0;


/*      Here are some examples of the WHERE clause. */
SELECT * FROM t1 WHERE x > 5;
SELECT * FROM t1 WHERE x IN (-30, -20, -10, 0);
SELECT * FROM t1 WHERE x IN (SELECT x FROM t2);
SELECT * FROM t1 WHERE x IN (SELECT x FROM t2 WHERE y = t1.x + 10);
SELECT * FROM t1 WHERE x BETWEEN (SELECT x FROM t2 WHERE y = t1.x + 10) AND 100;
SELECT * FROM t1 WHERE EXISTS (SELECT x FROM t2 WHERE y > t1.x);

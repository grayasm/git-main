/*  Cap.7   Queries
    7.2     Table Expressions
    7.2.1   The FROM Clause
    7.2.1.5 LATERAL Subquery

    psql -d mytestdb -U pgmihai
    \i   2.1_from_lateral.sql
    \?
    \qecho '\033[2J'
*/


/*      Subqueries appearing in FROM can be preceded by the key word LATERAL.
        This allows them to reference columns provided by preceding FROM items.
        Without LATERAL , each subquery is evaluated independently and so cannot
        cross-reference any other FROM item.
*/


DROP TABLE IF EXISTS t1, t2 CASCADE;
CREATE TABLE t1 (id INTEGER, code TEXT, value NUMERIC);
CREATE TABLE t2 (num INTEGER, value NUMERIC);

INSERT INTO t1 VALUES (1,'add',10.0), (2,'sub',5.0), (3,'mul',3);
INSERT INTO t2 VALUES (1, 10.0), (2, 5.0), (3, 11.0);

SELECT * FROM t1, LATERAL (SELECT * FROM t2 WHERE t1.id = t2.num) AS a;
/*
psql:07_from_lateral.sql:25: ERROR:  syntax error at or near "SELECT"
LINE 1: SELECT * FROM t1, LATERAL (SELECT * FROM t2 WHERE t1.id = t2...
*/
--LATERAL not supported in 9.2

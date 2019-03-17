/*  Cap.7   Queries
    7.2     Table Expressions
    7.2.1   The FROM Clause
    7.2.1.4 Table Functions

    psql -d mytestdb -U pgmihai
    \i 7.02.1_from_function.sql
    \?
    \qecho '\033[2J'
*/

/*      Table functions are functions that produce a set of rows, made up of
        either
        - base data types (scalar types) or
        - composite data types (table rows).

        They are used like
        > a table
        > a view, or
        > a subquery
        in the FROM clause of a query. Columns returned by table functions
        can be included in SELECT , JOIN , or WHERE clauses in the same manner
        as columns of a table, view, or subquery.
*/



DROP TABLE    IF EXISTS t1      CASCADE;
DROP FUNCTION IF EXISTS return_table(integer) CASCADE;
DROP FUNCTION IF EXISTS return_out  (integer) CASCADE;

CREATE TABLE t1(num integer, val text);
INSERT INTO  t1 VALUES (1,'a'), (2,'b'), (3,'c');

CREATE FUNCTION return_table(id integer)    -- obs:this function returns a table
       RETURNS TABLE(num_ integer, val_ text)
       AS
       $$
            SELECT * FROM t1 WHERE num > id;
       $$
LANGUAGE 'sql' VOLATILE;

CREATE FUNCTION return_out(id integer)      -- obs: this function returns SETOF
       RETURNS SETOF t1
       AS
       $$
            SELECT * FROM t1 WHERE num > id;
       $$
LANGUAGE 'sql' VOLATILE;

SELECT * FROM return_table(1) AS a;         -- FROM function returning table
/*
 num_ | val_
------+------
    2 | b
    3 | c
(2 rows)
*/

SELECT * FROM return_out(2) AS b;           -- FROM function returning SETOF
/*
 num | val
-----+-----
   3 | c
(1 row)
*/


CREATE VIEW vw1 AS SELECT * FROM return_table(0);
SELECT * FROM vw1;                          -- FROM view
/*
 num_ | val_
------+------
    1 | a
    2 | b
    3 | c
(3 rows)
*/

SELECT * FROM t1 WHERE num IN               -- FROM subquery
       (
            SELECT num FROM return_out(0) AS a WHERE a.num <> 1
       );
/*
 num | val
-----+-----
   2 | b
   3 | c
(2 rows)
*/

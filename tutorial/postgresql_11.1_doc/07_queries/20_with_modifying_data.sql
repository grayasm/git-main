/*  Cap.7   Queries
    7.8     WITH queries
    7.8.2   Data modifying statements in WITH

    psql -d mytestdb -U pgmihai
    \i 20_with_modifying_data.sql
*/


/*      You can use INSERT,UPDATE,DELETE in a WITH statement.
        Data modifying statements in WITH, have RETURNING clause to return
        the temporary table. It is the output of the RETURNING clause,
        not the target table of the data-modifying statement, that forms
        the temporary table that can be referred to by the rest of the query.
*/

DROP TABLE IF EXISTS products, products_log CASCADE;
CREATE TABLE products(num INTEGER, nume VARCHAR(255), _date DATE);
CREATE TABLE products_log (num INTEGER, nume VARCHAR(255), _date DATE);

INSERT INTO products VALUES (1, 'p1', '2010-01-01'),
                            (2, 'p2', '2012-01-01'),
                            (3, 'p3', '2013-01-01'),
                            (4, 'p4', '2014-01-01'),
                            (5, 'p5', '2015-01-01');

WITH moved_rows AS (
     DELETE FROM products
            WHERE "_date" >= '2011-01-01' AND
                  "_date" <  '2015-01-01'
            RETURNING *
     )
     INSERT INTO products_log
     SELECT * FROM moved_rows;

-- show the result
SELECT * FROM products;
SELECT * FROM products_log;
/*
 num | nume |   _date    
-----+------+------------
   1 | p1   | 2010-01-01
   5 | p5   | 2015-01-01
(2 rows)

 num | nume |   _date    
-----+------+------------
   2 | p2   | 2012-01-01
   3 | p3   | 2013-01-01
   4 | p4   | 2014-01-01
(3 rows)
*/



/*      Recursive self-references in data-modifying statements are not allowed.
        In some cases it is possible to work around this limitation by referring
        to the output of a recursive WITH.
        Example: delete manager1 and all its dependent workers.
*/
DROP TABLE IF EXISTS tab1 CASCADE;
CREATE TABLE tab1(employee_id INTEGER, manager_id INTEGER, nume TEXT);
INSERT INTO tab1 VALUES (1, NULL, 'boss'),
                        (2, 1, 'sub-boss'),
                        (3, 2, 'manager1'),
                        (4, 2, 'manager2'),
                        (5, 3, 'man1-w1'),
                        (6, 3, 'man1-w2'),
                        (7, 3, 'man1-w3'),
                        (8, 4, 'man2-w1');

WITH RECURSIVE with_tab1 (employee_id, manager_id, nume) AS (
     SELECT employee_id, manager_id, nume
            FROM tab1
            WHERE employee_id = 3
     UNION ALL
     SELECT t1.employee_id, t1.manager_id, t1.nume
            FROM with_tab1 stab1, tab1 t1
            WHERE t1.manager_id = stab1.employee_id
     )
     DELETE FROM tab1
     WHERE employee_id IN (SELECT employee_id FROM with_tab1);

-- show the result
SELECT * FROM tab1;
/*
 employee_id | manager_id |   nume   
-------------+------------+----------
           1 |            | boss
           2 |          1 | sub-boss
           4 |          2 | manager2
           8 |          4 | man2-w1
(4 rows)
*/


/*      Data modifying statements in WITH:
        > are executed only once in a snapshot
        > substatements are executed in parallel with the main query
        > the order is unpredicatable unless RETURNING is used, which is the
          only way to communicate changes between a subquery and the main query
        > a row is updated only 1 time in a snapshot. 
        > a table must not have a conditional rule, ALSO or INSTEAD clauses that
          expand to multiple statements
*/
DROP TABLE IF EXISTS table1,table2 CASCADE;
CREATE TABLE table1 (v NUMERIC);
CREATE TABLE table2 (v NUMERIC);
INSERT INTO table1 VALUES (1), (2), (3), (4), (5);
INSERT INTO table2 VALUES (1), (2), (3), (4), (5);

WITH t AS (
     UPDATE table1 SET v = v * 10
     RETURNING *
     )
     SELECT * FROM table1;
/*
 v 
---
 1
 2
 3
 4
 5
(5 rows)
*/

WITH t AS (
     UPDATE table2 SET v = v * 10
     RETURNING *
     )
     SELECT * FROM t;
/*
 v  
----
 10
 20
 30
 40
 50
(5 rows)
*/

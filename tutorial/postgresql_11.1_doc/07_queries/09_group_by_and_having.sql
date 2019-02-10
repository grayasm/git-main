/*  Cap.7   Queries
    7.2     Table Expressions
    7.2.3   The GROUP BY and HAVING clauses

    psql -d mytestdb -U pgmihai
    \i 09_group_by_and_having.sql
    \?
    \qecho '\033[2J'
*/



/*      After passing the WHERE filter, the derived input table might be subject
        to grouping, using the GROUP BY clause, and elimination of group rows
        using HAVING clause.

        SELECT select_list
               FROM ...
               [WHERE ...]
               GROUP BY grouping_column_reference [, grouping_column_reference]
               HAVING boolean_expression;
*/


DROP TABLE IF EXISTS t1 CASCADE;
CREATE TABLE t1 (x TEXT, y NUMERIC);
INSERT INTO t1 VALUES ('a', 3),
                      ('c', 2),
                      ('b', 5),
                      ('a', 1);

/*      Some examples of the GROUP BY, and HAVING clause. */
SELECT * FROM t1;
SELECT x FROM t1 GROUP BY x;
/*
 x
---
 c
 b
 a
(3 rows)
*/

SELECT x, sum(y) FROM t1 GROUP BY x;
/*
 x | sum
---+-----
 c |   2
 b |   5
 a |   4
(3 rows)
*/

SELECT x, sum(y) FROM t1 GROUP BY x HAVING sum(y) > 3;
/*
 x | sum
---+-----
 b |   5
 a |   4
(2 rows)
*/

SELECT x, sum(y) FROM t1 GROUP BY x HAVING x < 'c';
/*
 x | sum
---+-----
 b |   5
 a |   4
(2 rows)
*/

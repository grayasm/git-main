/*  Cap.7   Queries
    7.5     Sorting rows

    psql -d mytestdb -U pgmihai
    \i 7.05.0_order_by.sql
    \?
    \qecho '\033[2J'
*/


/*      If sorting is not chosen the ordering will depend on:
        the scan and join plan types and the order on disk.
        Specify the sort order with: ORDER BY clause.

        SELECT sel_list
               FROM table_expr
               ORDER BY sort_expr [ASC | DESC] [NULLS {FIRST | LAST}]
                      [,sort_expr [ASC | DESC] [NULLS {FIRST | LAST}] ...]
*/

DROP TABLE IF EXISTS t1 CASCADE;
CREATE TABLE t1 (a NUMERIC, b NUMERIC, c NUMERIC);
INSERT INTO t1 VALUES (1, 2, 3),
                      (1, 2, 2),
                      (1, 2, 1),
                      (2, 1, 1),
                      (2, 2, 1),
                      (2, 3, 1),
                      (3, 3, 1),
                      (3, 2, 2),
                      (3, 1, 3),
                      (3, NULL, NULL);

SELECT a, b FROM t1 ORDER BY a+b, c; -- any expression that would be valid
/*
 a | b
---+---
 1 | 2
 2 | 1
 1 | 2
 1 | 2
 2 | 2
 3 | 1
 2 | 3
 3 | 2
 3 | 3
 3 |
(10 rows)
*/

SELECT a,b,c FROM t1 ORDER BY a ASC, b ASC NULLS FIRST, c DESC; -- use ASC,DESC
/*
 a | b | c
---+---+---
 1 | 2 | 3
 1 | 2 | 2
 1 | 2 | 1
 2 | 1 | 1
 2 | 2 | 1
 2 | 3 | 1
 3 |   |
 3 | 1 | 3
 3 | 2 | 2
 3 | 3 | 1
(10 rows)
*/

SELECT a+b AS sum, c FROM t1 ORDER BY sum; -- by column label 'sum'
/*
 sum | c
-----+---
   3 | 2
   3 | 1
   3 | 1
   3 | 3
   4 | 3
   4 | 1
   5 | 1
   5 | 2
   6 | 1
     |
(10 rows)
*/

SELECT a,max(b) FROM t1 GROUP BY a ORDER BY 1; -- by number of output column: 1
/*
 a | max
---+-----
 1 |   2
 2 |   3
 3 |   3
(3 rows)
*/


--SELECT a+b AS sum, c FROM t1 ORDER BY sum+c;  <-- wrong, restricted to reduce
--                                                  the ambiguity.

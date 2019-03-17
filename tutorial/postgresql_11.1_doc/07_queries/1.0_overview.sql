/*  Cap.7   Queries
    7.1     Overview

    psql -d mytestdb -U pgmihai
    \i 7.01.0_overview.sql
    \?
    \qecho '\033[2J'
*/


/*      A query is the process of retrieving data from a database with SELECT.
        The general syntax of command SELECT is:
        [WITH with_queries] SELECT sel_list FROM table_expr [sort_specification]

        You can use SELECT to:
        > do a simple query
        > make calculations w/o using columns
        > call a function
*/

DROP TABLE IF EXISTS t1 CASCADE;
CREATE TABLE t1 (
        a       numeric,
        b       numeric,
        c       numeric
        );

INSERT INTO t1 VALUES (0, 0.1, 0.2), (1, 1.1, 1.2), (2, 2.1, 2.2), (3, 3.1, 3.2);

SELECT * FROM t1;
SELECT a, b + c FROM t1;
SELECT 3 * 4;
SELECT random();

/*  Cap.7   Queries
    7.2     Table Expressions
    7.2.4   Window Function Processing

    psql -d mytestdb -U pgmihai
    \i 7.02.5_window_function_processing.sql
    \?
    \qecho '\033[2J'
*/

/*      http://www.postgresqltutorial.com/postgresql-window-function/

        window_function(arg1,arg2,..) OVER (PARTITION BY expr ORDER BY expr)

        window_funtion: any built-in or user-defined aggregate function.
        PARTITION BY  : used to devide rows into groups or partitions.
        ORDER BY      : window function will process the rows in the order
                        specified by ORDER BY clause especially for the window
                        functions that are sensitive to the order such as
                        fist_value(), last_value(), nth_value().

        ex: SELECT x, wf(y) OVER (PARTITION BY z ORDER BY w), ...
*/

DROP TABLE IF EXISTS pers,finc CASCADE;
CREATE TABLE pers (id INTEGER, nume TEXT, job TEXT);
CREATE TABLE finc (id INTEGER, salary NUMERIC);

INSERT INTO pers VALUES (1, 'An Hua', 'aplication engineer'),
                        (2, 'Ai Hia', 'aplication engineer'),
                        (3, 'Ao Tua', 'aplication engineer'),
                        (4, 'Pi Yng', 'principal developer'),
                        (5, 'Si Tog', 'senior developer'),
                        (6, 'Si Toa', 'senior developer'),
                        (7, 'Si Tao', 'senior developer'),
                        (8, 'Di Hao', 'developer'),
                        (9, 'Di Jia', 'developer'),
                       (10, 'Di Mao', 'developer'),
                       (11, 'Di Dao', 'developer');

INSERT INTO finc VALUES (1, 1000.0),
                        (2, 1040.0),
                        (3, 1050.0), -- average=1030
                        (4, 5000.0), -- unique
                        (5, 3000.0),
                        (6, 3040.0),
                        (7, 3080.0), -- average=3040
                        (8, 2000.0),
                        (9, 2020.0),
                       (10, 2010.0),
                       (11, 2010.0); -- average=2010



/*      The next 2 examples show the difference between:
        (a) AVG(x) as aggregate function
        (b) AVG(x) as window    function
        An (a) aggregate function uses: GROUP BY
        A  (b) window function uses:    OVER (PARTITION BY x ORDER BY y)
*/


/*      An aggregate function aggregates data from a set of rows into a single
        row. To apply the aggregate function to subsets of rows use GROUP BY
        clause. */

SELECT job, AVG(salary)
       FROM pers INNER JOIN finc USING(id)
       GROUP BY job;

/*
         job         |          avg
---------------------+-----------------------
 aplication engineer | 1030.0000000000000000
 developer           | 2010.0000000000000000
 senior developer    | 3040.0000000000000000
 principal developer | 5000.0000000000000000
(4 rows)
*/




/*      A window function operates on a set of rows, but it does not reduce the
        number of rows returned by the query.
        A window function returns a value from the rows in a window. */

SELECT job, AVG(salary) OVER (PARTITION BY job)
       FROM pers INNER JOIN finc USING(id);

/*
         job         |          avg
---------------------+-----------------------
 aplication engineer | 1030.0000000000000000
 aplication engineer | 1030.0000000000000000
 aplication engineer | 1030.0000000000000000
 developer           | 2010.0000000000000000
 developer           | 2010.0000000000000000
 developer           | 2010.0000000000000000
 developer           | 2010.0000000000000000
 principal developer | 5000.0000000000000000
 senior developer    | 3040.0000000000000000
 senior developer    | 3040.0000000000000000
 senior developer    | 3040.0000000000000000
(11 rows)
*/


/*      More examples for window functions: ROW_NUMBER(), RANK(), FIRST_VALUE()
        LAST_VALUE(). */


/*      The ROW_NUMBER() function assigns a running serial number to rows in
        each partition. */
SELECT nume, job, salary, ROW_NUMBER() OVER (PARTITION BY job ORDER BY salary)
       FROM pers INNER JOIN finc USING(id);

/*
  nume  |         job         | salary | row_number
--------+---------------------+--------+------------
 An Hua | aplication engineer | 1000.0 |          1
 Ai Hia | aplication engineer | 1040.0 |          2
 Ao Tua | aplication engineer | 1050.0 |          3
 Di Hao | developer           | 2000.0 |          1
 Di Dao | developer           | 2010.0 |          2
 Di Mao | developer           | 2010.0 |          3
 Di Jia | developer           | 2020.0 |          4
 Pi Yng | principal developer | 5000.0 |          1
 Si Tog | senior developer    | 3000.0 |          1
 Si Toa | senior developer    | 3040.0 |          2
 Si Tao | senior developer    | 3080.0 |          3
(11 rows)
*/



/*      The RANK() function assigns ranking within an ordered partition.
        If the values of the two rows are the same, the  RANK() function
        assigns the same rank, with the next ranking(s) skipped. */
SELECT nume, job, salary, RANK() OVER (PARTITION BY job ORDER BY salary)
       FROM pers INNER JOIN finc USING(id);

/*
  nume  |         job         | salary | rank
--------+---------------------+--------+------
 An Hua | aplication engineer | 1000.0 |    1
 Ai Hia | aplication engineer | 1040.0 |    2
 Ao Tua | aplication engineer | 1050.0 |    3
 Di Hao | developer           | 2000.0 |    1
 Di Dao | developer           | 2010.0 |    2
 Di Mao | developer           | 2010.0 |    2
 Di Jia | developer           | 2020.0 |    4
 Pi Yng | principal developer | 5000.0 |    1
 Si Tog | senior developer    | 3000.0 |    1
 Si Toa | senior developer    | 3040.0 |    2
 Si Tao | senior developer    | 3080.0 |    3
(11 rows)
*/


/*      The FIRST_VALUE() function returns the first value from the first row
        of the ordered set, aka the lowest salary per group. */

SELECT nume, job, salary, FIRST_VALUE(salary) OVER (PARTITION BY job ORDER BY salary)
       AS lowest_salary_per_group
       FROM pers INNER JOIN finc USING(id);

/*
  nume  |         job         | salary | lowest_salary_per_group
--------+---------------------+--------+-------------------------
 An Hua | aplication engineer | 1000.0 |                  1000.0
 Ai Hia | aplication engineer | 1040.0 |                  1000.0
 Ao Tua | aplication engineer | 1050.0 |                  1000.0
 Di Hao | developer           | 2000.0 |                  2000.0
 Di Dao | developer           | 2010.0 |                  2000.0
 Di Mao | developer           | 2010.0 |                  2000.0
 Di Jia | developer           | 2020.0 |                  2000.0
 Pi Yng | principal developer | 5000.0 |                  5000.0
 Si Tog | senior developer    | 3000.0 |                  3000.0
 Si Toa | senior developer    | 3040.0 |                  3000.0
 Si Tao | senior developer    | 3080.0 |                  3000.0
(11 rows)
*/


/*      Use LAST_VALUE() function to return the highest salary per group. */
SELECT nume, job, salary, LAST_VALUE(salary)
       OVER (PARTITION BY job ORDER BY salary RANGE BETWEEN UNBOUNDED PRECEDING
       AND UNBOUNDED FOLLOWING) AS highest_salary_per_group
       FROM pers INNER JOIN finc USING(id);

/*
  nume  |         job         | salary | highest_salary_per_group
--------+---------------------+--------+--------------------------
 An Hua | aplication engineer | 1000.0 |                   1050.0
 Ai Hia | aplication engineer | 1040.0 |                   1050.0
 Ao Tua | aplication engineer | 1050.0 |                   1050.0
 Di Hao | developer           | 2000.0 |                   2020.0
 Di Dao | developer           | 2010.0 |                   2020.0
 Di Mao | developer           | 2010.0 |                   2020.0
 Di Jia | developer           | 2020.0 |                   2020.0
 Pi Yng | principal developer | 5000.0 |                   5000.0
 Si Tog | senior developer    | 3000.0 |                   3080.0
 Si Toa | senior developer    | 3040.0 |                   3080.0
 Si Tao | senior developer    | 3080.0 |                   3080.0
(11 rows)
*/

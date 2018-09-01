/*  Cap.7   Queries
    7.2     Table Expressions
    7.2.4   Window Function Processing

    psql -d mytestdb -U pgmihai
    \i 10_window_function_processing.sql
*/

/*      window_function(arg1,arg2,..) OVER (PARTITION BY expr ORDER BY expr)

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


/*  Comparing AVG(x) as aggregate versus window function. */


/*  An aggregate function aggregates data from a set of rows into a single row.
    To apply the aggregate function to subsets of rows use GROUP BY clause. */

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




/*  A window function operates on a set of rows, but it does not reduce the
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


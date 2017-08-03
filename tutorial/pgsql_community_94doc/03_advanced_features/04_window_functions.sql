/*  Cap.3 Advanced Features
    3.5 Window Functions

    Run with:
    psql -d mytestdb -U pgmihai   # give password
    \i 04_window_functions.sql
*/


-- create full sample of data for this example
DROP TABLE IF EXISTS empsalary;

CREATE TABLE empsalary(
	depname		varchar(80),
	empno		int,
	salary		real
);

INSERT INTO empsalary VALUES ('develop', 11, 5200);
INSERT INTO empsalary VALUES ('develop',  7, 4200);
INSERT INTO empsalary VALUES ('develop',  9, 4500);
INSERT INTO empsalary VALUES ('develop',  8, 6000);
INSERT INTO empsalary VALUES ('develop', 10, 5200);
INSERT INTO empsalary VALUES ('personnel', 5, 3500);
INSERT INTO empsalary VALUES ('personnel', 2, 3900);
INSERT INTO empsalary VALUES ('sales', 3, 4800);
INSERT INTO empsalary VALUES ('sales', 1, 5000);
INSERT INTO empsalary VALUES ('sales', 4, 4800);


/*  A window function performs a calculation across a set of table rows that
    are somehow related to the current row. Unlinke regular aggregate functions
    use of a window function does not cause rows to become grouped into a
    single output row - the rows retain their separate identities.
*/
SELECT depname, empno, salary, avg(salary)
	OVER (PARTITION BY depname)
	FROM empsalary;

/*
  depname  | empno | salary |       avg        
-----------+-------+--------+------------------
 develop   |    11 |   5200 |             5020
 develop   |     7 |   4200 |             5020
 develop   |     9 |   4500 |             5020
 develop   |     8 |   6000 |             5020
 develop   |    10 |   5200 |             5020
 personnel |     5 |   3500 |             3700
 personnel |     2 |   3900 |             3700
 sales     |     3 |   4800 | 4866.66666666667
 sales     |     1 |   5000 | 4866.66666666667
 sales     |     4 |   4800 | 4866.66666666667
*/


/*  The OVER clause causes it to be treated as a window function and computed
    accross an appropriate set of rows.
    The PARTITION BY list within OVER specifies dividing the rows into groups,
    or partitions, that share the same values of the PARTITION BY expression.
    For each row, the window function is computed across the rows that fall
    into the same partition as the current row.
*/
SELECT depname, empno, salary, rank()
	OVER (PARTITION BY depname ORDER BY salary DESC)
	FROM empsalary;

/*
  depname  | empno | salary | rank 
-----------+-------+--------+------
 develop   |     8 |   6000 |    1
 develop   |    10 |   5200 |    2
 develop   |    11 |   5200 |    2
 develop   |     9 |   4500 |    4
 develop   |     7 |   4200 |    5
 personnel |     2 |   3900 |    1
 personnel |     5 |   3500 |    2
 sales     |     1 |   5000 |    1
 sales     |     3 |   4800 |    2
 sales     |     4 |   4800 |    2
*/


/*  The window function (WF) processes the rows of the "virtual table"
    produced by the query's FROM, WHERE, GROUP BY, HAVING clauses.
    If a row is removed by the WHERE condition, it is not seen by the WF.
    A query can contain multiple WFs that slice up the data in different
    ways by means of WHERE clauses, but they all act on the same collection
    of rows defined by the "virtual table".
    It is possible to ommit ORDER BY, PARTITION BY.
*/

SELECT salary, sum(salary) OVER() FROM empsalary;

/*
 salary |  sum  
--------+-------
   5200 | 47100
   4200 | 47100
   4500 | 47100
   6000 | 47100
   5200 | 47100
   3500 | 47100
   3900 | 47100
   4800 | 47100
   5000 | 47100
   4800 | 47100
*/


/*  If we add an ORDER BY clause, we get very different results.
*/
SELECT depname, salary, sum(salary)
	OVER (ORDER BY salary)
	FROM empsalary;

/*
  depname  | salary |  sum  
-----------+--------+-------
 personnel |   3500 |  3500
 personnel |   3900 |  7400
 develop   |   4200 | 11600
 develop   |   4500 | 16100
 sales     |   4800 | 25700
 sales     |   4800 | 25700
 sales     |   5000 | 30700
 develop   |   5200 | 41100
 develop   |   5200 | 41100
 develop   |   6000 | 47100
*/


/*  Window functions are permitted only in the SELECT list and ORDER BY clause.
    They are forbidden elsewhere, such as GROUP BY, HAVING or WHERE clauses.
    Window functions execute after regular aggregate functions.
    If there is a need to filter or group rows after the window calculations
    are performed, you can use a sub-select.
*/
SELECT depname, empno, salary
    FROM (SELECT depname, empno, salary, rank()
          OVER (PARTITION BY depname ORDER BY salary DESC, empno) AS pos
          FROM empsalary
         ) AS ss
    WHERE pos < 3;

/*
  depname  | empno | salary 
-----------+-------+--------
 develop   |     8 |   6000
 develop   |    10 |   5200
 personnel |     2 |   3900
 personnel |     5 |   3500
 sales     |     1 |   5000
 sales     |     3 |   4800
*/	


/*  The above query shows the rows from the inner query having rank() less
    then 3.
    When a query involves multiple window functions, it is possible to write
    out each one with a separate OVER clause, or each windowing behavior can
    be named in a WINDOW clause and then referenced in OVER.
 */
SELECT sum(salary) OVER w, avg(salary) OVER w
	FROM empsalary
	WINDOW w AS (PARTITION BY depname ORDER BY salary DESC);

/*
  sum  |       avg        
-------+------------------
  6000 |             6000
 16400 | 5466.66666666667
 16400 | 5466.66666666667
 20900 |             5225
 25100 |             5020
  3900 |             3900
  7400 |             3700
  5000 |             5000
 14600 | 4866.66666666667
 14600 | 4866.66666666667
*/

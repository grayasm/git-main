/*  Cap.2 The SQL Language,
    2.5 Querying a Table

    psql -d mytestdb -U pgmihai
    \i   5_select.sql
    \?
    \qecho '\033[2J'
*/

SELECT * FROM weather;  -- retrieve all rows from weather;

/*  The * is a shorthand for "all columns" */
SELECT city, temp_lo, temp_hi, prcp, date FROM weather;

/*  You can write expressions, not just simple column references
    in the select list.
*/
SELECT city, (temp_hi + temp_lo)/2 AS temp_avg, date FROM weather;


/*  A query can be "qualified" by adding WHERE clause which contains
    a Boolean expression, and only rows for which is true are returned.
    Example for weather of San Francisco on rainy days:
*/
SELECT * FROM weather WHERE city = 'San Francisco' AND prcp > 0.0;


/*  You can request that the results of a query be returned in sorted order:
*/
SELECT * FROM weather ORDER BY city;


/*  The sort order above is not fully specified, and so you might get
    San Francisco rows in either order. To order the lowest temperature
    in ascending order do:
*/
SELECT * FROM weather ORDER BY city, temp_lo;


/*  You can request that duplicate rows be removed from the results
    of a query.
*/
SELECT DISTINCT city FROM weather;


/*  Here again, the result row ordering might vary. You can ensure consistent
    results by using DISTINCT and ORDER BY together.
*/
SELECT DISTINCT city FROM weather ORDER BY city;

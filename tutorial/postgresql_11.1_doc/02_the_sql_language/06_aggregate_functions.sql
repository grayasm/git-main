/*  Cap.2 The SQL Language,
    2.7 Aggregate Functions

    Run with:
    psql -d mytestdb -U pgmihai
    \i 06_aggregate_functions.sql
    \?
    \qecho '\033[2J'
*/


/*  An aggregate function computes a single result from multiple input rows.
    There are aggregates to compute the: count, sum, avg(average),
    max(maximum) and min(minimum) over a set of rows.
*/
SELECT max(temp_lo) FROM weather;


/*  We want to know what city (or cities) that reading occured in. However,
    the aggregate max cannot be used in the WHERE clause, like this:
    SELECT city FROM weather WHERE temp_lo = max(temp_lo);
    In this case we accomplish the desired result by using a SUBQUERY.
*/
SELECT city FROM weather
       WHERE temp_lo = (SELECT max(temp_lo) FROM weather);


/*  Aggregates are also useful in combination with GROUP BY clauses.
    For example, we can get the maximum low temperature observed in each city
    with:
*/
SELECT city, max(temp_lo)
       FROM weather
       GROUP BY city;


/*  We can filter these grouped rows using HAVING.
*/
SELECT city, max(temp_lo)
       FROM weather
       GROUP BY city
       HAVING max(temp_lo) < 40;


/*  Finally, if we only care about cities whose names begin with "S" we might
    do:
*/
SELECT city, max(temp_lo)
       FROM weather
       WHERE city LIKE 'S%'
       GROUP BY city
       HAVING max(temp_lo) < 40;


/*  The fundamental different beween WHERE and HAVING is this:
    WHERE selects input rows before groups and aggregates are computed
    HAVING selects groups rows after groups and aggregates are computed,
    thus the WHERE clause must not contain aggregate functions.
*/

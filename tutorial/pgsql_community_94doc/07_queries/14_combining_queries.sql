/*  Cap.7   Queries
    7.4     Combining queries

    psql -d mytestdb -U pgmihai
    \i 14_combining_queries.sql
*/


/*      http://www.postgresqltutorial.com/postgresql-union/

        The result of two queries can be combined using set of operations
        union, intersection and difference. The syntax is:

        query1 UNION [ALL] query2
        query1 INTERSECT [ALL] query2
        query1 EXCEPT [ALL] query2
*/

DROP TABLE IF EXISTS sales1, sales2 CASCADE;
CREATE TABLE sales1 (nume TEXT, ammount NUMERIC);
CREATE TABLE sales2 (nume TEXT, ammount NUMERIC);
INSERT INTO sales1 VALUES ('Mike', 1000), ('John', 1100), ('Mary', 1200);
INSERT INTO sales1 VALUES ('Mike', 1100), ('John', 1200), ('Mary', 1300);

SELECT * FROM sales1 UNION SELECT * FROM sales2;
/*
 nume | ammount 
------+---------
 John |    1100
 Mary |    1200
 Mike |    1100
 Mary |    1300
 John |    1200
 Mike |    1000
(6 rows)
*/

SELECT * FROM sales1 UNION ALL SELECT * FROM sales2;
/*
 nume | ammount 
------+---------
 Mike |    1000
 John |    1100
 Mary |    1200
 Mike |    1100
 John |    1200
 Mary |    1300
(6 rows)
*/

SELECT * FROM sales1 UNION ALL SELECT * FROM sales2 ORDER BY nume ASC, ammount DESC;
/*
 nume | ammount 
------+---------
 John |    1200
 John |    1100
 Mary |    1300
 Mary |    1200
 Mike |    1100
 Mike |    1000
(6 rows)
*/

